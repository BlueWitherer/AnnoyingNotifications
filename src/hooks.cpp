#include <Include.h>

#include <horrible/OptionalAPI.hpp>

#include <ui/NotifNode.h>
#include <ui/NotifFeed.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;
using namespace cw::notifs;
using namespace horrible;

static std::vector<std::weak_ptr<Hook>> g_notifHooks;  // Array of registered notifications hooks
static bool g_horribleEnabled = true;                  // cuz geode event apis are acting gay...

namespace cw {
    static NotifNode* showNotif(const Notif* notif, CCNode* to, CopyableFunction<void(NotifNode*)>&& finished) {
        auto const size = CCDirector::sharedDirector()->getWinSize();

        auto x = size.width / 2.f;

        auto notifNode = NotifNode::create(notif, false);
        notifNode->setScale(0.875f);

        auto y = size.height + notifNode->getScaledContentHeight();
        auto yDown = size.height - (0.625f * notifNode->getScaledContentHeight());

        notifNode->setPosition({x, y});

        to->addChild(notifNode, HIGHEST_Z);

        notifNode->runAction(
            CCSequence::create(
                CCEaseExponentialOut::create(CCMoveTo::create(0.375f, {x, yDown})),
                CCDelayTime::create(rng::generate(2.5f, 3.75f)),
                CCEaseExponentialOut::create(CCMoveTo::create(0.375f, {x, y})),
                CallFuncExt::create([notifNode, finished = std::move(finished)]() {
                    notifNode->removeFromParent();
                    finished(notifNode);
                }),
                nullptr));

        if (auto fmod = FMODAudioEngine::sharedEngine()) (void)fmod->playEffectAsync("chest07.ogg");

        return notifNode;
    };
};

class $modify(NotifPlayLayer, PlayLayer) {
    static void onModify(auto& self) {
        if (Loader::get()->isModInstalled("cubicstudios.horriblemenu")) {
            utils::StringMap<std::shared_ptr<Hook>> const& hooks = self.m_hooks;  // intellisense my beloved
            auto enable = OptionManagerV2::isEnabled(g_horribleID).unwrapOr(true);

            for (auto const& hook : hooks | std::views::values) {
                hook->setAutoEnable(enable);
                (void)hook->toggle(enable);

                g_notifHooks.push_back(hook);
            };
        };
    };

    struct Fields final {
        Ref<NotifFeed> feed = nullptr;
    };

    void toggleAll(bool on) {
        auto f = m_fields.self();

        if (!on) {
            unschedule(schedule_selector(NotifPlayLayer::showNewNotif));
            cue::resetNode(f->feed);

            return;
        };

        if (Mod::get()->getSettingValue<bool>("challenge-mode")) {
            f->feed = NotifFeed::create(m_uiLayer->getScaledContentHeight());
            f->feed->setPosition({getScaledContentWidth(), getScaledContentHeight() / 2.f});

            m_uiLayer->addChild(f->feed, HIGHEST_Z);
        };

        PlatformToolbox::showCursor();

        setupSchedules(!Mod::get()->getSettingValue<bool>("always-on"));
    };

    void setupSchedules(bool on) {
        if (on) scheduleOnce(schedule_selector(NotifPlayLayer::showNewNotif), rng::generate(0.125f, 6.25f));
        if (!on) unschedule(schedule_selector(NotifPlayLayer::showNewNotif));
    };

    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();

        toggleAll(true);
    };

    void showNewNotif(float) {
        auto notifRes = NotifManager::get()->getRandom();
        if (notifRes.isErr()) return;

        auto notif = std::move(notifRes).unwrap();

        auto notifNode = cw::showNotif(notif, m_uiLayer, [this](NotifNode* sender) { cleanNotif(sender); });

        notifNode->setCallback([this, notifNode](bool correct) {
            if (notifNode) notifNode->removeFromParent();
            if (!correct) resetLevelFromStart();
        });

        auto f = m_fields.self();

        if (f->feed) f->feed->addNotif(notif, [this](bool correct) {
            if (!correct) resetLevelFromStart();
        });
    };

    void cleanNotif(CCNode* sender) {
        cue::resetNode(sender);
        scheduleOnce(schedule_selector(NotifPlayLayer::showNewNotif), rng::generate(0.125f, 6.25f));
    };
};

// this is all probably a lot messier than it needs to be xdd
#define AN_RUN_GLOBAL_ONCE CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GlobalNotifDirector::showNewNotif), this, 0.f, 0, rng::generate(0.125f, 6.25f), false)

class GlobalNotifDirector final : public CCObject {
protected:
    GlobalNotifDirector() = default;
    ~GlobalNotifDirector() = default;

    GlobalNotifDirector(const GlobalNotifDirector&) = delete;
    GlobalNotifDirector& operator=(const GlobalNotifDirector&) = delete;

    GlobalNotifDirector(GlobalNotifDirector&&) = delete;
    GlobalNotifDirector& operator=(GlobalNotifDirector&&) = delete;

    void showNewNotif(float) {
        auto notifRes = NotifManager::get()->getRandom();
        if (notifRes.isErr()) return;

        auto notif = std::move(notifRes).unwrap();

        auto notifNode = cw::showNotif(notif, OverlayManager::get(), [this](NotifNode* sender) { cleanNotif(sender); });
    };

    void cleanNotif(CCNode* sender) {
        cue::resetNode(sender);
        if (g_horribleEnabled && Mod::get()->getSettingValue<bool>("always-on")) AN_RUN_GLOBAL_ONCE;
    };

public:
    static GlobalNotifDirector* get() noexcept {
        static auto inst = new (std::nothrow) GlobalNotifDirector();
        return inst;
    };

    void start() {
        log::info("Starting up global scheduler");  // extra horrible menu check :p
        if (g_horribleEnabled) AN_RUN_GLOBAL_ONCE;
    };

    void stop() {
        log::info("Stopping global scheduler");
        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    };
};

namespace cw {  // decl namespace again cuz we need to wait for gnd class decl apparently.....
    static void toggleGlobalNotifs(bool on) {
        if (auto gnd = GlobalNotifDirector::get()) on ? gnd->start() : gnd->stop();
        log::debug("Persistent notifications {}", on ? "ENABLED" : "DISBALED");
    };
};

$on_game(Loaded) {
    listenForSettingChanges<bool>(
        "always-on",
        [](bool on) {
            log::trace("{} persistent notifications", on ? "ENABLING" : "DISBALING");

            if (auto pl = PlayLayer::get()) modify_cast<NotifPlayLayer*>(pl)->setupSchedules(!on);
            cw::toggleGlobalNotifs(on);
        });

    cw::toggleGlobalNotifs(Mod::get()->getSettingValue<bool>("always-on"));

    if (Loader::get()->isModLoaded("cubicstudios.horriblemenu")) {
        auto const opt = OptionV2{
            AN_HORRIBLE_ID,
            "Spam Notifications",
            "Enable the annoying notification spam during gameplay.",
            "Notification Hell",
            SillyTier::High,
            true,
        };

        horrible::listenForHorribleOptionChanges(
            g_horribleID,
            [](HorribleOptionSave data) {
                g_horribleEnabled = data.enabled;

                for (auto const& hook : g_notifHooks) {
                    if (auto h = hook.lock()) (void)h->toggle(data.enabled);
                };

                if (auto pl = PlayLayer::get()) modify_cast<NotifPlayLayer*>(pl)->toggleAll(data.enabled);
                cw::toggleGlobalNotifs(data.enabled && Mod::get()->getSettingValue<bool>("always-on"));
            });

        OptionManagerV2::registerOption(opt);
    };
};
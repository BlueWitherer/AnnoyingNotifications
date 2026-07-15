#include <Include.h>

#include <ui/NotifNode.h>
#include <ui/NotifFeed.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;
using namespace cw::notifs;

class $modify(NotifPlayLayer, PlayLayer) {
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

        f->feed = NotifFeed::create(m_uiLayer->getScaledContentHeight());
        f->feed->setPosition({getScaledContentWidth(), getScaledContentHeight() / 2.f});

        m_uiLayer->addChild(f->feed, HIGHEST_Z);

        PlatformToolbox::showCursor();

        scheduleOnce(schedule_selector(NotifPlayLayer::showNewNotif), rng::generate(1.25f, 5.f));
    };

    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();

        toggleAll(true);
    };

    void showNewNotif(float) {
        auto notifRes = NotifManager::get()->getRandom();
        if (notifRes.isErr()) return;

        auto notif = std::move(notifRes).unwrap();

        auto x = m_uiLayer->getScaledContentWidth() / 2.f;

        auto notifNode = NotifNode::create(notif, false);
        notifNode->setScale(0.875f);

        auto y = m_uiLayer->getScaledContentHeight() + notifNode->getScaledContentHeight();
        auto yDown = m_uiLayer->getScaledContentHeight() - (0.625f * notifNode->getScaledContentHeight());

        notifNode->setPosition({x, y});

        notifNode->setCallback([this, notifNode](bool correct) {
            if (notifNode) notifNode->removeFromParent();
            if (!correct) resetLevelFromStart();
        });

        m_uiLayer->addChild(notifNode, HIGHEST_Z);

        notifNode->runAction(
            CCSequence::create(
                CCEaseExponentialOut::create(CCMoveTo::create(0.375f, {x, yDown})),
                CCDelayTime::create(rng::generate(2.5f, 3.75f)),
                CCEaseExponentialOut::create(CCMoveTo::create(0.375f, {x, y})),
                CCCallFuncN::create(this, callfuncN_selector(NotifPlayLayer::cleanNotif)),
                nullptr));

        if (auto fmod = FMODAudioEngine::sharedEngine()) (void)fmod->playEffectAsync("chest07.ogg");

        m_fields->feed->addNotif(notif, [this](bool correct) {
            if (!correct) resetLevelFromStart();
        });
    };

    void cleanNotif(CCNode* sender) {
        cue::resetNode(sender);

        queueInMainThread([self = WeakRef(this)]() {
            if (auto s = self.lock()) s->scheduleOnce(schedule_selector(NotifPlayLayer::showNewNotif), rng::generate(1.25f, 8.75f));
        });
    };
};
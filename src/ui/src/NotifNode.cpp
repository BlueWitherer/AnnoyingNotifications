#include "../NotifNode.h"

#include <cue/Util.hpp>

#include <Include.h>

#include <Geode/Geode.hpp>

#include <Geode/ui/Button.hpp>

using namespace geode::prelude;
using namespace cw::notifs;

bool NotifNode::init(const Notif* notif, bool withBtns) {
    if (!CCNode::init()) return false;

    setID(notif->getID());
    setAnchorPoint({0.5, 0.5});
    setContentSize({255.f, withBtns ? 75.f : 65.f});

    auto notifMsg = CCLabelBMFont::create(notif->getMessage().c_str(), "chatFont.fnt", getScaledContentWidth() - 65.f);
    notifMsg->setID("notif-msg");
    notifMsg->setScale(0.875f);
    notifMsg->setAnchorPoint({0, 1});

    addChild(notifMsg, 9);

    setContentHeight(getScaledContentHeight() + notifMsg->getScaledContentHeight());

    if (withBtns) {
        auto btnContainerLayout = RowLayout::create()
                                      ->setGap(2.5f)
                                      ->setAutoScale(false)
                                      ->setGrowCrossAxis(true);

        auto btnContainer = CCNode::create();
        btnContainer->setID("btn-container");
        btnContainer->setAnchorPoint({0.5, 0});
        btnContainer->setContentSize({getScaledContentWidth() * 0.925f, 50.f});
        btnContainer->setPosition({getScaledContentWidth() / 2.f, 15.f});
        btnContainer->setLayout(btnContainerLayout);

        for (auto const& btn : notif->getButtons()) {
            auto btnNode = Button::createWithNode(
                ButtonSprite::create(btn.text.c_str(), "geode.loader/mdFontB.fnt", "GJ_button_05.png"),
                [this, &btn](auto) {
                    unscheduleUpdate();
                    if (m_callback) m_callback(btn.isOk);
                });
            btnNode->setScale(0.75f);

            btnContainer->addChild(btnNode);
        };

        btnContainer->updateLayout();

        setContentHeight(getScaledContentHeight() + btnContainer->getScaledContentHeight());

        addChild(btnContainer);

        m_countdown = ProgressBar::create();
        m_countdown->setID("countdown");
        m_countdown->setScale(0.75f);
        m_countdown->setAnchorPoint({0.5, 0.5});
        m_countdown->setPosition({getScaledContentWidth() / 2.f, 7.5f});

        addChild(m_countdown, 1);

        scheduleUpdate();
    };

    cue::attachBackground(
        this,
        {
            .opacity = 255,
            .sidePadding = 1.25f,
            .texture = "GJ_square02.png",
            .zOrder = -1,
        });

    auto notifTitle = CCLabelBMFont::create(notif->getTitle().c_str(), "goldFont.fnt");
    notifTitle->setID("notif-title");
    notifTitle->setScale(0.5f);
    notifTitle->setAnchorPoint({0.5, 0.5});
    notifTitle->setPosition({getScaledContentWidth() / 2.f, getScaledContentHeight() - (notifTitle->getScaledContentHeight() * 0.75f)});

    addChild(notifTitle, 1);

    auto senderIcon = CCSprite::createWithSpriteFrameName(notif->getSender().getIcon().c_str());
    senderIcon->setID("sender-icon");
    senderIcon->setPosition({32.5f, getScaledContentHeight() - 47.5f});

    cue::rescaleToMatch(senderIcon, 42.5f);

    addChild(senderIcon, 9);

    auto senderName = CCLabelBMFont::create(notif->getSender().getName().c_str(), "bigFont.fnt");
    senderName->setID("sender-name");
    senderName->setScale(0.5f);
    senderName->setAnchorPoint({0, 0.5});
    senderName->setPosition({senderIcon->getPositionX() + (senderIcon->getScaledContentWidth() * 0.75f), senderIcon->getPositionY() + ((senderIcon->getScaledContentHeight() / 2.f) * 0.875f)});

    addChild(senderName, 1);

    notifMsg->setPosition({senderName->getPositionX(), senderName->getPositionY() - (senderName->getScaledContentHeight() * 0.75f)});

    return true;
};

void NotifNode::update(float dt) {
    m_time -= dt;

    if (m_time <= 0.f) {
        if (m_callback) m_callback(false);
        return unscheduleUpdate();
    };

    if (m_time < 0.f) m_time = 0.f;
    auto pct = (m_time / 8.75f) * 100.f;

    if (m_countdown) {
        m_countdown->updateProgress(pct);
        m_countdown->setFillColor(colors::fadeColor(pct));
    };
};

void NotifNode::setCallback(Callback&& callback) {
    m_callback = std::move(callback);
};

NotifNode* NotifNode::create(const Notif* notif, bool withBtns) {
    auto ret = new NotifNode();
    if (ret->init(notif, withBtns)) {
        ret->autorelease();
        return ret;
    };

    delete ret;
    return nullptr;
};
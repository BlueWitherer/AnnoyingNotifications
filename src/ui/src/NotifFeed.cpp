#include "../NotifFeed.h"

#include <cue/Util.hpp>

#include <Include.h>

#include <ui/NotifNode.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::notifs;

bool NotifFeed::init(float height) {
    if (!CCNode::init()) return false;

    setID("notif-feed"_spr);
    setAnchorPoint({1, 0.5});
    setContentSize({225.f, height});

    // yea ik whatever man
    m_mainLayer = CCLayer::create();
    m_mainLayer->ignoreAnchorPointForPosition(false);
    m_mainLayer->setContentSize(getScaledContentSize());
    m_mainLayer->setPosition(getScaledContentSize() / 2.f);

    addChild(m_mainLayer);

    cue::attachBackground(
        m_mainLayer,
        {
            .opacity = 255,
            .sidePadding = -2.5,
            .verticalPadding = -2.5f,
            .texture = "GJ_square04.png",
            .zOrder = -1,
        });

    auto label = CCLabelBMFont::create("Notifications", "goldFont.fnt");
    label->setID("feed-label");
    label->setScale(0.5f);
    label->setPosition({m_mainLayer->getScaledContentWidth() / 2.f, m_mainLayer->getScaledContentHeight() - 15.f});

    m_mainLayer->addChild(label, 1);

    m_list = ScrollLayer::create({m_mainLayer->getScaledContentWidth() - 25.f, height - 37.5f});
    m_list->setID("notif-list");
    m_list->ignoreAnchorPointForPosition(false);
    m_list->setAnchorPoint({0.5, 0});
    m_list->setPosition({m_mainLayer->getScaledContentWidth() / 2.f, 12.5f});

    m_list->m_contentLayer->setLayout(ScrollLayer::createDefaultListLayout(5.f));

    m_mainLayer->addChild(m_list, 9);

    m_list->m_contentLayer->updateLayout();

    auto listBg = cue::createBackground(
        m_list->getScaledContentSize(),
        {
            .id = "",
        });
    listBg->setAnchorPoint(m_list->getAnchorPoint());
    listBg->setPosition(m_list->getPosition());

    m_mainLayer->addChild(listBg);

    auto toggle = Button::createWithSpriteFrameName(
        "accountBtn_messages_001.png",
        [this](Button* sender) {
            m_showing = !m_showing;

            if (m_showing) m_mainLayer->setVisible(true);

            runAction(
                CCSequence::createWithTwoActions(
                    CCEaseSineOut::create(
                        CCMoveBy::create(0.5f, {getScaledContentWidth() * (m_showing ? -1.f : 1.f), 0.f})),
                    CallFuncExt::create([this]() {
                        if (!m_showing) m_mainLayer->setVisible(false);
                    })));

            if (auto spr = typeinfo_cast<CCSprite*>(sender->getDisplayNode())) spr->runAction(CCFadeTo::create(0.5f, m_showing ? 255 : 125));
        });
    toggle->setID("feed-toggle");
    toggle->setScale(0.875f);
    toggle->setPosition({-1.f * (toggle->getScaledContentWidth() * 0.625f), getScaledContentHeight() - (toggle->getScaledContentHeight() * 1.25f)});

    addChild(toggle, 9);

    return true;
};

void NotifFeed::addNotif(const Notif* notif, Callback&& cb) {
    auto node = NotifNode::create(notif);
    node->setScale(0.75f);

    node->setCallback([this, node, cb = std::move(cb)](bool correct) {
        cb(correct);

        node->removeFromParent();

        m_list->m_contentLayer->updateLayout();
        m_list->scrollToTop();
    });

    m_list->m_contentLayer->addChild(node);
    m_list->m_contentLayer->updateLayout();

    m_list->scrollToTop();
};

NotifFeed* NotifFeed::create(float height) {
    auto ret = new NotifFeed();
    if (ret->init(height)) {
        ret->autorelease();
        return ret;
    };

    delete ret;
    return nullptr;
};
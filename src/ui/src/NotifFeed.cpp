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
    setContentSize({200.f, height});

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

    auto toggleBtn = Button::createWithSpriteFrameName(
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
    toggleBtn->setID("toggle-feed");
    toggleBtn->setScale(0.875f);
    toggleBtn->setPosition({-1.f * (toggleBtn->getScaledContentWidth() * 0.625f), getScaledContentHeight() / 2.f});

    addChild(toggleBtn);

    m_countLabelBg = CCSprite::createWithSpriteFrameName("geode.loader/updates-multiple.png");
    m_countLabelBg->setScale(0.575f);
    m_countLabelBg->setPosition(toggleBtn->getPosition() + (toggleBtn->getScaledContentSize() * 0.475f));
    m_countLabelBg->setVisible(false);

    addChild(m_countLabelBg, 1);

    m_countLabel = CCLabelBMFont::create(utils::numToString(m_list->m_contentLayer->getChildrenCount()).c_str(), "geode.loader/mdFontB.fnt");
    m_countLabel->setID("notif-counter");
    m_countLabel->setPosition(m_countLabelBg->getPosition());
    m_countLabel->setVisible(false);

    cue::rescaleToMatch(m_countLabel, m_countLabelBg->getScaledContentHeight() * 0.375f);

    addChild(m_countLabel, 9);

    return true;
};

void NotifFeed::updateCountLabel() {
    auto count = m_list->m_contentLayer->getChildrenCount();

    if (m_countLabel) {
        m_countLabel->setString(utils::numToString(count).c_str());
        m_countLabel->setVisible(count > 0);
    };

    if (m_countLabelBg) m_countLabelBg->setVisible(count > 0);
};

void NotifFeed::addNotif(const Notif* notif, Callback&& cb) {
    auto node = NotifNode::create(notif);
    node->setScale(0.65f);

    node->setCallback([this, node, cb = std::move(cb)](bool correct) {
        cb(correct);

        node->removeFromParent();

        m_list->m_contentLayer->updateLayout();
        m_list->scrollToTop();

        updateCountLabel();
    });

    m_list->m_contentLayer->addChild(node);
    m_list->m_contentLayer->updateLayout();

    m_list->scrollToTop();

    updateCountLabel();
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
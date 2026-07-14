#include <Include.h>

#include <ui/NotifNode.h>

#include <Geode/Geode.hpp>

#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;
using namespace cw::notifs;

class $modify(NotifPlayLayer, PlayLayer) {
    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();

        auto notifRes = NotifManager::get()->getRandom();
        if (notifRes.isErr()) return;

        auto notifNode = NotifNode::create(std::move(notifRes).unwrap(), utils::random::generate<bool>());
        notifNode->setScale(0.875f);
        notifNode->setPosition(m_uiLayer->getScaledContentSize() / 2.f);

        notifNode->setCallback([this, notifNode](bool correct) {
            if (notifNode) notifNode->removeFromParent();
            if (!correct) resetLevelFromStart();
        });

        m_uiLayer->addChild(notifNode, HIGHEST_Z);

        PlatformToolbox::showCursor();
    };
};
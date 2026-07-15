#pragma once

#include <API.h>

#include <Geode/Geode.hpp>

class NotifFeed final : public cocos2d::CCNode {
    using Callback = geode::CopyableFunction<void(bool)>;

private:
    geode::ScrollLayer* m_list = nullptr;

    cocos2d::CCLabelBMFont* m_countLabel = nullptr;
    cocos2d::CCSprite* m_countLabelBg = nullptr;

    cocos2d::CCNode* m_mainLayer = nullptr;

    bool m_showing = true;

protected:
    bool init(float height);

    void updateCountLabel();

public:
    static NotifFeed* create(float height);

    void addNotif(const cw::notifs::Notif* notif, Callback&& cb);
};
#pragma once

#include <API.h>

#include <Geode/Geode.hpp>

class NotifNode final : public cocos2d::CCNode {
    using Callback = geode::Function<void(bool)>;

private:
    Callback m_callback = nullptr;

    geode::ProgressBar* m_countdown = nullptr;

    float m_maxTime = 0.f;
    float m_time = 0.f;

protected:
    bool init(const cw::notifs::Notif* notif, bool withBtns);

    void update(float dt);

public:
    static NotifNode* create(const cw::notifs::Notif* notif, bool withBtns = true);

    void setCallback(Callback&& callback);
};
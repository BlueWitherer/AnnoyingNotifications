#pragma once

#include <API.h>

#include <Geode/Geode.hpp>

class NotifNode final : public cocos2d::CCNode {
    using Callback = geode::Function<void(bool)>;

private:
    Callback m_callback = nullptr;

    geode::ProgressBar* m_countdown = nullptr;

    float m_time = geode::utils::random::generate(8.75f, 17.5f);

protected:
    bool init(const cw::notifs::Notif* notif, bool withBtns);

    void update(float dt);

public:
    static NotifNode* create(const cw::notifs::Notif* notif, bool withBtns = true);

    void setCallback(Callback&& callback);
};
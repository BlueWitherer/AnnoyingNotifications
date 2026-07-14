#pragma once

#include <API.h>

#include <Geode/Geode.hpp>

class NotifFeed final : public cocos2d::CCNode {
private:
    geode::ScrollLayer* m_list = nullptr;

protected:
    bool init(float height);

public:
    static NotifFeed* create(float height);
};
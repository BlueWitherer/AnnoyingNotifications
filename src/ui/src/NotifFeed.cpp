#include "../NotifFeed.h"

#include <cue/Util.hpp>

#include <Include.h>

#include <Geode/Geode.hpp>

#include <Geode/ui/Button.hpp>

using namespace geode::prelude;
using namespace cw::notifs;

bool NotifFeed::init(float height) {
    if (!CCNode::init()) return false;

    setID("notif-feed"_spr);
    setAnchorPoint({1, 0.5});
    setContentSize({275.f, height});

    cue::attachBackground(
        this,
        {
            .opacity = 255,
            .sidePadding = -2.5,
            .verticalPadding = -2.5f,
            .texture = "GJ_square04.png",
        });

    return true;
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
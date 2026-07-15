#pragma once

#include <ranges>

#include <API.h>

#include <cue/Util.hpp>

#include <Geode/ui/Button.hpp>

#define HIGHEST_Z cocos2d::CCScene::get()->getHighestChildZ() + 1

#define AN_HORRIBLE_ID "enable"_spr
static constexpr auto g_horribleID = AN_HORRIBLE_ID;

namespace rng = geode::utils::random;

namespace colors {
    inline constexpr cocos2d::ccColor3B red = {225, 75, 100};
    inline constexpr cocos2d::ccColor3B yellow = {250, 250, 25};
    inline constexpr cocos2d::ccColor3B green = {100, 255, 100};

    namespace internal {
        inline constexpr cocos2d::ccColor3B lerpColor(cocos2d::ccColor3B const& a, cocos2d::ccColor3B const& b, float t) noexcept {
            return {
                static_cast<GLubyte>(a.r + (b.r - a.r) * t),
                static_cast<GLubyte>(a.g + (b.g - a.g) * t),
                static_cast<GLubyte>(a.b + (b.b - a.b) * t),
            };
        };
    };

    inline constexpr cocos2d::ccColor3B fadeColor(float value) noexcept {
        if (value > 100.f) value = 100.f;
        if (value < 0.f) value = 0.f;

        if (value <= 50.0f) {
            auto t = value / 50.0f;
            return internal::lerpColor(red, yellow, t);
        } else {
            auto t = (value - 50.0f) / 50.0f;
            return internal::lerpColor(yellow, green, t);
        };
    };
};
#pragma once

#include "DLL.hpp"

namespace cw::notifs {
    struct CW_NOTIFS_API_DLL Sender final {
    private:
        std::string m_id;
        std::string m_name;
        std::string m_icon;

    protected:
        Sender(std::string id, std::string name, std::string icon);

    public:
        static Sender create(std::string id, std::string name, std::string icon);

        geode::ZStringView getID() const noexcept;
        geode::ZStringView getName() const noexcept;
        geode::ZStringView getIcon() const noexcept;
    };
};
#pragma once

#include "DLL.hpp"

#include "Notif.hpp"
#include "Sender.hpp"

#include <Geode/Result.hpp>

#include <Geode/utils/StringMap.hpp>

namespace cw::notifs {
    class CW_NOTIFS_API_DLL NotifManager final {
    private:
        geode::utils::StringMap<Notif> m_notifs;
        std::vector<Sender> m_senders;

    protected:
        NotifManager() = default;
        ~NotifManager() = default;

        NotifManager(const NotifManager&) = delete;
        NotifManager& operator=(const NotifManager&) = delete;

        NotifManager(NotifManager&&) = delete;
        NotifManager& operator=(NotifManager&&) = delete;

        geode::Result<const Sender*> getRandomSender() const noexcept;

    public:
        static NotifManager* get() noexcept;

        void add(Notif notif);
        void addSender(Sender sender);

        geode::Result<const Notif*> getRandom() noexcept;
    };
};
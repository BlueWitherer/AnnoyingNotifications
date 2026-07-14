#pragma once

#include "DLL.hpp"

#include "Sender.hpp"

#include <Geode/utils/function.hpp>
#include <Geode/utils/ZStringView.hpp>

namespace cw::notifs {
    struct CW_NOTIFS_API_DLL Notif final {
        struct Button final {
            std::string text;
            bool isOk = false;
        };

        using Callback = geode::Function<void(Notif const&, Button const&)>;

    private:
        std::string m_id;
        std::string m_title;
        const Sender* m_sender = nullptr;
        std::string m_message;
        std::vector<Button> m_buttons;

    protected:
        Notif(std::string id);

    public:
        static Notif create(std::string id);

        Notif& setTitle(std::string title);
        Notif& setSender(Sender const& sender);
        Notif& setMessage(std::string message);
        Notif& setButtons(std::vector<Button> buttons);

        Notif& addButton(Button button);

        geode::ZStringView getID() const noexcept;
        geode::ZStringView getTitle() const noexcept;
        Sender const& getSender() const noexcept;
        geode::ZStringView getMessage() const noexcept;
        std::span<const Button> getButtons() const noexcept;
    };
};
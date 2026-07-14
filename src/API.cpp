#include <API.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::notifs;

Sender::Sender(std::string id, std::string name, std::string icon) : m_id(std::move(id)), m_name(std::move(name)), m_icon(std::move(icon)) {};

ZStringView Sender::getID() const noexcept {
    return m_id;
};

ZStringView Sender::getName() const noexcept {
    return m_name;
};

ZStringView Sender::getIcon() const noexcept {
    return m_icon;
};

Sender Sender::create(std::string id, std::string name, std::string icon) {
    return Sender(std::move(id), std::move(name), std::move(icon));
};

Notif::Notif(std::string id) : m_id(std::move(id)) {};

Notif Notif::create(std::string id) {
    return Notif(std::move(id));
};

Notif& Notif::setTitle(std::string title) {
    m_title = std::move(title);
    return *this;
};

Notif& Notif::setSender(Sender const& sender) {
    m_sender = &sender;
    return *this;
};

Notif& Notif::setMessage(std::string message) {
    m_message = std::move(message);
    return *this;
};

Notif& Notif::setButtons(std::vector<Button> buttons) {
    m_buttons = std::move(buttons);
    return *this;
};

Notif& Notif::addButton(Button button) {
    m_buttons.push_back(std::move(button));
    return *this;
};

ZStringView Notif::getID() const noexcept {
    return m_id;
};

ZStringView Notif::getTitle() const noexcept {
    return m_title;
};

Sender const& Notif::getSender() const noexcept {
    return *m_sender;
};

ZStringView Notif::getMessage() const noexcept {
    return m_message;
};

std::span<const Notif::Button> Notif::getButtons() const noexcept {
    return m_buttons;
};

Result<const Sender*> NotifManager::getRandomSender() const noexcept {
    if (m_senders.empty()) return Err("No notification senders found");
    return Ok(&m_senders[utils::random::generate(0, m_senders.size())]);
};

void NotifManager::add(Notif notif) {
    std::string id = notif.getID();
    m_notifs.emplace(std::move(id), std::move(notif));
};

void NotifManager::addSender(Sender sender) {
    m_senders.push_back(std::move(sender));
};

Result<const Notif*> NotifManager::getRandom() noexcept {
    if (m_notifs.empty()) return Err("No notifications found");

    auto it = m_notifs.begin();
    std::advance(it, utils::random::generate(0, m_notifs.size()));

    auto senderRes = getRandomSender();
    if (senderRes.isErr()) return senderRes.asErr();

    auto& notif = it->second;
    notif.setSender(*std::move(senderRes).unwrap());

    return Ok(&notif);
};

NotifManager* NotifManager::get() noexcept {
    static auto inst = new (std::nothrow) NotifManager();
    return inst;
};
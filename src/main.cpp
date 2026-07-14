#include <Include.h>

#include <horrible/OptionalAPI.hpp>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::notifs;
using namespace horrible;

// yeah big n shit script idk
$on_mod(Loaded) {
    if (auto nm = NotifManager::get()) {
        nm->addSender(Sender::create("durr", "durr", "durr.png"_spr));
        nm->addSender(Sender::create("gordon", "gordon", "gordon.png"_spr));
        nm->addSender(Sender::create("homelander", "Homelander", "homelander.png"_spr));
        nm->addSender(Sender::create("joe", "joe", "joe.png"_spr));
        nm->addSender(Sender::create("kane", "Kane Parsons", "kane.png"_spr));
        nm->addSender(Sender::create("kermit", "Kermit", "kermit.png"_spr));
        nm->addSender(Sender::create("michael", "Michael Sphere", "michael.png"_spr));
        nm->addSender(Sender::create("patrice", "patrice", "patrice.png"_spr));

        nm->add(
            Notif::create("clogged")
                .setTitle("Messages")
                .setMessage("The toilet is overflowing again.")
                .setButtons(
                    {
                        {
                            .text = "Who are you?",
                            .isOk = false,
                        },
                        {
                            .text = "I can help!",
                            .isOk = true,
                        },

                        {
                            .text = "Leave me alone...",
                            .isOk = false,
                        },
                    }));

        nm->add(
            Notif::create("on_fire")
                .setTitle("Messages")
                .setMessage("The fridge caught fire! RUN! HELP! AAAAA")
                .setButtons(
                    {
                        {
                            .text = "what the hell",
                            .isOk = true,
                        },
                        {
                            .text = "How do you..?",
                            .isOk = false,
                        },
                        {
                            .text = "Pour rice on it!",
                            .isOk = true,
                        },
                        {
                            .text = "where is that damn vodka",
                            .isOk = false,
                        },
                        {
                            .text = "You're hallucinating.",
                            .isOk = false,
                        },
                    }));

        nm->add(
            Notif::create("still_there")
                .setTitle("Messages")
                .setMessage("hey bestie are you still there....?")
                .setButtons(
                    {
                        {
                            .text = "gtfo my room",
                            .isOk = false,
                        },
                        {
                            .text = "Sir, this is a Wendy's",
                            .isOk = true,
                        },
                        {
                            .text = "no",
                            .isOk = true,
                        },
                        {
                            .text = "i have diarrhea",
                            .isOk = true,
                        },
                    }));

        nm->add(
            Notif::create("lamb_sauce")
                .setTitle("News")
                .setMessage("where's the lamb sauce !!!")
                .setButtons(
                    {
                        {
                            .text = "uh",
                            .isOk = false,
                        },
                        {
                            .text = "um",
                            .isOk = false,
                        },
                        {
                            .text = "fart?",
                            .isOk = true,
                        },
                        {
                            .text = "where",
                            .isOk = false,
                        },
                        {
                            .text = "Ok",
                            .isOk = true,
                        },
                    }));

        nm->add(
            Notif::create("shoutout")
                .setTitle("Email")
                .setMessage("brooo i lov yur youube chanel can i have a shoutout")
                .setButtons(
                    {
                        {
                            .text = "NO",
                            .isOk = true,
                        },
                        {
                            .text = "NO",
                            .isOk = true,
                        },
                        {
                            .text = "NO",
                            .isOk = false,
                        },
                        {
                            .text = "NO",
                            .isOk = true,
                        },
                        {
                            .text = "NO",
                            .isOk = true,
                        },
                    }));

        nm->add(
            Notif::create("10_bucks")
                .setTitle("Messages")
                .setMessage("hey man i need like 10 bucks for something but its important i promise")
                .setButtons(
                    {
                        {
                            .text = "YES",
                            .isOk = false,
                        },
                        {
                            .text = "YES",
                            .isOk = false,
                        },
                        {
                            .text = "NO",
                            .isOk = true,
                        },
                        {
                            .text = "YES",
                            .isOk = false,
                        },
                        {
                            .text = "yeag",
                            .isOk = true,
                        },
                    }));
    };
};

$on_game(Loaded) {
    if (Loader::get()->isModLoaded("cubicstudios.horriblemenu")) {
        auto const opt = OptionV2{
            AN_HORRIBLE_ID,
            "Notification Spam",
            "Enable the annoying notification spam during gameplay.",
            "Annoying Notifications",
            SillyTier::High,
            true,
        };

        OptionManagerV2::registerOption(opt);
    };
};
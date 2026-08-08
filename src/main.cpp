#include <Include.h>

#include <horrible/OptionalAPI.hpp>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw::notifs;
using namespace horrible;

// yeah big ass source file
$on_mod(Loaded) {
    if (auto nm = NotifManager::get()) {
        nm->addSender(Sender::create("among", "aomong", "aomong.png"_spr));
        nm->addSender(Sender::create("bfdi", "BFDI Mouth", "bfdi.png"_spr));
        nm->addSender(Sender::create("boo", "Boo", "boo.png"_spr));
        nm->addSender(Sender::create("borb", "Borb", "borb.png"_spr));
        nm->addSender(Sender::create("david", "David", "david.png"_spr));
        nm->addSender(Sender::create("doggie", "Doggo!", "doggie.png"_spr));
        nm->addSender(Sender::create("durr", "durr", "durr.png"_spr));
        nm->addSender(Sender::create("evw", "Mr. Wilderman", "evw.png"_spr));
        nm->addSender(Sender::create("fish", "Fihh", "fish.png"_spr));
        nm->addSender(Sender::create("glungus", "Glungus", "glungus.png"_spr));
        nm->addSender(Sender::create("gordon", "gordon", "gordon.png"_spr));
        nm->addSender(Sender::create("happy", "Steam Happy", "happy.png"_spr));
        nm->addSender(Sender::create("henry", "Henry.", "henry.png"_spr));
        nm->addSender(Sender::create("homelander", "Homelander", "homelander.png"_spr));
        nm->addSender(Sender::create("jacksepticeye", "Spedicey", "jacksepticeye.png"_spr));
        nm->addSender(Sender::create("joe", "joe", "joe.png"_spr));
        nm->addSender(Sender::create("kane", "Kane Parsons", "kane.png"_spr));
        nm->addSender(Sender::create("kermit", "Kermit", "kermit.png"_spr));
        nm->addSender(Sender::create("lobotomy", "Lobotomy", "lobotomy.png"_spr));
        nm->addSender(Sender::create("markiplier", "mark", "mark.png"_spr));
        nm->addSender(Sender::create("michael", "Michael Sphere", "michael.png"_spr));
        nm->addSender(Sender::create("miku", "Miku..?", "miku.png"_spr));
        nm->addSender(Sender::create("moist", "Big Moist", "moist.png"_spr));
        nm->addSender(Sender::create("patrice", "patrice", "patrice.png"_spr));
        nm->addSender(Sender::create("roach", "dancin' roach", "roach.png"_spr));
        nm->addSender(Sender::create("robtop", "robert", "robtop.png"_spr));
        nm->addSender(Sender::create("sammelot", "sam", "sammelot.png"_spr));
        nm->addSender(Sender::create("smile", "Winning Smile.", "smile.png"_spr));
        nm->addSender(Sender::create("soggy", "Lil' Ole' Soggy", "soggy.png"_spr));
        nm->addSender(Sender::create("squid", "squid guy", "squid.png"_spr));
        nm->addSender(Sender::create("takis", "Takis..?", "takis.png"_spr));
        nm->addSender(Sender::create("tarsorado", "Tarsorado Demon", "tarsorado.png"_spr));
        nm->addSender(Sender::create("tiger", "Curious Tiger", "tiger.png"_spr));
        nm->addSender(Sender::create("vortrox", "diva youtuber", "vortrox.png"_spr));
        nm->addSender(Sender::create("yellow", "The Yellow One.", "yellow.png"_spr));

        nm->add(
            Notif::create("hi")
                .setTitle("Messages")
                .setMessage("hi")
                .setButtons(
                    {
                        {.text = "hello", .isOk = false},
                        {.text = "bye", .isOk = true},
                    }));

        nm->add(
            Notif::create("fridge")
                .setTitle("Security Alert")
                .setMessage("A login has been detected for your smart fridge.")
                .setButtons(
                    {
                        {.text = "uh", .isOk = false},
                        {.text = "self-destruct!", .isOk = true},
                        {.text = "factory reset!", .isOk = false},
                        {.text = "play tidal wave", .isOk = true},
                    }));

        nm->add(
            Notif::create("clogged")
                .setTitle("Messages")
                .setMessage("The toilet is overflowing again.")
                .setButtons(
                    {
                        {.text = "who are you", .isOk = false},
                        {.text = "I can help!", .isOk = true},

                        {.text = "Leave me alone...", .isOk = false},
                        {.text = "ugh", .isOk = true},
                    }));

        nm->add(
            Notif::create("on_fire")
                .setTitle("Messages")
                .setMessage("The fridge caught fire! RUN! HELP! AAAAA")
                .setButtons(
                    {
                        {.text = "what the hell", .isOk = true},
                        {.text = "How do you..?", .isOk = false},
                        {.text = "Pour rice on it!", .isOk = true},
                        {.text = "where is that damn vodka", .isOk = false},
                        {.text = "You're hallucinating.", .isOk = false},
                    }));

        nm->add(
            Notif::create("still_there")
                .setTitle("Messages")
                .setMessage("hey bestie are you still there....?")
                .setButtons(
                    {
                        {.text = "gtfo of my room!!!", .isOk = false},
                        {.text = "this is a Wendy's.", .isOk = true},
                        {.text = "no", .isOk = true},
                        {.text = "maybe...", .isOk = true},
                        {.text = "let me pee in peace...", .isOk = true},
                    }));

        nm->add(
            Notif::create("lamb_sauce")
                .setTitle("News")
                .setMessage("where's the lamb sauce !!!")
                .setButtons(
                    {
                        {.text = "uh", .isOk = false},
                        {.text = "um", .isOk = false},
                        {.text = "fart?", .isOk = true},
                        {.text = "where", .isOk = false},
                        {.text = "Ok", .isOk = true},
                    }));

        nm->add(
            Notif::create("shoutout")
                .setTitle("E-mail")
                .setMessage("brooo i lov yur youube chanel can i have a shoutout")
                .setButtons(
                    {
                        {.text = "NO", .isOk = true},
                        {.text = "NO", .isOk = true},
                        {.text = "NO", .isOk = false},
                        {.text = "NO", .isOk = true},
                        {.text = "NO", .isOk = true},
                    }));

        nm->add(
            Notif::create("10_bucks")
                .setTitle("Messages")
                .setMessage("hey man i need like 10 bucks for something but its important i promise")
                .setButtons(
                    {
                        {.text = "YES", .isOk = false},
                        {.text = "YES", .isOk = false},
                        {.text = "NO", .isOk = true},
                        {.text = "YES", .isOk = false},
                        {.text = "yeag", .isOk = true},
                    }));

        nm->add(
            Notif::create("yt_intro")
                .setTitle("YouTube")
                .setMessage("what's up everyone welcome back to...")
                .setButtons(
                    {
                        {.text = "geometry dash!!!", .isOk = true},
                        {.text = "the recent tab!!!", .isOk = true},
                        {.text = "minecraft", .isOk = false},
                        {.text = "the impossible game!", .isOk = true},
                        {.text = "osu", .isOk = false},
                    }));

        nm->add(
            Notif::create("whatsapp_scam")
                .setTitle("Phone")
                .setMessage("I have something important to tell you. Can you add me on WhatsApp?")
                .setButtons(
                    {
                        {.text = "Ok", .isOk = false},
                        {.text = "Sure!", .isOk = false},
                        {.text = "whar", .isOk = false},
                        {.text = "will there be cake", .isOk = true},
                        {.text = "NOOOO", .isOk = true},
                    }));

        nm->add(
            Notif::create("browser_history")
                .setTitle("E-mail")
                .setMessage("hi i accidentally sent ur search history in the globed discord... we still cool?")
                .setButtons(
                    {
                        {.text = "no", .isOk = true},
                        {.text = "no", .isOk = true},
                        {.text = "hell no", .isOk = true},
                        {.text = "get out", .isOk = true},
                        {.text = "i'm so done...", .isOk = false},
                    }));

        nm->add(
            Notif::create("local_weather")
                .setTitle("Weather")
                .setMessage("Local forecast: Moderate chance of a new Geometry Dash update.")
                .setButtons(
                    {
                        {.text = "Ok", .isOk = false},
                        {.text = "Okay", .isOk = false},
                        {.text = "how do i reply to this...", .isOk = true},
                        {.text = "the impossible game!", .isOk = true},
                    }));

        nm->add(
            Notif::create("math_homework")
                .setTitle("Calculator")
                .setMessage("hey man what's 2 + 2? i need to know for my math homework")
                .setButtons(
                    {
                        {.text = "what", .isOk = false},
                        {.text = "4.", .isOk = true},
                        {.text = "6...", .isOk = false},
                        {.text = "fish!", .isOk = true},
                        {.text = "Block", .isOk = true},
                    }));

        nm->add(
            Notif::create("geode_virus")
                .setTitle("System")
                .setMessage("ey man ur pc got a virus from geode i need ur credit card info to give a fix")
                .setButtons(
                    {
                        {.text = "ok!", .isOk = false},
                        {.text = "delete system32", .isOk = true},
                        {.text = "rm -rf /", .isOk = true},
                        {.text = "u can have this virus too", .isOk = true},
                        {.text = "Block", .isOk = false},
                    }));

        nm->add(
            Notif::create("cheating")
                .setTitle("Twitter")
                .setMessage("Saw your completion for The Nightmare. Did you bot it..?")
                .setButtons(
                    {
                        {.text = "yeah", .isOk = false},
                        {.text = "nuh uh", .isOk = true},
                        {.text = "i can explain...", .isOk = false},
                        {.text = "caught", .isOk = false},
                    }));

        nm->add(
            Notif::create("music_pirata")
                .setTitle("Spotify")
                .setMessage("your account got slimed for downloading songs illegaly!!!")
                .setButtons(
                    {
                        {.text = "download more", .isOk = false},
                        {.text = "pirate ytm", .isOk = true},
                        {.text = "i can explain...", .isOk = false},
                        {.text = "caught", .isOk = false},
                    }));

        nm->add(
            Notif::create("bad_video")
                .setTitle("YouTube")
                .setMessage("Your video made me die of sadness. I will report you for this.")
                .setButtons(
                    {
                        {.text = "no wait pls", .isOk = false},
                        {.text = "i will delete it!", .isOk = true},
                        {.text = "i must make an apology video...", .isOk = false},
                        {.text = "hide from channel", .isOk = true},
                        {.text = "ignore", .isOk = true},
                    }));

        nm->add(
            Notif::create("viral")
                .setTitle("TikTok")
                .setMessage("You've reached 10,000 likes on your video!")
                .setButtons(
                    {
                        {.text = "uh oh", .isOk = true},
                        {.text = "sell crypto", .isOk = false},
                        {.text = "promote gambling!", .isOk = false},
                        {.text = "go on vacation", .isOk = true},
                    }));

        nm->add(
            Notif::create("rejected_mod")
                .setTitle("Geode")
                .setMessage("Your mod was rejected for overuse of AI. Please do not submit \"TotallyAwesomeCryptoMiner\" again, just don't...")
                .setButtons(
                    {
                        {.text = "re-submit", .isOk = false},
                        {.text = "i shall depart", .isOk = true},
                        {.text = "i must make an apology video...", .isOk = false},
                        {.text = "pls?", .isOk = false},
                        {.text = "vibecode it again", .isOk = false},
                    }));

        nm->add(
            Notif::create("steam_scam")
                .setTitle("Steam")
                .setMessage("Is \"stupidsmelly_119\" your Steam account? I accidentally reported it.")
                .setButtons(
                    {
                        {.text = "NO!", .isOk = true},
                        {.text = "maybe...", .isOk = false},
                        {.text = "what's in it for me if i tell you?", .isOk = true},
                    }));

        nm->add(
            Notif::create("fifty_fifty")
                .setTitle("Notes")
                .setMessage("you have a 50% of responding to this incorrectly. but you also have a 50% chance of responding correctly!")
                .setButtons(
                    {
                        {.text = "ruh roh", .isOk = false},
                        {.text = "ruh roh", .isOk = true},
                    }));

        nm->add(
            Notif::create("mrbreast")
                .setTitle("Discord")
                .setMessage("bro 1.png 2.png 3.png 4.png ")
                .setButtons(
                    {
                        {.text = "count me in!", .isOk = false},
                        {.text = "ignore", .isOk = true},
                        {.text = "bro got hacked :skull:", .isOk = true},
                    }));
    };
};
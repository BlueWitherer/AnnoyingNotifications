#pragma once

#ifdef GEODE_IS_WINDOWS
#ifdef AnnoyingNotifications_EXPORTS
#define CW_NOTIFS_API_DLL __declspec(dllexport)
#else
#define CW_NOTIFS_API_DLL __declspec(dllimport)
#endif
#else
#ifdef AnnoyingNotifications_EXPORTS
#define CW_NOTIFS_API_DLL __attribute__((visibility("default")))
#else
#define CW_NOTIFS_API_DLL
#endif
#endif
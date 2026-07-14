#pragma once

#ifdef GEODE_IS_WINDOWS
#ifdef CW_NOTIFS_API_EXPORTING
#define CW_NOTIFS_API_DLL __declspec(dllexport)
#else
#define CW_NOTIFS_API_DLL __declspec(dllimport)
#endif
#else
#define CW_NOTIFS_API_DLL __attribute__((visibility("default")))
#endif
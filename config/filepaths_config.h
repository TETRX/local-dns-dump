#pragma once
#include <string>

#if GLOBAL
#define CACHE_PATH    "/var/cache/localdns/DnsMapCache.config"
#define SETTINGS_PATH "/etc/localdns/DnsMapUserSettings.config"
#define MAP_PATH      "/etc/localdns/DnsMapUser.config"
#else
#define CACHE_PATH    "config/DnsMapCache.config"
#define SETTINGS_PATH "config/DnsMapUserSettings.config"
#define MAP_PATH      "config/DnsMapUser.config"
#endif

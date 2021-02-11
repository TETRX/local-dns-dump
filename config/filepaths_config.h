#pragma once
#include <string>

#if GLOBAL
    const std::string CACHE_PATH="/var/cache/localdns/DnsMapCache.config";
    const std::string SETTINGS_PATH="/etc/localdns/DnsMapUserSettings.config";
    const std::string MAP_PATH="/etc/localdns/DnsMapUser.config";

#else
    const std::string CACHE_PATH="../config/DnsMapCache.config";
    const std::string SETTINGS_PATH="../config/DnsMapUserSettings.config";
    const std::string MAP_PATH="../config/DnsMapUser.config";
#endif

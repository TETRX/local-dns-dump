#pragma once
#include "../config/DnsMapUserSettings.h"
#include <string>


const std::string IFACE         = DnsMapUserSettings().get_setting(std::string("iface"));
const std::string IP_MASK       = DnsMapUserSettings().get_setting(std::string("ip_mask"));
const int         CACHE_TIMEOUT = std::stoi(DnsMapUserSettings().get_setting(std::string("cache_timeout")));

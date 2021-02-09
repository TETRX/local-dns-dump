#pragma once
#include "../config/DnsMapUserSettings.h"


const std::string iface = DnsMapUserSettings().get_setting(std::string("iface"));
const std::string PREFIX = DnsMapUserSettings().get_setting(std::string("prefix"));
const std::string MAC = "54:e0:19:62:e0:05";

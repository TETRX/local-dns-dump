#pragma once

#include <iostream>
#include <string>
#include "DnsMap.h"

class DnsMapUserSettings {
private:
    const std::string filename = "../config/DnsMapUserSettings.config";
    DnsMap dnsMap;

public:
    DnsMapUserSettings();

    std::string get_setting(std::string setting_name);
};
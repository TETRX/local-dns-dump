#pragma once

#include <string>
#include "DnsMap.h"

class DnsMapUserSettings {
private:
    DnsMap dnsMap;

public:
    DnsMapUserSettings();

    std::string get_setting(std::string setting_name);
};

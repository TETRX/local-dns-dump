#pragma once

#include <iostream>
#include "configUtils.h"

class configUtilsUser {
private:
    const std::string filename = "DnsMapUser";
    configUtils utils;

public:
    configUtilsUser();

    void updateEntry(const std::string &dns_name, const std::string &mac);

    std::string getMacFromDnsName(const std::string &dns_name);

    std::unordered_set<std::string> entries();
};
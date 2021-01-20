#pragma once

#include <iostream>
#include "configUtils.h"
#include "configUtilsUser.h"

class configUtilsCache {
private:
    const std::string filename = "DnsMapCache";
    configUtils utils;
public:
    configUtilsCache();

    void updateEntry(const std::string &dns_name, const std::vector<std::string> &attributes);

    // returns {ip, timestamp} vector
    std::vector<std::string> getIpAttributes(const std::string &dns_name);

    void synchronizeCacheWithUserConfig(configUtilsUser utilsUser);
};
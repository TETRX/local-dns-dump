#pragma once

#include <mutex>
#include "DnsMap.h"
#include "DnsMapUser.h"

class DnsMapCache {
private:
    DnsMap dnsMap;
    std::mutex m;
public:
    DnsMapCache();

    void updateEntry(const std::string &dns_name, const std::vector<std::string> &attributes);

    // returns {ip, timestamp} vector
    std::vector<std::string> getIpAttributes(const std::string &mac);

    void synchronizeCacheWithUserConfig(DnsMapUser& dnsMapUser);
};

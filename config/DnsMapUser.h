#pragma once

#include "DnsMap.h"

class DnsMapUser {
private:
    DnsMap dnsMap;

public:
    DnsMapUser();

    void updateEntry(const std::string &dns_name, const std::string &mac);

    std::string getMacFromDnsName(const std::string &dns_name);

    std::unordered_set<std::string> entries();
};

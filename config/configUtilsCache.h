#include <iostream>
#include "configUtils.h"

#define filename "DnsMapCache"

class configUtilsCache : configUtils {
public:
    configUtilsCache();

    void updateEntry(const std::string &dns_name, const std::vector<std::string> &attributes);

    // returns {ip, timestamp} vector
    std::vector<std::string> getIpAttributes(const std::string &dns_name);
};
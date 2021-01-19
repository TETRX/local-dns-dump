#include <iostream>
#include "configUtils.h"

class configUtilsCache : configUtils {
public:
    configUtilsCache();

    static void updateEntry(const std::string &dns_name, const std::vector<std::string> &attributes);

    // returns {ip, timestamp} vector
    std::vector<std::string> getIpAttributes(const std::string &dns_name);

    static void synchronizeCacheWithUserConfig();
};
#include "configUtilsCache.h"

void configUtilsCache::updateEntry(const std::string &dns_name, const std::vector<std::string> &cacheAttributes) {
    configUtils::updateEntry(dns_name, "", cacheAttributes);
}

std::vector<std::string> configUtilsCache::getIpAttributes(const std::string &dns_name) {
    return configUtils::getEntry(dns_name);
}

configUtilsCache::configUtilsCache() : configUtils(filename) {}
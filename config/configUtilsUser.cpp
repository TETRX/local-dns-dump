#include "configUtilsUser.h"

void configUtilsUser::updateEntry(const std::string &dns_name, const std::string &mac) {
    configUtils::updateEntry(USERFILE, dns_name, mac, {});
}

std::string configUtilsUser::getMacFromDnsName(const std::string &dns_name) {
    auto attributes = configUtils::getEntry(dns_name);
    if (attributes.empty()) {
        return "";
    }
    return attributes[0];
}

configUtilsUser::configUtilsUser() : configUtils(USERFILE) {}
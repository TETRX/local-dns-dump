#include "configUtilsUser.h"

void configUtilsUser::updateEntry(const std::string &dns_name, const std::string &mac) {
    utils.updateEntry(dns_name, {mac});
}

std::string configUtilsUser::getMacFromDnsName(const std::string &dns_name) {
    auto attributes = utils.getEntry(dns_name);
    if (attributes.empty()) {
        return "";
    }
    return attributes[0];
}

configUtilsUser::configUtilsUser() {
    utils.setFileName(this->filename);
}

std::unordered_set<std::string> configUtilsUser::entries() {
    return utils.entries();
}
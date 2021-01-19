#include <iostream>
#include "configUtils.h"

#define filename "DnsMapUser"

class configUtilsUser : configUtils {
public:
    configUtilsUser();

    void updateEntry(const std::string &dns_name, const std::string &mac);

    std::string getMacFromDnsName(const std::string &dns_name);
};
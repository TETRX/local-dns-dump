#include <iostream>
#include "configUtils.h"

class configUtilsUser : configUtils {
public:
    configUtilsUser();

    static void updateEntry(const std::string &dns_name, const std::string &mac);

    std::string getMacFromDnsName(const std::string &dns_name);
};
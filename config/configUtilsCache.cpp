#include <fstream>
#include "configUtilsCache.h"

void configUtilsCache::updateEntry(const std::string &dns_name, const std::vector<std::string> &cacheAttributes) {
    configUtils::updateEntry(CACHEFILE, dns_name, "", cacheAttributes);
}

std::vector<std::string> configUtilsCache::getIpAttributes(const std::string &dns_name) {
    return configUtils::getEntry(dns_name);
}

configUtilsCache::configUtilsCache() : configUtils(CACHEFILE) {}

void configUtilsCache::synchronizeCacheWithUserConfig() {
    auto user_dns_names = configUtils::updateEntry(USERFILE, "", "", {});

    std::string copyFileName = "copy" + CACHEFILE;
    createFile(copyFileName);
    std::ofstream copyFile;
    copyFile.open(copyFileName, std::ios_base::trunc);

    std::ifstream configFile(CACHEFILE);

    std::string line;
    std::vector<std::pair<std::string, std::vector<std::string>>> entries;

    while (getline(configFile, line)) {
        auto first_character = line.find_first_not_of(' ');
        if (first_character == std::string::npos || line[first_character] == '/' || line[first_character] == '{' ||
            line[first_character] == '}') {
            copyFile << line << std::endl;
            continue;
        }

        auto last_character = line.find_last_not_of(' ');
        if (line[last_character] == ',') {
            line = line.substr(0, last_character);
        }
        nlohmann::json j = nlohmann::json::parse("{" + line + "}");

        auto e = j.items().begin();
        if (user_dns_names.find(e.key()) == user_dns_names.end()) {
            continue;
        } else {
            std::vector<std::string> attributes = {e.value()[0], e.value()[1]};
            entries.emplace_back(e.key(), attributes);
        }
    }
    remove(CACHEFILE.c_str());
    rename(copyFileName.c_str(), CACHEFILE.c_str());

    for (const auto &entry: entries) {
        updateEntry(entry.first, entry.second);
    }
}
#include <fstream>
#include <thread>
#include "configUtilsCache.h"

void configUtilsCache::updateEntry(const std::string &mac, const std::vector<std::string> &cacheAttributes) {
    m.lock();
    utils.updateEntry(mac, cacheAttributes);
    m.unlock();
}

std::vector<std::string> configUtilsCache::getIpAttributes(const std::string &mac) {
    m.lock();
    auto entry = utils.getEntry(mac);
    m.unlock();
    return entry;
}

configUtilsCache::configUtilsCache() {
    utils.setFileName(filename);
}

void configUtilsCache::synchronizeCacheWithUserConfig(configUtilsUser utilsUser) {
    m.lock();
    auto mac_set = utilsUser.entries();

    std::string copyFileName = "copy" + filename;
    configUtils::createFile(copyFileName);
    std::ofstream copyFile;
    copyFile.open(copyFileName, std::ios_base::trunc);

    std::ifstream configFile(filename);

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
        if (mac_set.find(e.key()) == mac_set.end()) {
            continue;
        } else {
            std::vector<std::string> attributes = {e.value()[0], e.value()[1]};
            entries.emplace_back(e.key(), attributes);
        }
    }
    remove(filename.c_str());
    rename(copyFileName.c_str(), filename.c_str());

    for (const auto &entry: entries) {
        updateEntry(entry.first, entry.second);
    }
    m.unlock();
}
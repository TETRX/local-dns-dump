#include <fstream>
#include "configUtils.h"

#define LINE_PADDING 4

std::string configUtils::prettifyLine(std::string line, bool insertComma) {
    line = line.substr(1); // remove first {
    line = line.substr(0, line.length() - 1); // remove last }
    line.insert(0, LINE_PADDING, ' '); // add extra padding
    if (insertComma) {
        line += ',';
    }
    return line;
}

void configUtils::createFile(const std::string &name) {
    if (std::ifstream(name)) { // check if file already exists
        return;
    }
    std::ofstream file(name);
    file << "{\n}";
}

configUtils::configUtils(const std::string &filename) : filename(filename) {
    createFile(filename);
}

void configUtils::updateEntry(const std::string &dns_name, const std::string &mac,
                              const std::vector<std::string> &cacheAttributes) {
    std::string copyFileName = "copy" + filename;
    createFile(copyFileName);
    std::ofstream copyFile;
    copyFile.open(copyFileName, std::ios_base::trunc);

    std::ifstream configFile(filename);

    std::string line;
    bool dnsUpdated = false; // indicate whether dns_name is a new entry

    while (getline(configFile, line)) {
        auto first_character = line.find_first_not_of(' ');
        if (first_character == std::string::npos || line[first_character] == '/' || line[first_character] == '{') {
            copyFile << line << std::endl;
            continue;
        }

        if (line[first_character] == '}') {
            if (dnsUpdated) {
                copyFile << line << std::endl;
            } else { // append new dns pair
                nlohmann::json j;
                if (mac.length() == 0) {
                    j = {{dns_name, cacheAttributes}};
                } else {
                    j = {{dns_name, {mac}}};
                }

                copyFile << prettifyLine(j.dump(), false) << std::endl;
                copyFile << line << std::endl;
            }
            continue;
        }

        auto last_character = line.find_last_not_of(' ');
        bool hasEndComma = false;
        if (line[last_character] == ',') {
            hasEndComma = true;
            line = line.substr(0, last_character);
        }
        nlohmann::json j = nlohmann::json::parse("{" + line + "}");

        auto e = j.items().begin();
        if (e.key() == dns_name) {
            if (mac.length() == 0) {
                j[e.key()] = cacheAttributes;
            } else {
                j[e.key()] = {mac};
            }
            dnsUpdated = true;
        }

        copyFile << prettifyLine(j.dump(), hasEndComma || !dnsUpdated) << std::endl;
    }

    remove(filename.c_str());
    rename(copyFileName.c_str(), filename.c_str());
}


std::vector<std::string> configUtils::getEntry(const std::string &dns_name) {
    std::ifstream inputFile(filename);
    nlohmann::json j = nlohmann::json::parse(inputFile, nullptr, true, true);
    if (j.contains(dns_name)) {
        return j[dns_name];
    }

    return {};
}
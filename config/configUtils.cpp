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

configUtils::configUtils() {
    createFile(this->filename);
}

void configUtils::createFile(const std::string &name) {
    if (std::ifstream(name)) { // check if file already exists
        return;
    }
    std::ofstream file(name);
    file << "{\n}";
}

void configUtils::updateEntry(const std::string &dns_name, const std::vector<std::string> &attributes) {
    std::string copyFileName = "copy" + this->filename;
    createFile(copyFileName);
    std::ofstream copyFile;
    copyFile.open(copyFileName, std::ios_base::trunc);

    std::ifstream configFile(this->filename);

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
                nlohmann::json j = {{dns_name, attributes}};
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
            j[e.key()] = attributes;
            dnsUpdated = true;
        }

        copyFile << prettifyLine(j.dump(), hasEndComma || !dnsUpdated) << std::endl;
    }

    remove(this->filename.c_str());
    rename(copyFileName.c_str(), this->filename.c_str());
}

std::vector<std::string> configUtils::getEntry(const std::string &dns_name) {
    std::ifstream inputFile(this->filename);
    nlohmann::json j = nlohmann::json::parse(inputFile, nullptr, true, true);
    if (j.contains(dns_name)) {
        return j[dns_name];
    }

    return {};
}
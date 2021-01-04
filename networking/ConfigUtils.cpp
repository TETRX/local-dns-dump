#include <fstream>
#include "ConfigUtils.h"

#define LINE_PADDING 4

string ConfigUtils::prettifyLine(string line, bool insertComma) {
    line = line.substr(1); // remove first {
    line = line.substr(0, line.length() - 1); // remove last }
    line.insert(0, LINE_PADDING, ' '); // add extra padding
    if (insertComma) {
        line += ',';
    }
    return line;
}

ConfigUtils::ConfigUtils() {
    createFile(this->filename);
}

void ConfigUtils::createFile(const string &name) {
    if (ifstream(name)) { // check if file already exists
        return;
    }
    ofstream file(name);
    file << "{\n}";
}

void ConfigUtils::addEntry(const string &dns_name, const string &mac) {
    string copyFileName = "copy" + this->filename;
    createFile(copyFileName);
    ofstream copyFile;
    copyFile.open(copyFileName, ios_base::trunc);

    ifstream configFile(this->filename);

    string line;
    bool dnsUpdated = false; // indicate whether dns_name is a new entry

    while (getline(configFile, line)) {
        auto first_character = line.find_first_not_of(' ');
        if (first_character == std::string::npos || line[first_character] == '/' || line[first_character] == '{') {
            copyFile << line << endl;
            continue;
        }

        if (line[first_character] == '}') {
            if (dnsUpdated) {
                copyFile << line << endl;
            } else { // append new dns pair
                nlohmann::json j = {{dns_name, mac}};
                copyFile << prettifyLine(j.dump(), false) << endl;
                copyFile << line << endl;
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
            j[e.key()] = mac;
            dnsUpdated = true;
        }

        copyFile << prettifyLine(j.dump(), hasEndComma || !dnsUpdated) << endl;
    }

    remove(this->filename.c_str());
    rename(copyFileName.c_str(), this->filename.c_str());
}

bool ConfigUtils::isDnsNameInMap(const string &dns_name) {
    ifstream inputFile(this->filename);
    nlohmann::json j = nlohmann::json::parse(inputFile, nullptr, true, true);
    return j[dns_name] != nullptr;
}
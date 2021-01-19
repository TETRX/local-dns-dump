#include <iostream>
#include <unordered_map>
#include <vector>
#include "../lib/nlohmann/json.hpp"

class configUtils {
private:
    const std::string filename = "DnsMapConfig";

    static void createFile(const std::string &filename);

    static std::string prettifyLine(std::string line, bool insertComma);

public:
    configUtils();

    void updateEntry(const std::string &dns_name, const std::vector<std::string> &attributes);

    // returns vector (possibly empty) with all attributes [MAC, (optional) IP, (optional) timestamp]
    std::vector<std::string> getEntry(const std::string &dns_name);
};
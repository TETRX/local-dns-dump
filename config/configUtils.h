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

    void addEntry(const std::string &dns_name, const std::string &mac);

    bool isDnsNameInMap(const std::string &dns_name);
};
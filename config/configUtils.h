#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "../lib/nlohmann/json.hpp"


const std::string USERFILE = "DnsMapUser";
const std::string CACHEFILE = "DnsMapCache";

class configUtils {
private:
    const std::string filename;

protected:

    static void createFile(const std::string &filename);

    static std::string prettifyLine(std::string line, bool insertComma);

    static std::unordered_set<std::string>
    updateEntry(const std::string &file, const std::string &dns_name, const std::string &mac,
                const std::vector<std::string> &cacheAttributes);

    std::vector<std::string> getEntry(const std::string &dns_name);

public:
    configUtils() = default;

    configUtils(const std::string &filename);
};
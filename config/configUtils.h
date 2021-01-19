#include <iostream>
#include <unordered_map>
#include <vector>
#include "../lib/nlohmann/json.hpp"

class configUtils {
private:
    const std::string filename;
protected:

    static void createFile(const std::string &filename);

    static std::string prettifyLine(std::string line, bool insertComma);

    void
    updateEntry(const std::string &dns_name, const std::string &mac, const std::vector<std::string> &cacheAttributes);

    std::vector<std::string> getEntry(const std::string &dns_name);

public:
    configUtils() = default;

    configUtils(const std::string &filename);
};
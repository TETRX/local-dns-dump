#include <iostream>
#include <unordered_map>
#include <vector>
#include "../lib/nlohmann/json.hpp"

using namespace std;

class ConfigUtils {
private:
    const string filename = "DnsMapConfig";

    static void createFile(const string &filename);

    static string prettifyLine(string line, bool insertComma);

public:
    ConfigUtils();

    void addEntry(const string &dns_name, const string &mac);

    bool isDnsNameInMap(const string &dns_name);
};
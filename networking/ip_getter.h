// IPGetter isolates the entire local-dns algorithm
#include <string>
#include <map>
#include <utility>
#include <future>

#include "requester.h"
#include "replier.h"
#include "../config/DnsMapCache.h"

class IPGetter
{
private:
    std::string local_network_ip_prefix; //Something like "192.168.0."
    Requester *requester;
 
    std::map<std::string, std::promise<std::string>*>* map;
    std::mutex& map_lock;
    Replier *replier;

    int timeout; //in miliseconds

    DnsMapCache cache;

    std::string wait_for_promise(std::promise<std::string>& promise);
public:
    std::string get_ip(std::string mac); //This is the API the rest of the program has to call in order to invoke local-dns for a certain mac address
    
    IPGetter(Requester *requester1, Replier *replier1, DnsMapUser dnsMapUser, std::string local_network_ip_prefix1="192.168.0.", int timeout1=1000) : requester(requester1), replier(replier1), map(&replier1->map), map_lock(replier1->map_lock), local_network_ip_prefix(local_network_ip_prefix1), timeout(timeout1) {
        cache.synchronizeCacheWithUserConfig(dnsMapUser);
    }
};


// IPGetter isolates the entire local-dns algorithm
#include "requester.h"
#include "replier.h"
#include <string>

class IPGetter
{
private:
    std::string local_network_ip_prefix; //Something like "192.168.0."
    Requester *requester;

    
    std::map<std::string, std::promise<std::string>*>* map;
    std::mutex& map_lock;
    Replier *replier;

    int timeout; //in miliseconds

    void request_a_lot(std::string mac);
    std::string request_a_lot_single(std::string mac); // (temp) single-thread brute-force

    std::string wait_for_promise(std::promise<std::string>& promise);
public:
    std::string get_ip(std::string mac); //This is the API the rest of the program has to call in order to invoke local-dns for a certain mac address
    IPGetter(Requester *requester1, Replier *replier1, std::map<std::string, std::promise<std::string>*>* map1,std::mutex& map_lock1 ,std::string local_network_ip_prefix1="192.168.0.", int timeout1=1000):map_lock(map_lock1), local_network_ip_prefix(local_network_ip_prefix1), timeout(timeout1) {
        replier=replier1;
        map=map1;
        requester=requester1;
        replier=replier1;
    }
};


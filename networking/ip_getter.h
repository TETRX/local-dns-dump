// IPGetter isolates the entire local-dns algorithm
#include "requester.h"
#include <string>

class IPGetter
{
private:
    std::string local_network_ip_prefix; //Something like "192.168.0."
    Requester *requester;
public:
    std::string get_ip(std::string mac); //This is the API the rest of the program has to call in order to invoke local-dns for a certain mac address
    IPGetter(Requester *requester1, std::string local_network_ip_prefix1="192.168.0."): local_network_ip_prefix(local_network_ip_prefix1) {
        requester=requester1;
    }
    ~IPGetter();
};


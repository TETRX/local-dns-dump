#include "requester.h"

class ArpingRequester: public Requester
{   
    public:
        virtual std::string request(std::string ip_mask, std::string mac_requested); 

};
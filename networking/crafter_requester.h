#include "requester.h"
#include "config.h"
#include "../lib/blocking_queue.h"
#include <crafter.h>

class CrafterRequester: public Requester
{  
	private:
        std::string myIP;
        std::string myMAC;

        Crafter::Ethernet ethernetHeaderTemplate;
        Crafter::ARP arpHeaderTemplate;

        BlockingQueue<std::pair<std::string, std::string>> requests;

        void listen_for_requests();
    
	public:
		CrafterRequester();
            
        virtual void request(std::string ip_mask, std::string mac_requested); 
};

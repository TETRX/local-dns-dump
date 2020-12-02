#include "requester.h"

extern "C" {
	#include "arping.h" // same
	#include "../local_dns/src/arping_libnet_context.h" // same
}

class ArpingRequester: public Requester
{  
	private:
		struct arping_libnet_context context;	
    
	public:
		ArpingRequester() {
			// TODO: add constructor argument - number of arping request retries
			arping_libnet_init(&context);
		}
		~ArpingRequester() {
			// TODO: libnet_destroy(context.libnet)
		}
        virtual void request(std::string ip_mask, std::string mac_requested); 
        virtual std::string request_instant(std::string ip_mask, std::string mac_requested); 

};

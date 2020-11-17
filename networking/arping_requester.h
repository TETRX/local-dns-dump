#include "requester.h"

extern "C" {
	#include "arping.h" // same
	#include "../local_dns/src/arping_init.h" // same
}

class ArpingRequester: public Requester
{  
	private:
		struct arping_context context;	
    
	public:
		ArpingRequester() {
			// TODO: add constructor argument - number of arping request retries
			arping_init(&context);
		}
		~ArpingRequester() {
			// TODO: libnet_destroy(context.libnet)
		}
        	virtual std::string request(std::string ip_mask, std::string mac_requested); 

};

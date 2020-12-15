#include "requester.h"
#include "arping_context.h"
#include "../lib/blocking_queue.h"

class ArpingRequester: public Requester
{  
	private:
		ArpingContext * context;
        BlockingQueue<std::pair<std::string, std::string>> requests;

        void listen_for_requests();
    
	public:
		ArpingRequester(ArpingContext * context1) : Requester(), context(context1) {
            listen_for_requests();
		}
        virtual void request(std::string ip_mask, std::string mac_requested); 
};

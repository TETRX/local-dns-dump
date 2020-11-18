#include "listener.h"

extern "C" {
	#include "arping.h" // same
	#include "../local_dns/src/arping_pcap_context.h"
}

class ArpingListener: public Listener
{  
	private:
		struct arping_pcap_context context;	
    
	public:
		ArpingListener() {
			arping_pcap_init(&context);
		}
		~ArpingListener() {
			// TODO: pcap_close(context.pcap)
		}
        virtual bool listen(std::pair<std::string, std::string>* out);

};

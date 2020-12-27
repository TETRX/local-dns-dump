#include "listener.h"
#include "config.h"
#include <string>
#include <crafter.h>
#include "../lib/blocking_queue.h"

class CrafterListener: public Listener
{
    friend void packet_handler_wrapper(Crafter::Packet*, void*);
    private:
        BlockingQueue<std::pair<std::string, std::string>> replies;
        Crafter::Sniffer sniffer;

        void packet_handler(Crafter::Packet *packet);
    
	public:
        CrafterListener();
        virtual bool listen(std::pair<std::string, std::string>* out);
};

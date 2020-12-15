#pragma once

#include <string>

extern "C" {
	#include "arping.h" // same
	#include "../local_dns/src/arping_context.h" // same
}

class ArpingContext {
    struct arping_context context;

    public:
        ArpingContext() {
            arping_libnet_init(&context);
            arping_pcap_init(&context);
        }
        ~ArpingContext() {
            // libnet_destroy(context->libnet);
            // pcap_close(context->pcap);
        }
        
        bool send(const std::string& ip_mask, const std::string& mac);
        bool recv(std::string& mac, std::string& ip);
};

#ifndef ARPING_CONTEXT_H
#define ARPING_CONTEXT_H
#include <sys/types.h>
struct libnet_t;
struct pcap_t;

struct arping_context {
	libnet_t * libnet;
    pcap_t * pcap;
	
    ssize_t payload_suffix_size;
	char* payload_suffix;
    int fd;
};
#endif

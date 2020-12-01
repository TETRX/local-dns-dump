#include <sys/types.h>
struct libnet_t;
struct arping_libnet_context {
	libnet_t * libnet;
	ssize_t payload_suffix_size;
	char* payload_suffix;
};


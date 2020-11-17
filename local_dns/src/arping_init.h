#include <sys/types.h>
struct libnet_t;
struct arping_context {
	libnet_t * libnet;
	ssize_t payload_suffix_size;
	char* payload_suffix;
};

void do_libnet_init(struct arping_context *context, const char *ifname, int recursive);

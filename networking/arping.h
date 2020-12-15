#include <stdint.h>
struct arping_context;

int arping_libnet_init(struct arping_context *context);
int arping_pcap_init(struct arping_context *context);

int arping_send(struct arping_context *context, const char *ip_mask, const char *mac);
int arping_recv(struct arping_context *context, char *mac, uint32_t* ip);

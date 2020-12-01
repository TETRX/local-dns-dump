#include <stdint.h>
struct arping_libnet_context;
struct arping_pcap_context;

int arping_libnet_init(struct arping_libnet_context *context);
int arping_pcap_init(struct arping_pcap_context *context);

int arping_send();
int arping_recv();

int get_ip_local(struct arping_context *context, const char* ip_mask, const char* mac, uint32_t* out_ip);

#include <stdint.h>
struct arping_context;

int arping_init(struct arping_context *context);
int get_ip_local(struct arping_context *context, const char* ip_mask, const char* mac, uint32_t* out_ip);

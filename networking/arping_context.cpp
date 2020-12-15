#include "arping_context.h"

#if HAVE_CONFIG_H
#include "../local_dns/config.h" // consider copying this file in networking/
#endif

#if HAVE_STDINT_H
#include <stdint.h>
#endif

#if HAVE_INTTYPES_H
#include <inttypes.h>
#endif


static std::string ip_addr2str(uint32_t addr) {
	uint8_t a, b, c, d;
	a = (addr & 0xff);
	b = (addr & 0xff00) >> 8;
	c = (addr & 0xff0000) >> 16;
	d = (addr & 0xff000000) >> 24;

	return std::to_string(a) + '.' + std::to_string(b) + '.' + std::to_string(c) + '.' + std::to_string(d);
}


bool ArpingContext::send(const std::string& ip_mask, const std::string& mac) {
    return arping_send(&context, ip_mask.c_str(), mac.c_str()) > 0;
}

bool ArpingContext::recv(std::string& mac, std::string& ip_str) {
    mac.resize(17, 0);
    uint32_t ip;
    int result = arping_recv(&context, const_cast<char*>(mac.c_str()), &ip);
    if (result) ip_str = ip_addr2str(ip);
    return result > 0;
}

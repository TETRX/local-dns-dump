#include "arping_requester.h"
#include "no_response_exception.h"
#include <string>
#include <iostream>

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

std::string ArpingRequester::request(std::string ip_mask, std::string mac_requested){
    uint32_t ip;
    if (get_ip_local(&context, ip_mask.c_str(), mac_requested.c_str(), &ip)) {
	return ip_addr2str(ip);
    } else {
	throw NoResponseException();
    }
}

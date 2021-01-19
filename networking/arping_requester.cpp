#include "arping_requester.h"
#include <string>
#include <iostream>
#include <thread>

#if HAVE_CONFIG_H
#include "../local_dns/config.h" // consider copying this file in networking/
#endif

void ArpingRequester::request(std::string ip_mask, std::string mac_requested){
	requests.push(make_pair(ip_mask, mac_requested));
}

void ArpingRequester::listen_for_requests() {
    std::thread([this]() {
        while (true) {
            auto request = this->requests.pop();
            std::string ipMask = request.first;
            std::string mac = request.second;
            size_t pos;
            if ((pos = ipMask.find('*')) == std::string::npos) {
                this->context->send(ipMask, mac);
            } else {
                for (int i = 0; i < 256; i++) {
                    ipMask.replace(pos, ipMask.length() - pos, std::to_string(i));
                    this->context->send(ipMask, mac);
                }
            }
        }
    }).detach();
}

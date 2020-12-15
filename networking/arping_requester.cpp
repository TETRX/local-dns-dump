#include "arping_requester.h"
#include "no_response_exception.h"
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
            this->context->send(request.first, request.second);
        }
    }).detach();
}

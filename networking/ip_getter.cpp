#include <vector>
#include <map>
#include <future>
#include <thread>
#include <functional>
#include <utility>
#include <iostream>

#include "ip_getter.h"

std::string IPGetter::wait_for_promise(std::promise<std::string>& promise){
    auto future = promise.get_future();
    auto status = future.wait_for(std::chrono::milliseconds(timeout));
    if (status == std::future_status::timeout) {
        return "";
    }
    else {
        return future.get();
    }
}

std::string IPGetter::get_ip(std::string mac){
    std::cout << "Request: MAC=" << mac << std::endl;
    std::promise<std::string> result;
    std::pair<std::map<std::string, std::promise<std::string>*>::iterator, bool> entry;
    {
	    std::lock_guard<std::mutex> guard(map_lock);
    	entry = map->emplace(mac, &result);
    }
    requester->request(local_network_ip_prefix + "*", mac);
    std::string resultIP = wait_for_promise(result);
    return resultIP;   
}

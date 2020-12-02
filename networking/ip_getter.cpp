#include <vector>
#include <map>
#include <future>
#include <thread>
#include <functional>
#include <utility>

#include "ip_getter.h"
#include "no_response_exception.h"


void IPGetter::request_a_lot_single(std::string mac) {
	for (int i = 0; i < 255; i++) {
		const int i_cp(i);
		const std::string ip = local_network_ip_prefix + std::to_string(i_cp);
		requester->request(ip, mac);
		/*try {
			return requester_local->request_instant(ip, mac);
		} catch (NoResponseException e) {}*/
	}
	//return "";
}


void IPGetter::request_a_lot(std::string mac){
    std::vector<std::function<void()>> requests;
    Requester *requester_local=requester;
    for(int i=0;i<255;i++){
        const int i_cp(i);
        const std::string ip = local_network_ip_prefix+std::to_string(i_cp);
        requests.push_back([ip,mac,requester_local](){
        	requester_local->request(ip,mac);
        });
    }    
    for(auto request: requests){
        std::thread(request).detach();
    }
    
}

std::string IPGetter::wait_for_promise(std::promise<std::string>& promise){
    auto future = promise.get_future();
    auto status = future.wait_for(std::chrono::milliseconds(timeout));
    if (status==std::future_status::timeout) {
        return "";
    }
    else {
        return future.get();
    }
}

std::string IPGetter::get_ip(std::string mac){
    std::promise<std::string> result;
    std::pair<std::map<std::string, std::promise<std::string>*>::iterator, bool> entry;
    {
	std::lock_guard<std::mutex> guard(map_lock);
    	entry = map->emplace(mac, &result);
    }
    requester->request(local_network_ip_prefix+"255",mac);
    std::string broadcast_only = wait_for_promise(result);
    if(broadcast_only!=""){
        return broadcast_only;
    }
    result = std::promise<std::string>();
    entry.first->second = &result;
    request_a_lot_single(mac);
    std::string all_requests = wait_for_promise(result);
    return all_requests;
}

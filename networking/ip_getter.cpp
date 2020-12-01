#include "ip_getter.h"
#include "no_response_exception.h"
#include <vector>
#include <future>
#include <thread>


void IPGetter::request_a_lot(std::string mac){
    std::vector<std::function<std::string()>> requests;
    Requester *requester_local=requester;
    for(int i=0;i<255;i++){
        const int i_cp(i);
        const std::string ip = local_network_ip_prefix+std::to_string(i_cp);
        requests.push_back([ip,mac,requester_local](){
            try{
                return requester_local->request(ip,mac);      
            }
            catch(NoResponseException no_response){
                return std::string("");
            }
        });
    }    
    for(auto request: requests){
        std::thread(request).detach();
    }
    
}

std::string IPGetter::wait_for_promise(std::promise<std::string>& promise){
    auto future = promise.get_future();
    auto status = future.wait_for(std::chrono::milliseconds(timeout));
    if(status==std::future_status::timeout){
        return "";
    }
    else {
        return future.get();
    }
}

std::string IPGetter::get_ip(std::string mac){
    std::promise<std::string> result;
    map_lock.lock();
    map->emplace(&result);
    map_lock.unlock();
    requester->request(local_network_ip_prefix+"255",mac);
    std::string broadcast_only = wait_for_promise(result);
    if(broadcast_only!=""){
        return broadcast_only;
    }
    request_a_lot(mac);
    std::string all_requests = wait_for_promise(result);
    return all_requests;
}

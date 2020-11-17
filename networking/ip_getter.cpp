#include "ip_getter.h"
#include "no_response_exception.h"
#include <vector>
#include <future>
#include <thread>
#include <iostream>


std::string IPGetter::request_a_lot(std::string mac){
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
    std::vector<std::shared_future<std::string>> futures;
    for(auto& request: requests){
        std::shared_future<std::string> future = std::async(std::launch::async, request);
        futures.push_back(future);
    }
    int i=0;
    for(auto& future: futures){
        future.wait();
    }
    for(auto& future:futures){
        std::string result = future.get();
        // std::cout << result << std::endl;
        if(result!=""){
            return result;
        }
    }
    return "";
}

std::string IPGetter::get_ip(std::string mac){
    try{
        std::string ip=requester->request(local_network_ip_prefix+"255", mac);
        return ip;
    }
    catch(NoResponseException no_response){
        return request_a_lot(mac);
    }
}

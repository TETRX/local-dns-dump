#include "ip_getter.h"
#include "no_response_exception.h"
#include <vector>
#include <future>
#include <thread>

std::string IPGetter::get_ip(std::string mac){
    try{
        std::string ip=requester->request(local_network_ip_prefix+"255",mac);
        return ip;
    }
    catch(NoResponseException no_response){
        //TODO: fill in
    }
}
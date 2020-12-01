#include "replier.h"

void Replier::reply(){
    std::pair<std::string,std::string> reply;
    while(true){
        reply=listener->listen();
        std::string mac=reply.first, IP=reply.second;
        map_lock.lock();
        auto promise = map->find(mac);
        if(promise!=map->end()){
            promise->second->set_value(IP);
        }
        map->erase(promise);
        map_lock.unlock();
    }
}
#include "replier.h"

void Replier::reply() {
    std::pair<std::string,std::string> reply;
    while (true) {
        if (listener->listen(&reply)) {
        	std::string mac=reply.first, IP=reply.second;
		std::lock_guard<std::mutex> guard(map_lock);
		auto promise = map->find(mac);
        	if(promise!=map->end()){
           		promise->second->set_value(IP);
            		map->erase(promise);
        	}
	}
    }
}

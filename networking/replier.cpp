#include <thread>

#include "replier.h"
        
Replier::Replier(std::map<std::string, std::promise<std::string>*>* map1, std::mutex& map_lock1, Listener* listener1): map(map1), map_lock(map_lock1), listener(listener1) {
    std::thread([this]() {
        std::pair<std::string,std::string> reply;
        while (true) {
            if (this->listener->listen(&reply)) {
                std::string mac = reply.first, IP = reply.second;
                std::lock_guard<std::mutex> guard(this->map_lock);
                auto promise = this->map->find(mac);
                if (promise != this->map->end()){
                    promise->second->set_value(IP);
                    this->map->erase(promise);
                }
            }
        }
    }).detach();
}

//class that handles the process of listening for responses (via an instance of the listener class) and invoking the apropriate logic
#pragma once
#include <string> 
#include <map>
#include <thread>
#include <future>

#include "listener.h"

class Replier
{
    private:
        std::map<std::string, std::promise<std::string>*>* map;
        std::mutex& map_lock;
        Listener* listener;
    public:
        void reply();
        Replier(std::map<std::string, std::promise<std::string>*>* map1, std::mutex& map_lock1, Listener* listener1): map(map1), map_lock(map_lock1), listener(listener1) {
        }
};

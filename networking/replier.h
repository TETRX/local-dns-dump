//class that handles the process of listening for responses (via an instance of the listener class) and invoking the apropriate logic
#pragma once
#include <string> 
#include <map>
#include <future>

#include "listener.h"

class IPGetter;

class Replier
{
    private:
        std::map<std::string, std::promise<std::string>*> map;
        std::mutex map_lock;
        Listener* listener;
    public:
        Replier(Listener* listener);

        friend IPGetter;
};

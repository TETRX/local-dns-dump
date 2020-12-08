// an abstract class to handle listening for responses
#pragma once
#include <string>
#include <utility>

class Listener
{
public:
    virtual bool listen(std::pair<std::string, std::string>* out) = 0; //returns (mac,IP)
};

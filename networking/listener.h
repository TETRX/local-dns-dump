// an abstract class to handle listening for responses
#include <string>


class Listener
{
public:
    virtual std::pair<std::string, std::string> listen()=0; //returns (mac,IP)
};
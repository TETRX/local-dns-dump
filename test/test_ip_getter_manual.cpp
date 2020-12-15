#include <iostream>
#include <unistd.h>
#include <map>
#include <future>

#include "../networking/ip_getter.h"
#include "../networking/arping_requester.h"
#include "../networking/arping_listener.h"
#include "../networking/replier.h"

#define PREFIX "10.0.2."
#define MAC "52:54:00:12:35:02"


int main() {
    ArpingContext context;
    ArpingRequester requester(&context);
    ArpingListener listener(&context);
    std::map<std::string, std::promise<std::string>*> reqs;
    std::mutex lock;
    Replier replier(&reqs, lock, &listener);
    IPGetter ipgetter(&requester, &replier, &reqs, lock, PREFIX);
    std::string my_ans = ipgetter.get_ip(std::string(MAC)); //testing mac
    std::cout << "IPGetter got: " << my_ans << std::endl;
    return 0;
}

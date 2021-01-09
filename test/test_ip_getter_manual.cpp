#include <iostream>
#include <unistd.h>
#include <map>
#include <future>

#define USE_ARPING 0

#include "../networking/ip_getter.h"
#if USE_ARPING
#include "../networking/arping_requester.h"
#include "../networking/arping_listener.h"
#else
#include "../networking/crafter_requester.h"
#include "../networking/crafter_listener.h"
#endif
#include "../networking/replier.h"


int main() {
#if USE_ARPING
    ArpingContext context;
    ArpingRequester requester(&context);
    ArpingListener listener(&context);
#else
    Crafter::InitCrafter();
    CrafterRequester requester;
    CrafterListener listener;
#endif
    std::map<std::string, std::promise<std::string>*> reqs;
    std::mutex lock;
    Replier replier(&reqs, lock, &listener);
    IPGetter ipgetter(&requester, &replier, &reqs, lock, PREFIX, 10 * 1000);
    std::string my_ans = ipgetter.get_ip(std::string(MAC)); //testing mac
    std::cout << "IPGetter got: " << my_ans << std::endl;
#if !USE_ARPING
    Crafter::CleanCrafter();
#endif
    return 0;
}

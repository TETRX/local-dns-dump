#include <iostream>
#include <unistd.h>
#include <map>
#include <future>
#include "../config/DnsMapUser.h"

#include "../networking/ip_getter.h"
#include "../networking/crafter_requester.h"
#include "../networking/crafter_listener.h"
#include "../networking/replier.h"


int main() {
    Crafter::InitCrafter();
    CrafterRequester requester;
    CrafterListener listener;
    Replier replier(&listener);
    DnsMapUser dnsMapUser;
    IPGetter ipgetter(&requester, &replier, dnsMapUser, PREFIX, 3 * 1000);
    std::string my_ans = ipgetter.get_ip(std::string(MAC)); //testing mac
    std::cout << "IPGetter got: " << my_ans << std::endl;
    Crafter::CleanCrafter();
    exit(0);
}

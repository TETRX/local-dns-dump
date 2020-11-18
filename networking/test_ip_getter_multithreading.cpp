#include <iostream>
#include <unistd.h>
#include <map>
#include <future>
#include <thread>

#include "ip_getter.h"
#include "arping_requester.h"
#include "arping_listener.h"
#include "replier.h"

#define PREFIX "10.0.2."
#define MAC "52:54:00:12:35:02"


int main(){
    ArpingRequester requester;
    ArpingListener listener;
    std::map<std::string, std::promise<std::string>*> reqs;
    std::mutex lock;
    Replier replier(&reqs, lock, &listener);
    IPGetter ipgetter(&requester, &replier, &reqs, lock, PREFIX);
    std::thread([&replier]() {
		    replier.reply();
		    }).detach();
    std::string my_ans = ipgetter.get_ip(std::string(MAC)); //testing mac
    std::cout << "IPGetter got: " << my_ans << std::endl;
    return 0;
}

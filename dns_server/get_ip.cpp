#include "../config/DnsMapUser.h"
#include <future>
#include <iostream>
#include <map>
#include <unistd.h>

#define USE_ARPING 0

#include "../networking/ip_getter.h"
#if USE_ARPING
#include "../networking/arping_listener.h"
#include "../networking/arping_requester.h"
#else
#include "../networking/crafter_listener.h"
#include "../networking/crafter_requester.h"
#endif
#include "../networking/replier.h"

// The first argument (argv[1]) is the dns name
int main(int argc, char *argv[]) {
#if USE_ARPING
   ArpingContext context;
   ArpingRequester requester(&context);
   ArpingListener listener(&context);
#else
   Crafter::InitCrafter();
   CrafterRequester requester;
   CrafterListener listener;
#endif

   Replier replier(&listener);
   DnsMapUser dnsMapUser;
   std::string mac = dnsMapUser.getMacFromDnsName(argv[1]);

   // // Test for the timeout
   // if (argv[1][0] == '3')
   //    sleep(1000000);

   if (mac == "") {
      std::cerr << "Name not known" << std::endl;
      exit(1);
   }

   IPGetter ipgetter(&requester, &replier, dnsMapUser, PREFIX, 3 * 1000);
   std::string ip_addr = ipgetter.get_ip(mac);

   if (ip_addr == "") {
      std::cerr << "Couldn't get the ip adress" << std::endl;
      exit(1);
   }

   std::cerr << "Ip address: " << ip_addr << std::endl;
   std::cout << ip_addr << std::endl;
   exit(0);
}

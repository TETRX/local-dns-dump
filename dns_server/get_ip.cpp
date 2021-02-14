#include "../config/DnsMapUser.h"
#include <future>
#include <iostream>
#include <map>
#include <unistd.h>

#include "../networking/ip_getter.h"
#include "../networking/crafter_listener.h"
#include "../networking/crafter_requester.h"
#include "../networking/replier.h"

// The first argument (argv[1]) is the dns name
int main(int argc, char *argv[]) {
   Crafter::InitCrafter();
   CrafterRequester requester;
   CrafterListener listener;

   Replier replier(&listener);
   DnsMapUser dnsMapUser;
   std::string mac = dnsMapUser.getMacFromDnsName(argv[1]);

   if (mac == "") {
      std::cerr << "Name not known" << std::endl;
      exit(1);
   }

   IPGetter ipgetter(&requester, &replier, dnsMapUser, PREFIX, 3 * 1000);
   std::string ip_addr = ipgetter.get_ip(mac);

   if (ip_addr == "") {
      std::cerr << "Couldn't get the ip adress" << std::endl;
      Crafter::CleanCrafter();
      exit(1);
   }

   std::cerr << "Ip address: " << ip_addr << std::endl;
   std::cout << ip_addr << std::endl;
   Crafter::CleanCrafter();
   exit(0);
}

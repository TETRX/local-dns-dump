#include "ip_getter.h"
#include "../lib/time_utils.h"
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <utility>
#include <vector>

std::string IPGetter::wait_for_promise(std::promise<std::string> &promise) {
   auto future = promise.get_future();
   auto status = future.wait_for(std::chrono::milliseconds(timeout));
   if (status == std::future_status::timeout) {
      return "";
   } else {
      return future.get();
   }
}

std::string IPGetter::get_ip(std::string mac) {
   std::cerr << "Request: MAC=" << mac << std::endl;

   std::vector<std::string> cacheAttributes = cache.getIpAttributes(mac);
   if (!cacheAttributes.empty() && TimeUtils::valid(cacheAttributes[1], CACHE_TIMEOUT)) {
       return cacheAttributes[0];
   }

   std::promise<std::string> result;
   std::pair<std::map<std::string, std::promise<std::string> *>::iterator, bool> entry;
   {
      std::lock_guard<std::mutex> guard(map_lock);
      entry = map->emplace(mac, &result);
   }
   requester->request(local_network_ip_mask, mac);
   std::string resultIP = wait_for_promise(result);
   if (resultIP.empty()) {
       std::cout << "error: empty IP\n";
       exit(1);
   } else {
       cacheAttributes.push_back(resultIP);
       cacheAttributes.push_back(TimeUtils::timeNow());
       cache.updateEntry(mac, cacheAttributes);
   }
   return resultIP;
}

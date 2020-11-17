#include <iostream>
#include "ip_getter.h"
#include "arping_requester.h"
#include "no_response_exception.h"
#include <unistd.h>

#define MOCK 0
#define PREFIX "192.168.0."
#define MAC "00:00:00:00:00:00"

class MockRequester: public Requester
{
private:
    std::string right_ans;
public:
    std::string request(std::string ip_mask, std::string mac_requested){
        // std::cout << right_ans << "!=" << ip_mask << std::endl;
        sleep(1);
        if(right_ans==ip_mask){
            return right_ans;
        }
        throw NoResponseException();
    }
    MockRequester(std::string right): right_ans(right){};
};



int main(){
#if MOCK
    int ans;
    std::cin >> ans;
    std::string ans_string= std::to_string(ans);
    MockRequester mock(ans_string);
    Requester* p_mock=&mock;
    IPGetter ipgetter(p_mock,std::string(""));
#else
    ArpingRequester requester;
    Requester* p_requester = &requester;
    IPGetter ipgetter(p_requester, PREFIX); //testing ip-mask
#endif
    std::string my_ans=ipgetter.get_ip(std::string(MAC)); //testing mac
#if MOCK
    std::cout << "Input: " << ans << std::endl; 
#endif
    std::cout << "IPGetter got: " << my_ans << std::endl;
    return 0;
}

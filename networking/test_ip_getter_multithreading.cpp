#include <iostream>
#include "ip_getter.h"
#include "no_response_exception.h"
#include <unistd.h>

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
    int ans;
    std::cin >> ans;
    std::string ans_string= std::to_string(ans);
    MockRequester mock(ans_string);
    Requester* p_mock=&mock;
    IPGetter ipgetter(p_mock,std::string(""));
    std::string my_ans=ipgetter.get_ip(std::string(""));
    std::cout << "Input: " << ans << std::endl; 
    std::cout << "IPGetter got: " << my_ans << std::endl;
    return 0;
}
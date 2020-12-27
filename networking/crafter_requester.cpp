#include <thread>
#include <iostream>

#include "crafter_requester.h"

CrafterRequester::CrafterRequester() : Requester() {
    myIP = Crafter::GetMyIP(iface);
    myMAC = Crafter::GetMyMAC(iface);
            
    ethernetHeaderTemplate.SetSourceMAC(myMAC);
    arpHeaderTemplate.SetOperation(Crafter::ARP::Request);
    arpHeaderTemplate.SetSenderIP(myIP);
    arpHeaderTemplate.SetSenderMAC(myMAC);

    listen_for_requests();
}

void CrafterRequester::listen_for_requests() {
    std::thread([this]() {
            while (true) {
                auto request = this->requests.pop();
                this->ethernetHeaderTemplate.SetDestinationMAC(request.second);
                this->arpHeaderTemplate.SetTargetIP(request.first);
                
                Crafter::Packet *packet = new Crafter::Packet;
                packet->PushLayer(this->ethernetHeaderTemplate);
                packet->PushLayer(this->arpHeaderTemplate);
                std::cout << "Sending " << this->ethernetHeaderTemplate.GetSourceMAC() << " " << this->ethernetHeaderTemplate.GetDestinationMAC() << " " << this->arpHeaderTemplate.GetSenderIP() << " " << this->arpHeaderTemplate.GetSenderMAC() << " " << this->arpHeaderTemplate.GetTargetIP() << std::endl;
                packet->Send(iface);
        }
    }).detach();
}

void CrafterRequester::request(std::string ip_mask, std::string mac_requested) {
	requests.push(make_pair(ip_mask, mac_requested));
}

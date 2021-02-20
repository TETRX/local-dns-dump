#include <thread>
#include <iostream>

#include "crafter_requester.h"

CrafterRequester::CrafterRequester() : Requester() {
    myIP = Crafter::GetMyIP(IFACE);
    if (myIP.empty()) {
        std::cerr << "Local DNS error: invalid interface" << std::endl;
        exit(1);
    }
    myMAC = Crafter::GetMyMAC(IFACE);
    if (myMAC.empty()) {
        std::cerr << "Local DNS error: invalid interface" << std::endl;
        exit(1);
    }
     
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
                std::string ipMask = request.first;
                std::string mac = request.second;
                this->ethernetHeaderTemplate.SetDestinationMAC(mac);
                std::vector<std::string> net = Crafter::GetIPs(ipMask);
                std::vector<Crafter::Packet*> packets;
                for (auto ipAddr = net.begin(); ipAddr != net.end(); ipAddr++) {
                    this->arpHeaderTemplate.SetTargetIP(*ipAddr);
                    Crafter::Packet *packet = new Crafter::Packet;
                    packet->PushLayer(this->ethernetHeaderTemplate);
                    packet->PushLayer(this->arpHeaderTemplate);
                    packets.push_back(packet);
                }
                Crafter::Send(packets.begin(), packets.end(), IFACE, 48);
                Crafter::ClearContainer(packets);
        }
    }).detach();
}

void CrafterRequester::request(std::string ip_mask, std::string mac_requested) {
	requests.push(make_pair(ip_mask, mac_requested));
}

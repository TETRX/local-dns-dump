#include "crafter_listener.h"
#include <utility>

void packet_handler_wrapper(Crafter::Packet *packet, void *user) {
    CrafterListener *This = static_cast<CrafterListener*>(user);
    This->packet_handler(packet);
}

CrafterListener::CrafterListener() : Listener(), sniffer(std::string("arp[7]=2"), "", packet_handler_wrapper) {
    sniffer.SetInterface(IFACE);
    sniffer.Spawn(-1, static_cast<void*>(this));
}

void CrafterListener::packet_handler(Crafter::Packet *packet) { 
    Crafter::ARP *arpLayer = packet->GetLayer<Crafter::ARP>();
    replies.push(make_pair(arpLayer->GetSenderMAC(), arpLayer->GetSenderIP()));
}

bool CrafterListener::listen(std::pair<std::string, std::string>* out) {
    *out = replies.pop();
    return true;
}

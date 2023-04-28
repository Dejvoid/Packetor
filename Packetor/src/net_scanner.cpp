#include "net_scanner.hpp"
#include <iostream>
#include <EthLayer.h>

static bool on_packet_arrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    //std::cout << "Arrived packet ";
    auto storage = (unordered_set<MacAddress>*)cookie;
    Packet p(packet);
    if (auto p2 = p.getLayerOfType<EthLayer>()) { 
        //std::cout << "Source: " << p2->getSourceMac() << " Destination: "  << p2->getDestMac() << std::endl;
        storage->insert(p2->getSourceMac());
        storage->insert(p2->getDestMac());
    }
    return false;
}

static bool on_packet_arrival_ipv4(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    //std::cout << "Arrived packet ";
    auto storage = (set<IPv4Address>*)cookie;
    Packet p(packet);
    if (auto p2 = p.getLayerOfType<IPv4Layer>()) { 
        //std::cout << "Source: " << p2->getSourceMac() << " Destination: "  << p2->getDestMac() << std::endl;
        storage->insert(p2->getDstIPv4Address());
        storage->insert(p2->getSrcIPv4Address());
    }
    return false;
}

static bool on_packet_arrival_ipv6(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    //std::cout << "Arrived packet ";
    auto storage = (set<IPv6Address>*)cookie;
    Packet p(packet);
    if (auto p2 = p.getLayerOfType<IPLayer>()) { 
        //std::cout << "Source: " << p2->getSourceMac() << " Destination: "  << p2->getDestMac() << std::endl;
        auto dest =p2->getDstIPAddress().getIPv6();
        auto src = p2->getSrcIPAddress().getIPv6();
        if (dest != IPv6Address::Zero)
            storage->insert(dest);
        if (src != IPv6Address::Zero)
            storage->insert(src);
    }
    return false;
}


NetScanner::NetScanner(PcapLiveDevice* device) : interface_(device) {
}

void NetScanner::scan_mac_passive(int wait_time) {
    std::cout << "Started passive MAC scan" << std::endl;
    if (interface_->open()) {
        interface_->startCaptureBlockingMode(on_packet_arrival, &mac_devs_, wait_time);
    }
    else 
        std::cout << "Device in use: " << interface_->getName() << std::endl;
    std::cout << "Scan done!" << std::endl;
    std::cout << "Found " << mac_devs_.size() << " devices: " << std::endl;
    for (auto it = mac_devs_.begin(); it != mac_devs_.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
    std::cout << std::endl;
}

void NetScanner::scan_ipv4_passive(int wait_time) {
    std::cout << "Started passive IPv4 scan" << std::endl;
    if (interface_->open()) {
        interface_->startCaptureBlockingMode(on_packet_arrival_ipv4, &ipv4_devs_, wait_time);
    }
    else 
        std::cout << "Device in use: " << interface_->getName() << std::endl;
    std::cout << "Scan done!" << std::endl;
    std::cout << "Found " << ipv4_devs_.size() << " devices: " << std::endl;
    for (auto it = ipv4_devs_.begin(); it != ipv4_devs_.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
    std::cout << std::endl;
}

void NetScanner::scan_ipv6_passive(int wait_time) {
    std::cout << "Started passive IPv6 scan" << std::endl;
    if (interface_->open()) {
        interface_->startCaptureBlockingMode(on_packet_arrival_ipv6, &ipv6_devs_, wait_time);
    }
    else 
        std::cout << "Device in use: " << interface_->getName() << std::endl;
    std::cout << "Scan done!" << std::endl;
    std::cout << "Found " << ipv6_devs_.size() << " devices: " << std::endl;
    for (auto it = ipv6_devs_.begin(); it != ipv6_devs_.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
    std::cout << std::endl;
}
#include "net_scanner.hpp"
#include <iostream>
#include <EthLayer.h>

/// @brief Callback for blocking capture mode
/// @param packet captured packet
/// @param dev device where packet was captured
/// @param cookie storage, we use Stats struct for collecting statistics
/// @return returns if we should continue capturing more
static bool on_packet_arrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    auto storage = (Stats*)cookie;
    Packet p(packet);
    storage->consumePacket(p);
    return false;
}

void Stats::consumePacket(const Packet& packet){
    if (packet.isPacketOfType(pcpp::Ethernet)){
        if (auto p = packet.getLayerOfType<EthLayer>()) { 
            mac_devs.insert(p->getSourceMac());
            mac_devs.insert(p->getDestMac());
        }

        eth_count++;
    }
    if (packet.isPacketOfType(pcpp::IPv4)) {
        ipv4_count++;
        if (auto p = packet.getLayerOfType<IPv4Layer>()) { 
            ipv4_devs.insert(p->getDstIPv4Address());
            ipv4_devs.insert(p->getSrcIPv4Address());
        }
    }
    if (packet.isPacketOfType(pcpp::IPv6)){
        ipv6_count++;
        if (auto p = packet.getLayerOfType<IPLayer>()) { 
            auto dest = p->getDstIPAddress().getIPv6();
            auto src = p->getSrcIPAddress().getIPv6();
            if (dest != IPv6Address::Zero)
                ipv6_devs.insert(dest);
            if (src != IPv6Address::Zero)
                ipv6_devs.insert(src);
        }
    }
    if (packet.isPacketOfType(pcpp::TCP))
        tcp_count++;
    if (packet.isPacketOfType(pcpp::UDP))
        udp_count++;
    if (packet.isPacketOfType(pcpp::DNS))
        dns_count++;
    if (packet.isPacketOfType(pcpp::HTTP))
        http_count++;
    if (packet.isPacketOfType(pcpp::SSL))
        ssl_count++;
    }

void NetScanner::scan_mac_passive(PcapLiveDevice* device, int wait_time) {
    std::cout << "Started passive MAC scan" << std::endl;
    if (device->open()) {
        device->startCaptureBlockingMode(on_packet_arrival, &stats_, wait_time);
    }
    else 
        std::cout << "Device in use: " << device->getName() << std::endl;
    std::cout << "Scan done!" << std::endl;
    std::cout << "Found " << stats_.mac_devs.size() << " devices: " << std::endl;
    for (auto it = stats_.mac_devs.begin(); it != stats_.mac_devs.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
}

void NetScanner::scan_ipv4_passive(PcapLiveDevice* device, int wait_time) {
    std::cout << "Started passive IPv4 scan" << std::endl;
    if (device->open()) {
        device->startCaptureBlockingMode(on_packet_arrival, &stats_, wait_time);
    }
    else 
        std::cout << "Device in use: " << device->getName() << std::endl;
    std::cout << "Scan done!" << std::endl;
    std::cout << "Found " << stats_.ipv4_devs.size() << " devices: " << std::endl;
    for (auto it = stats_.ipv4_devs.begin(); it != stats_.ipv4_devs.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
}

void NetScanner::scan_ipv6_passive(PcapLiveDevice* device, int wait_time) {
    std::cout << "Started passive IPv6 scan" << std::endl;
    if (device->open()) {
        device->startCaptureBlockingMode(on_packet_arrival, &stats_, wait_time);
    }
    else 
        std::cout << "Device in use: " << device->getName() << std::endl;
    std::cout << "Scan done!" << std::endl;
    std::cout << "Found " << stats_.ipv6_devs.size() << " devices: " << std::endl;
    for (auto it = stats_.ipv6_devs.begin(); it != stats_.ipv6_devs.end(); ++it) {
        std::cout << (*it) << std::endl;
    }
}

void NetScanner::print_stats(std::ostream& os) const {
    os << "Capture statistics: " << std::endl;
    print_mac(os);
    print_ipv4(os);
    print_ipv6(os);
    print_packets(os);
}

void NetScanner::print_ipv6(std::ostream& os) const { 
    os << "Discovered IPv6 addresses: " << std::endl;
    int i = 0;
    for (auto it = stats_.ipv6_devs.begin(); it != stats_.ipv6_devs.end(); ++it) {
        auto ip = *it;
        os << " [" << i++ << "] " << ip << std::endl;
    }
}

void NetScanner::print_ipv4(std::ostream& os) const {
    os << "Discovered IPv4 addresses: " << std::endl;
    int i = 0;
    for (auto it = stats_.ipv4_devs.begin(); it != stats_.ipv4_devs.end(); ++it) {
        auto ip = *it;
        os << " [" << i++ << "] " << ip << std::endl;
    }
}

void NetScanner::print_mac(std::ostream& os) const {
    os << "Discovered MAC addresses: " << std::endl;
    int i = 0;
    for (auto it = stats_.mac_devs.begin(); it != stats_.mac_devs.end(); ++it) {
        auto m = *it;
        os << " [" << i++ << "] " << m << std::endl;
    }
}

void NetScanner::print_packets(std::ostream& os) const {
    os << "Packet summary: " << std::endl
    << " Ethernet packets: " << stats_.eth_count  << std::endl
    << " IPv4 packets: " << stats_.ipv4_count  << std::endl
    << " IPv6 packets: " << stats_.ipv6_count << std::endl
    << " TPC packets: " << stats_.tcp_count << std::endl
    << " UDP packets: " << stats_.udp_count  << std::endl
    << " DNS packets: " << stats_.dns_count << std::endl
    << " HTTP packets: " << stats_.http_count << std::endl
    << " SSL packets: " << stats_.ssl_count << std::endl;
}
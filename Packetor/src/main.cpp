#include <iostream>
#include <IPv4Layer.h>
#include <Packet.h>
#include <PcapFileDevice.h>
#include <PcapLiveDeviceList.h>

#include "net_scanner.hpp"

using namespace pcpp;

struct PacketStats
{
    int ethPacketCount;
    int ipv4PacketCount;
    int ipv6PacketCount;
    int tcpPacketCount;
    int udpPacketCount;
    int dnsPacketCount;
    int httpPacketCount;
    int sslPacketCount;

    /**
    * Clear all stats
    */
    void clear() { ethPacketCount = 0; ipv4PacketCount = 0; ipv6PacketCount = 0; tcpPacketCount = 0; udpPacketCount = 0; tcpPacketCount = 0; dnsPacketCount = 0; httpPacketCount = 0; sslPacketCount = 0; }

    /**
    * C'tor
    */
    PacketStats() { clear(); }

    /**
    * Collect stats from a packet
    */
    void consumePacket(pcpp::Packet& packet)
    {
        if (packet.isPacketOfType(pcpp::Ethernet))
            ethPacketCount++;
        if (packet.isPacketOfType(pcpp::IPv4)) {
            ipv4PacketCount++;
            std::cout << "Captured ipv4 packet: ";
            auto ipv4_info = packet.getLayerOfType<IPv4Layer>();
            std::cout << "Source: " << ipv4_info->getSrcIPAddress() << " Destination: " << ipv4_info->getDstIPAddress() << std::endl;
        }
        if (packet.isPacketOfType(pcpp::IPv6))
            ipv6PacketCount++;
        if (packet.isPacketOfType(pcpp::TCP))
            tcpPacketCount++;
        if (packet.isPacketOfType(pcpp::UDP))
            udpPacketCount++;
        if (packet.isPacketOfType(pcpp::DNS))
            dnsPacketCount++;
        if (packet.isPacketOfType(pcpp::HTTP))
            httpPacketCount++;
        if (packet.isPacketOfType(pcpp::SSL))
            sslPacketCount++;
    }

    /**
    * Print stats to console
    */
    void printToConsole()
    {
        std::cout
            << "Ethernet packet count: " << ethPacketCount << std::endl
            << "IPv4 packet count:     " << ipv4PacketCount << std::endl
            << "IPv6 packet count:     " << ipv6PacketCount << std::endl
            << "TCP packet count:      " << tcpPacketCount << std::endl
            << "UDP packet count:      " << udpPacketCount << std::endl
            << "DNS packet count:      " << dnsPacketCount << std::endl
            << "HTTP packet count:     " << httpPacketCount << std::endl
            << "SSL packet count:      " << sslPacketCount << std::endl;
    }
};

void list_devices() {
    auto device_list = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    for (auto it = device_list.begin(); it!=device_list.end(); ++it) {
        auto device = *it;
        if (device->getMacAddress() != MacAddress::Zero) {
            std::cout << device->getName() << std::endl;
            std::cout << "Address (ipv4): " << device->getIPv4Address() << " (ipv6): " << device->getIPv6Address() << std::endl;
            std::cout << "MAC: " << device->getMacAddress() << std::endl;
            //std::cout << "DNS: " << device->getDnsServers() << std::endl;
            std::cout << std::endl;
        }
    }
}

static bool onPacketArrivesBlockingMode(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
    // extract the stats object form the cookie
    PacketStats* stats = (PacketStats*)cookie;

    // parsed the raw packet
    pcpp::Packet parsedPacket(packet);

    // collect stats from packet
    stats->consumePacket(parsedPacket);

    // return false means we don't want to stop capturing after this callback
    return false;
}

int main (int argc, char** argv){ 
    //if (argc <= 1) {
    //    std::cout << "Use --help" << std::endl;
    //}
    //std::string interfaceIPAddr = "192.168.0.20";
    //pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr);
    //if (dev == NULL)
    //{
    //    std::cerr << "Cannot find interface with IPv4 address of '" << interfaceIPAddr << "'" << std::endl;
    //    return 1;
    //}
    // list interfaces: 

    list_devices();
    auto device = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList()[0];

    NetScanner ns{device};
    ns.scan_mac_passive();
    ns.scan_ipv4_passive();
    ns.scan_ipv6_passive();
    int a;
    std::cin >> a;
    PcapLiveDevice::DeviceConfiguration config;
    config.direction = PcapLiveDevice::PcapDirection::PCPP_IN;
    config.mode = PcapLiveDevice::DeviceMode::Promiscuous;
    config.packetBufferSize = 10;
    //device->open(config);
    
    if (device->open()) {
        PacketStats stats;
        device->startCaptureBlockingMode(onPacketArrivesBlockingMode, &stats, 10);
        std::cout << "Results:" << std::endl;
        stats.printToConsole();
    }
} 
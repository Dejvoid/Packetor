#include <iostream>
#include <IPv4Layer.h>
#include <Packet.h>
#include <PcapFileDevice.h>
#include <PcapLiveDeviceList.h>

int main (int argc, char** argv){ 
    if (argc <= 1) {
        std::cout << "Use --help" << std::endl;
    }
    std::string interfaceIPAddr = "192.168.0.20";
    pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr);
    if (dev == NULL)
    {
        std::cerr << "Cannot find interface with IPv4 address of '" << interfaceIPAddr << "'" << std::endl;
        return 1;
    }
} 
#include "controls.hpp"
#include <iostream>
#include <string>
#include <PcapLiveDeviceList.h>
#include <PcapFileDevice.h>

#include "net_scanner.hpp"

using namespace pcpp;

void UserControl::main_loop() {
    std::cout << "Try 'help' for commands" << std::endl;
    while (true) {
        std::cout << "> ";
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "help") {
            help();
        } else if (cmd == "list") {
            list_devs();
        } else if (cmd == "mac_scan") {
            mac_scan();
        }
        else if (cmd == "exit") {
            return;
        } else {
            help();
        }
    }
}

void UserControl::help() {
    std::cout << "Help for Packetor: " << std::endl;
    std::cout << "In interactive mode: " << std::endl;

    std::cout << "'help'" << " to show this help" << std::endl;
    std::cout << "'list'" << " to list interfaces" << std::endl;
    std::cout << "'exit'" << " to exit" << std::endl;

}

void UserControl::list_devs() {
    int i = 0;
    for (auto it = dev_list_.begin(); it!=dev_list_.end(); ++it) {
        auto device = *it;
        if (device->getMacAddress() != MacAddress::Zero) {
            std::cout << "[" << i << "] "<< device->getName() << std::endl;
            std::cout << "Address (ipv4): " << device->getIPv4Address() << " (ipv6): " << device->getIPv6Address() << std::endl;
            std::cout << "MAC: " << device->getMacAddress() << std::endl;
            //std::cout << "DNS: " << device->getDnsServers() << std::endl;
            std::cout << std::endl;
        }
        ++i;
    }
}

void UserControl::mac_scan() {
    list_devs();
    std::cout << "> Select device: ";
    int dev_index = 0;
    std::cin >> dev_index;
    bool passive = true;
    if (passive) {
        NetScanner ns {dev_list_[dev_index]};
        std::cout << "> Select how long: ";
        int wait_time = 5;
        std::cin >> wait_time;
        ns.scan_mac_passive(wait_time);
    }
}
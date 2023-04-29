#include "controls.hpp"
#include <iostream>
#include <string>
#include <PcapLiveDeviceList.h>
#include <PcapFileDevice.h>

#include "net_scanner.hpp"
#include "packet_sender.hpp"

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
        } else if (cmd == "ip_scan") {
            ip_scan();
        } else if (cmd == "send") {
            send();
        }
        else if (cmd == "exit") {
            return;
        } else {
            std::cout << "Unknown command!" << std::endl;
            // help();
        }
    }
}

void UserControl::help() {
    std::cout << "Help for Packetor: " << std::endl;
    std::cout << "In interactive mode: " << std::endl;

    std::cout << "'help'" << " to show this help" << std::endl;
    std::cout << "'list'" << " to list interfaces" << std::endl;
    std::cout << "'mac_scan'" << " to scan MAC addresses" << std::endl;
    std::cout << "'ip_scan'" << " to scan IP addresses" << std::endl;
    std::cout << "'send'" << " to send custom packets" << std::endl;
    std::cout << "'exit'" << " to exit" << std::endl;
}

void UserControl::list_devs() {
    int i = 0;
    for (auto it = dev_list_.begin(); it!=dev_list_.end(); ++it) {
        auto device = *it;
        // if (device->getMacAddress() != MacAddress::Zero) {
            std::cout << "[" << i << "] "<< device->getName() << std::endl;
            std::cout << "Address (ipv4): " << device->getIPv4Address() << " (ipv6): " << device->getIPv6Address() << std::endl;
            std::cout << "MAC: " << device->getMacAddress() << std::endl;
            //std::cout << "DNS: " << device->getDnsServers() << std::endl;
            std::cout << std::endl;
        //}
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

void UserControl::ip_scan() {
    list_devs();
    std::cout << "> Select device: ";
    int dev_index = 0;
    std::cin >> dev_index;
    std::cout << "> Select version (4 or 6): ";
    int version = 4;
    std::cin >> version;
    bool passive = true;
    if (passive) {
        NetScanner ns {dev_list_[dev_index]};
        std::cout << "> Select how long: ";
        int wait_time = 5;
        std::cin >> wait_time;
        if (version == 4)
            ns.scan_ipv4_passive(wait_time);
        else if (version == 6) 
            ns.scan_ipv6_passive(wait_time);
        else 
            std::cout << "Wrong input" << std::endl;
        //else {
        //    ns.scan_ipv4_passive(wait_time);
        //    ns.scan_ipv6_passive(wait_time);
        //}
    }
}

bool UserControl::read_mac(MacAddress& mac, std::istream& is) {
    std::string mac_str;
    std::cin >> mac_str;
    if (mac_str == "none") {
        mac = MacAddress::Zero;
        return true;
    }
    mac = MacAddress{mac_str};
    if (!mac.isValid()){ 
        std::cout << "MAC: " << mac_str << " is invalid. Returning." << std::endl;
        return false;
    }
    return true;
}

void UserControl::send() {
    list_devs();
    std::cout << "> Select device: ";
    int dev_index = 0;
    std::cin >> dev_index;
    if (dev_index <0 || dev_index >= dev_list_.size()) {
        std::cout << "Wrong device index" << std::endl;
        return;
    }
    auto device = dev_list_[dev_index];
    PacketSender ps{device};
    MacAddress src_mac;
    MacAddress dst_mac;
    std::cout << "> Enter source MAC ('none' if use interface MAC): ";
    if (!read_mac(src_mac))
        return;
    if (src_mac == MacAddress::Zero)
        src_mac = device->getMacAddress();
    std::cout << "> Enter destination MAC ('none' if use zeros): ";
    if (!read_mac(dst_mac))
        return;
    Packet newPacket;
    EthLayer layer{src_mac,dst_mac};
    newPacket.addLayer(&layer);

    if (device->open()) {
        // std::cout << "Attempting to send packet" << std::endl;
        device->sendPacket(&newPacket);
        std::cout << "Packet sent " << src_mac << " " << dst_mac << std::endl;
    }
    else 
        std::cout << "ERROR" << std::endl;
}

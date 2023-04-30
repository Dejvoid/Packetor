#include "controls.hpp"
#include <iostream>
#include <string>
#include <PcapLiveDeviceList.h>
#include <PcapFileDevice.h>
#include <IPv6Layer.h>

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
        } else if (cmd == DEV_LIST) {
            list_devs();
        } else if (cmd == MAC_SCAN) {
            mac_scan();
        } else if (cmd == IP_SCAN) {
            ip_scan();
        } else if (cmd == SEND) {
            send();
        } else if (cmd == MAC_LIST) {
            list_mac();
        } else if (cmd == IP4_LIST) {
            list_ipv4();
        } else if (cmd == IP6_LIST) {
            list_ipv6();
        }
        else if (cmd == EXIT) {
            return;
        } else {
            std::cout << "Unknown command!" << std::endl;
            // help();
        }
    }
}

void UserControl::help() {
    std::cout << "Help for Packetor: " << std::endl;
    //std::cout << "In interactive mode: " << std::endl;

    std::cout << "'help'" << " to show this help" << std::endl;
    std::cout << "'" << DEV_LIST << "'" << " to list interfaces" << std::endl;
    std::cout << "'" << MAC_LIST << "'" << " to list discovered MAC addresses" << std::endl;
    std::cout << "'" << MAC_SCAN << "'" << " to scan MAC addresses" << std::endl;
    std::cout << "'" << IP_SCAN << "'" << " to scan IP addresses" << std::endl;
    std::cout << "'" << IP4_LIST << "'" << " to list IPv4 addresses" << std::endl;
    std::cout << "'" << IP6_LIST << "'" << " to list IPv6 addresses" << std::endl;
    std::cout << "'" << SEND <<"'" << " to send custom packets" << std::endl;
    std::cout << "'" << EXIT << "'" << " to exit" << std::endl;
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

void UserControl::list_mac() {
    auto macs = net_scanner_.get_mac();
    std::cout << "Discovered MAC addresses: " << std::endl;
    int i = 0;
    for (auto it = macs.begin(); it != macs.end(); ++it) {
        auto m = *it;
        std::cout << "[" << i++ << "] " << m << std::endl;
    }
}

void UserControl::list_ipv4() {
    auto ips = net_scanner_.get_ipv4();
    std::cout << "Discovered IPv4 addresses: " << std::endl;
    int i = 0;
    for (auto it = ips.begin(); it != ips.end(); ++it) {
        auto ip = *it;
        std::cout << "[" << i++ << "] " << ip << std::endl;
    }
}

void UserControl::list_ipv6() {
    auto ips = net_scanner_.get_ipv6();
    std::cout << "Discovered IPv6 addresses: " << std::endl;
    int i = 0;
    for (auto it = ips.begin(); it != ips.end(); ++it) {
        auto ip = *it;
        std::cout << "[" << i++ << "] " << ip << std::endl;
    }
}

void UserControl::mac_scan() {
    list_devs();
    std::cout << "> Select device: ";
    size_t dev_index = 0;
    std::cin >> dev_index;
    bool passive = true;
    if (passive) {
        std::cout << "> Select how long: ";
        int wait_time = 5;
        std::cin >> wait_time;
        net_scanner_.scan_mac_passive(dev_list_[dev_index],wait_time);
    }
}

void UserControl::ip_scan() {
    list_devs();
    std::cout << "> Select device: ";
    size_t dev_index = 0;
    std::cin >> dev_index;
    std::cout << "> Select version (4 or 6): ";
    int version = 4;
    std::cin >> version;
    bool passive = true;
    if (passive) {
        std::cout << "> Select how long: ";
        int wait_time = 5;
        std::cin >> wait_time;
        if (version == 4)
            net_scanner_.scan_ipv4_passive(dev_list_[dev_index],wait_time);
        else if (version == 6) 
            net_scanner_.scan_ipv6_passive(dev_list_[dev_index],wait_time);
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

bool UserControl::read_ip4(IPv4Address& ip, std::istream& is) {
    std::string ip_str;
    std::cin >> ip_str;
    if (ip_str == "none") {
        ip = IPv4Address::Zero;
        return true;
    }
    ip = IPv4Address{ip_str};
    if (!ip.isValid()){ 
        std::cout << "IPv4: " << ip_str << " is invalid. Returning." << std::endl;
        return false;
    }
    return true;
}

bool UserControl::read_ip6(IPv6Address& ip, std::istream& is) {
    std::string ip_str;
    std::cin >> ip_str;
    if (ip_str == "none") {
        ip = IPv6Address::Zero;
        return true;
    }
    ip = IPv6Address{ip_str};
    if (!ip.isValid()){ 
        std::cout << "IPv6: " << ip_str << " is invalid. Returning." << std::endl;
        return false;
    }
    return true;
}

bool UserControl::select_device(PcapLiveDevice** device) {
    std::cout << "> Select device: ";
    size_t dev_index = 0;
    std::cin >> dev_index;
    if (dev_index <0 || dev_index >= dev_list_.size()) {
        std::cout << "Wrong device index" << std::endl;
        return false;
    }
    *device = dev_list_[dev_index];
    return true;
}

bool UserControl::fill_eth_layer(const PcapLiveDevice* device, MacAddress& src_mac, MacAddress& dst_mac, uint16_t& eth_type) {
    std::cout << "> Enter source MAC ('none' if use interface MAC): ";
    if (!read_mac(src_mac))
        return false;
    if (src_mac == MacAddress::Zero) {
        src_mac = device->getMacAddress();
    }
    std::cout << "> Enter destination MAC ('none' if use zeros): ";
    if (!read_mac(dst_mac))
        return false;
    std::cout << "> Ethernet type (HEX)? (" << hex << "0x" << PCPP_ETHERTYPE_ARP << "-ARP, "
                                    << "0x" << PCPP_ETHERTYPE_IP << "-IP, "
                                    << "0x" << PCPP_ETHERTYPE_IPV6 << "-IPv6, "
                                    << "0x" << PCPP_ETHERTYPE_VLAN << "-Vlan, "
                                    << "0x" << PCPP_ETHERTYPE_WAKE_ON_LAN << "-WakeOnLan and more...) ";
    std::cin >> hex >> eth_type;
    return true;
}

bool UserControl::fill_ip4_layer(const PcapLiveDevice* device, IPv4Address& src_ip, IPv4Address& dst_ip) {
    std::cout << "> Enter source address: ('none' if use interface MAC) ";
    if(!read_ip4(src_ip))
        return false;
    if (src_ip == IPv4Address::Zero)
        src_ip = device->getIPv4Address();
    std::cout << "> Enter destination address: ('none' for zero) ";
    if(!read_ip4(dst_ip))
        return false;
    return true;
}

bool UserControl::fill_ip6_layer(const PcapLiveDevice* device, IPv6Address& src_ip, IPv6Address& dst_ip) {
    std::cout << "> Enter source address: ('none' if use interface MAC) ";
    if(!read_ip6(src_ip))
        return false;
    if (src_ip == IPv6Address::Zero)
        src_ip = device->getIPv6Address();
    std::cout << "> Enter destination address: ('none' for zero) ";
    if(!read_ip6(dst_ip))
        return false;
    return true;
}

void UserControl::send() {
    list_devs();
    PcapLiveDevice* device;
    if (!select_device(&device))
        return;
    PacketSender ps{device};    
    Packet newPacket;
    MacAddress src_mac,dst_mac;
    uint16_t eth_type;
    if (!fill_eth_layer(device, src_mac,dst_mac, eth_type))
        return;
    auto eth_layer = EthLayer{src_mac,dst_mac, eth_type};
    eth_layer.computeCalculateFields();
    newPacket.addLayer(&eth_layer);
    std::cout << "> Add IP layer [4/6/n]? ";
    char ip_l;
    std::cin >> ip_l;
    if (ip_l == '4') {
        IPv4Address src_ip;
        IPv4Address dst_ip;
        fill_ip4_layer(device, src_ip,dst_ip);
        IPv4Layer ip_layer{src_ip, dst_ip};
        ip_layer.computeCalculateFields();
        newPacket.addLayer(&ip_layer);
    }
    else if (ip_l == '6') {
        IPv6Address src_ip;
        IPv6Address dst_ip;
        fill_ip6_layer(device, src_ip, dst_ip);
        IPv6Layer ip_layer{src_ip, dst_ip};
        ip_layer.computeCalculateFields();
        newPacket.addLayer(&ip_layer);
    }

    std::cout << "> How many packets to send?: ";
    unsigned int packet_count = 1;
    std::cin >> packet_count;
    ps.send_packet(&newPacket, packet_count);
    std::cout << "> Save packet template [y/n]? ";
    char save;
    std::cin >> save;
    if (save == 'y') {
        save_packet_file("preset_packet", newPacket);
    }
}

void UserControl::save_packet_file(const std::string& filename, const Packet& packet) {
    ofstream ofs;
    ofs.open(filename);
    if (ofs.good()) {
        ofs << packet;
        ofs.close();
        std::cout << "Saved" << std::endl;
    }
    else 
        std::cout << "Error with file " << filename << std::endl;
}

Packet UserControl::load_packet_file(const std::string& filename) {
    Packet p;
    return p;
}
#ifndef CONTROLS_HPP_
#define CONTROLS_HPP_

#include <vector>
#include <PcapLiveDeviceList.h>
#include <iostream>

#include "net_scanner.hpp"

using namespace pcpp;

constexpr std::string_view DEV_LIST = "dev_list";
constexpr std::string_view MAC_LIST = "mac_list";
constexpr std::string_view MAC_SCAN = "mac_scan";
constexpr std::string_view SEND = "send";
constexpr std::string_view IP_SCAN = "ip_scan";
constexpr std::string_view IP4_LIST = "ip4_list";
constexpr std::string_view IP6_LIST = "ip6_list";
constexpr std::string_view EXIT = "exit";

class UserControl {
    std::vector<PcapLiveDevice*> dev_list_ = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    NetScanner net_scanner_;
    public:
    void main_loop();
    void help();
    void list_devs();
    void list_mac();
    void list_ipv4();
    void list_ipv6();
    void mac_scan();
    void ip_scan();
    void send();
    void save_packet_file(const std::string& file, const Packet& packet);
    Packet load_packet_file(const std::string& file);
    private:
    bool read_mac(MacAddress& mac, std::istream& is = std::cin);
};

#endif
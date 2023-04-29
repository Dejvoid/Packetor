#ifndef CONTROLS_HPP_
#define CONTROLS_HPP_

#include <vector>
#include <PcapLiveDeviceList.h>
#include <iostream>

#include "net_scanner.hpp"

using namespace pcpp;

class UserControl {
    std::vector<PcapLiveDevice*> dev_list_ = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    NetScanner net_scanner_;
    public:
    void main_loop();
    void help();
    void list_devs();
    void mac_scan();
    void ip_scan();
    void send();
    void save_packet_file(const std::string& file, const Packet& packet);
    Packet load_packet_file(const std::string& file);
    private:
    bool read_mac(MacAddress& mac, std::istream& is = std::cin);
};

#endif
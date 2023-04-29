#ifndef CONTROLS_HPP_
#define CONTROLS_HPP_

#include <vector>
#include <PcapLiveDeviceList.h>
#include <iostream>

using namespace pcpp;

class UserControl {
    std::vector<PcapLiveDevice*> dev_list_ = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    public:
    void main_loop();
    void help();
    void list_devs();
    void mac_scan();
    void ip_scan();
    void send();
    private:
    bool read_mac(MacAddress& mac, std::istream& is = std::cin);
};

#endif
#ifndef CONTROLS_HPP_
#define CONTROLS_HPP_

#include <vector>
#include <PcapLiveDeviceList.h>

using namespace pcpp;

class UserControl {
    private:
    std::vector<PcapLiveDevice*> dev_list_ = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    public:
    void main_loop();
    void help();
    void list_devs();
    void mac_scan();
};

#endif
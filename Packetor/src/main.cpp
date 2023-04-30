#include <iostream>
#include <IPv4Layer.h>
#include <Packet.h>
#include <PcapFileDevice.h>
#include <PcapLiveDeviceList.h>

#include "net_scanner.hpp"
#include "packet_sender.hpp"
#include "controls.hpp"


int main (int argc, char** argv){ 
    if (argc <= 1) {
        std::cout << "Interactive mode" << std::endl;
        UserControl uc;
        uc.main_loop();
        return 0;
    }
    else {
        std::cout << "Argument mode not ready yet, use Interactive mode instead" << std::endl;
        return 0;
    } 
} 
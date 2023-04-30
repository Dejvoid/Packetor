#include <iostream>
#include <IPv4Layer.h>
#include <Packet.h>
#include <PcapFileDevice.h>
#include <PcapLiveDeviceList.h>

#include "net_scanner.hpp"
#include "packet_sender.hpp"
#include "arguments.hpp"
#include "controls.hpp"

static bool onPacketArrivesBlockingMode(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
    // extract the stats object form the cookie
    Stats* stats = (Stats*)cookie;

    // parsed the raw packet
    pcpp::Packet parsedPacket(packet);

    // collect stats from packet
    stats->consumePacket(parsedPacket);

    // return false means we don't want to stop capturing after this callback
    return false;
}

int main (int argc, char** argv){ 
    if (argc <= 1) {
        std::cout << "Interactive mode" << std::endl;
        UserControl uc;
        uc.main_loop();
        return 0;
    }
    else {
        args_t args{argv + 1, argv + argc};
        options_t options;

    } 

    auto device = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList()[1]; 
    PacketSender ps{device};
    //ps.send_packet();
    ps.wifi_deauth();

    if (device->open()) {
        Stats stats;
        device->startCaptureBlockingMode(onPacketArrivesBlockingMode, &stats, 10);
        std::cout << "Results:" << std::endl;
        //stats.printToConsole();
    }
} 
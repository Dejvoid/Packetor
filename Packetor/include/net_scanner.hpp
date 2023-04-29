#ifndef NET_SCANNER_HPP_
#define NET_SCANNER_HPP_

#include <unordered_set>
#include <set>
#include <IPv4Layer.h>
#include <PcapLiveDevice.h>

using namespace std;
using namespace pcpp;

namespace std {
template <>
struct hash<MacAddress> {
  size_t operator()(const MacAddress &addr) const {
    return hash<const uint8_t*>()(addr.getRawData());
  }
};
}

struct PacketStats
{
    int eth_count = 0;
    int ipv4_count = 0;
    int ipv6_count = 0;
    int tcp_count = 0;
    int udp_count = 0;
    int dns_count = 0;
    int http_count = 0;
    int ssl_count = 0;

    void consumePacket(const Packet& packet);

    /**
    * Print stats to console
    */
    void printToConsole();
};

class NetScanner {
    set<IPv4Address> ipv4_devs_;
    set<IPv6Address> ipv6_devs_;
    unordered_set<MacAddress> mac_devs_;
    public:
    void scan_mac_passive(PcapLiveDevice* device, int wait_time = 5);
    void scan_ipv4_passive(PcapLiveDevice* device, int wait_time = 5);
    void scan_ipv6_passive(PcapLiveDevice* device, int wait_time = 5);
};

#endif 
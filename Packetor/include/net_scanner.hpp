#ifndef NET_SCANNER_HPP_
#define NET_SCANNER_HPP_

#include <unordered_set>
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

class NetScanner {
    private:
    //unordered_set<IPv4Address> ipv4_devs_;
    //unordered_set<IPv6Address> ipv6_devs_;
    unordered_set<MacAddress> mac_devs_;
    PcapLiveDevice* interface_;
    public:
    NetScanner(PcapLiveDevice* device);
    void scan_mac_passive(int wait_time = 5);
};

#endif 
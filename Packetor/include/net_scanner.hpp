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

//namespace std {
//template <>
//struct hash<IPv4Address> {
//  size_t operator()(const IPv4Address &addr) const {
//    return hash<const uint8_t*>()(addr.);
//  }
//};
//}

class NetScanner {
    private:
    set<IPv4Address> ipv4_devs_;
    set<IPv6Address> ipv6_devs_;
    unordered_set<MacAddress> mac_devs_;
    PcapLiveDevice* interface_;
    public:
    NetScanner(PcapLiveDevice* device);
    void scan_mac_passive(int wait_time = 5);
    void scan_ipv4_passive(int wait_time = 5);
    void scan_ipv6_passive(int wait_time = 5);
};

#endif 
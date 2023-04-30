#ifndef NET_SCANNER_HPP_
#define NET_SCANNER_HPP_

#include <unordered_set>
#include <set>
#include <IPv4Layer.h>
#include <PcapLiveDevice.h>

using namespace std;
using namespace pcpp;

/// @brief MacAddress hashing for unordered_set container
namespace std {
template <>
struct hash<MacAddress> {
  size_t operator()(const MacAddress &addr) const {
    return hash<const uint8_t*>()(addr.getRawData());
  }
};
}

/// @brief Struct for saving stats
struct Stats {
    int eth_count = 0;
    int ipv4_count = 0;
    int ipv6_count = 0;
    int tcp_count = 0;
    int udp_count = 0;
    int dns_count = 0;
    int http_count = 0;
    int ssl_count = 0;


    /// @brief Add packet to stats
    /// @param packet 
    void consumePacket(const Packet& packet);

    void printToConsole();
};

/// @brief Class for scanning network
class NetScanner {
    /// @brief Discovered IPv4 addresses
    set<IPv4Address> ipv4_devs_;
    /// @brief Discovered IPv6 addresses
    set<IPv6Address> ipv6_devs_;
    /// @brief Discovered MAC addresses
    unordered_set<MacAddress> mac_devs_;
    public:
    /// @brief Passive scan of MAC addresses communicating on the netowrk
    /// @param device Device where scan is performed
    /// @param wait_time (default=5) Scan duration [seconds]
    void scan_mac_passive(PcapLiveDevice* device, int wait_time = 5);
    /// @brief Passive scan of IPv4 addresses communicating on the netowrk
    /// @param device Device where scan is performed
    /// @param wait_time (default=5) Scan duration [seconds]
    void scan_ipv4_passive(PcapLiveDevice* device, int wait_time = 5);
    /// @brief Passive scan of IPv6 addresses communicating on the netowrk
    /// @param device Device where scan is performed
    /// @param wait_time (default=5) Scan duration [seconds]
    void scan_ipv6_passive(PcapLiveDevice* device, int wait_time = 5);
    /// @brief Readonly getter for ipv4_devs_ field
    /// @return Const reference to the field
    const set<IPv4Address>& get_ipv4() const {return ipv4_devs_;};
    /// @brief Readonly getter for ipv6_devs_ field
    /// @return Const reference to the field
    const set<IPv6Address>& get_ipv6() const {return ipv6_devs_;};
    /// @brief Readonly getter for mac_devs_ field
    /// @return Const reference to the field
    const unordered_set<MacAddress>& get_mac() const {return mac_devs_;};
};

#endif 
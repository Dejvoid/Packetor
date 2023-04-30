#ifndef NET_SCANNER_HPP_
#define NET_SCANNER_HPP_

#include <unordered_set>
#include <set>
#include <IPv4Layer.h>
#include <PcapLiveDevice.h>
#include <iostream>

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
    /// @brief Discovered IPv4 addresses
    set<IPv4Address> ipv4_devs;
    /// @brief Discovered IPv6 addresses
    set<IPv6Address> ipv6_devs;
    /// @brief Discovered MAC addresses
    unordered_set<MacAddress> mac_devs;
    /// @brief Add packet to stats
    /// @param packet 
    void consumePacket(const Packet& packet);
};

/// @brief Class for scanning network
class NetScanner {
    Stats stats_;
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
    const set<IPv4Address>& get_ipv4() const {return stats_.ipv4_devs;};
    /// @brief Readonly getter for ipv6_devs_ field
    /// @return Const reference to the field
    const set<IPv6Address>& get_ipv6() const {return stats_.ipv6_devs;};
    /// @brief Readonly getter for mac_devs_ field
    /// @return Const reference to the field
    const unordered_set<MacAddress>& get_mac() const {return stats_.mac_devs;};
    /// @brief Readonly getter for all stats
    /// @return Const reference to stats field
    const Stats& get_stats() const {return stats_;};
    /// @brief Prints stats in human-readable format
    /// @param os output stream
    void print_stats(std::ostream& os = std::cout) const;
    void print_ipv6(std::ostream& os = std::cout) const;
    void print_ipv4(std::ostream& os = std::cout) const;
    void print_mac(std::ostream& os = std::cout) const;
    void print_packets(std::ostream& os = std::cout) const;
};

#endif 
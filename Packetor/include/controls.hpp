#ifndef CONTROLS_HPP_
#define CONTROLS_HPP_

#include <vector>
#include <PcapLiveDeviceList.h>
#include <iostream>

#include "net_scanner.hpp"

using namespace pcpp;

constexpr std::string_view DEV_LIST = "dev_list";
constexpr std::string_view MAC_LIST = "mac_list";
constexpr std::string_view MAC_SCAN = "mac_scan";
constexpr std::string_view SEND = "send";
constexpr std::string_view IP_SCAN = "ip_scan";
constexpr std::string_view IP4_LIST = "ip4_list";
constexpr std::string_view IP6_LIST = "ip6_list";
constexpr std::string_view EXIT = "exit";

/// @brief Class responsible for user interface (mostly interactive mode)
class UserControl {
    /// @brief Vector of local devices
    std::vector<PcapLiveDevice*> dev_list_ = PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    /// @brief Network scanning and logging interface
    NetScanner net_scanner_;
    public:
    /// @brief Interactive mode main loop
    void main_loop();
    /// @brief Shows help for commands
    void help();
    /// @brief Lists all available local devices
    void list_devs();
    /// @brief Lists discovered MAC addresses from net_scanner_ field
    void list_mac();
    /// @brief Lists discovered IPv4 addresses from net_scanner_ field
    void list_ipv4();
    /// @brief Lists discovered IPv6 addresses from net_scanner_ field
    void list_ipv6();
    /// @brief User interface for scanning MACs using net_scanner_ field
    void mac_scan();
    /// @brief User interface for scanning IPs using net_scanner_ field
    void ip_scan();
    /// @brief User interface for custom packet sending
    void send();
    /// @brief Saves packet to file for future uses
    /// @param file filename for storing packet
    /// @param packet packet to be stored in the file
    void save_packet_file(const std::string& file, const Packet& packet);
    /// @brief Loads packet from file
    /// @param file filename for loading the packet
    /// @return loaded packet
    Packet load_packet_file(const std::string& file);
    private:
    /// @brief Interface for reading MAC from user (user input == "none" is correct usage and returns MacAddress::Zero)
    /// @param mac out MAC address
    /// @param is user input stream
    /// @return false if the address is invalid
    bool read_mac(MacAddress& mac, std::istream& is = std::cin);
    /// @brief Interface for reading IPv4 from user (user input == "none" is correct usage and returns IPv4Address::Zero)
    /// @param ip out IP address
    /// @param is user input stream
    /// @return false if the address is invalid
    bool read_ip4 (IPv4Address& ip, std::istream& is = std::cin);
    /// @brief Interface for reading IPv6 from user (user input == "none" is correct usage and returns IPv6Address::Zero)
    /// @param ip out IP address
    /// @param is false if the address is invalid
    /// @return false if the address is invalid
    bool read_ip6 (IPv6Address& ip, std::istream& is = std::cin);
    /// @brief User interface for selection of the device from local devices using index
    /// @param device Selected device
    /// @return true if device was successfully selected
    bool select_device(PcapLiveDevice** device);
    /// @brief Prepares Ethernet layer for packet (Addresses and Type)
    /// @param device Used to determine default source MAC address
    /// @param src_mac Source MAC address
    /// @param dst_mac Destination MAC address
    /// @param eth_type Ethernet type code (i.e. ARP, WakeOnLan etc.)
    /// @return false if there was error
    bool fill_eth_layer(const PcapLiveDevice* device, MacAddress& src_mac, MacAddress& dst_mac, uint16_t& eth_type);
    /// @brief Prepares IPv4 layer for packet (addresses)
    /// @param device Used to fill default address
    /// @param src_ip Source address
    /// @param dst_ip Destination address
    /// @return false if there was error
    bool fill_ip4_layer(const PcapLiveDevice* device, IPv4Address& src_ip, IPv4Address& dst_ip);
    /// @brief Prepares IPv6 layer for packet (addresses)
    /// @param device Used to fill default address
    /// @param src_ip Source address
    /// @param dst_ip Destination address
    /// @return false if there was error
    bool fill_ip6_layer(const PcapLiveDevice* device, IPv6Address& src_ip, IPv6Address& dst_ip);
};

#endif
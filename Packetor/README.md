
# Packetor - C++ programming final assignment

Author: David Hřivna

Keywords: C++, libpcap, Network, CLI

## Introduction

This project is my final assignment for C++ programming course at MFF UK. Idea was to create network analysis tool with ability to send custom packets, logging traffic, monitoring activity in the network.

## User interface

Program has simple interactive console interface where you enter commands: 

- `help` - shows program help
- `list` - lists local interfaces
- `mac_scan` - passive network MAC scan
- `ip_scan` - passive network IP scan (IPv4 or IPv6)
- `send` - send custom packet (interactively created or file templated)
- `exit` - exits the program

## Technical information 

Project is developed in C++ with [Pcap++ library](https://pcapplusplus.github.io/).

## Compilation

Use `cmake` to compile. Compiled Pcap++ library sources and headers are required in `lib` directory. Recommended structure is described in `lib/README.md` 
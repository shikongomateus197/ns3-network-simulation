# Project Documentation

## 1. Introduction

This project demonstrates the design, configuration and simulation of a hybrid wired and wireless network using ns-3.
The project began as an academic practical for a Wireless Technologies course and was subsequently organised as a personal portfolio project.


## 2. Objectives

- Design a hybrid wired and wireless network topology.

- Configure network devices and IP addressing.

- Implement communication between network devices.

- Test connectivity using ICMP ping.

- Generate network traffic traces and packet captures.

- Visualise the simulated network using NetAnim.

- Inspect captured network packets using Wireshark.


## 3. Technologies and Tools

|   Technology             | Purpose                         |

|   ---                    |    ---                          |

|   C++                    | Simulation programming          |

|   ns-3                   | Network simulation              |

|   Wireshark              | Packet inspection and analysis  |

|   NetAnim                | Network topology visualisation  |

|   Ethernet / CSMA        | Wired network communication     |

|   IEEE 802.11b           | Wireless communication          |

|   ICMP                   | Connectivity testing            |


## 4. Personalisation

The simulation uses the assigned personalisation value X = 49.

- Server switch configuration: 49 ports, with port 49 allocated to the Authentication Server.

- Serial link data rate: 49 kbps.

- PC1 ICMP payload size: 49 bytes.

- IP addressing: addresses include 49 in one octet.


## 5. Connectivity Testing

Connectivity was tested between:

- PC1 and the ISP router.
- Authentication Server and the ISP router.

The simulation reported successful ping communication for both tests, with 0% packet loss in the recorded runs.


## 6. Generated Files

|      File         | Description                                   |

|   ---             |   ---                                         |

|  shikongo.cc      | C++ ns-3 simulation source code               |

|  shikongo.pcap    | Packet capture from the Authentication Server |

|  shikongo.tr      | ns-3 traffic trace                            |

|  shikongo.xml     | NetAnim network animation data                |



## 7. Wireshark Packet Analysis

The simulation generates a PCAP file from the Authentication Server's network interface.

The PCAP file can be opened in Wireshark to inspect captured packets, examine protocol information and understand communication between network devices.

This provides practical experience with packet inspection and network troubleshooting.


## 8. NetAnim Visualisation

The generated XML file can be opened in NetAnim to visualise the simulated network topology and observe the network nodes and their connections.

A screenshot of the topology is included in the screenshots directory.


## 9. Skills Demonstrated

- C++ programming
- Network topology design
- IP addressing and subnetting
- Wired and wireless networking
- Routing and connectivity testing
- Packet capture and analysis
- Network traffic tracing
- Linux command-line usage
- Network simulation and visualisation


## 10. Possible Future Improvements

- Add more network devices and network segments.

- Analyse network performance under different traffic loads.

- Compare different routing configurations.

- Measure throughput, delay and packet loss.

- Extend the simulation with additional network protocols.


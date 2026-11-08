# Hybrid Wired & Wireless Network Simulation

A small ns-3 network simulation project demonstrating how a mixed wired/wireless network can be designed, configured, tested, traced, and visualised.

> Project origin: This project was first completed as an academic practical for a Wireless Technologies course. I then extended and organised it as a personal portfolio project to demonstrate my practical networking and simulation skills.

## What is this project?

The project models a small network containing:

-   Two PCs
-   An access Ethernet switch
-   A site router
-   An 802.11b ad-hoc wireless link
-   An exit router
-   A server Ethernet switch
-   A Web Server
-   An Authentication Server
-   An ISP router

The simulation intentionally excludes the Internet cloud from the original topology.
The network is created and tested entirely in ns-3, using C++.

## Technology

  Tool / Technology          Purpose
    C++                 Simulation source code
    ns-3                Network simulation
    802.11b             Wireless ad-hoc connection
    CSMA/Ethernet       Wired LAN connections
    Point-to-Point      Serial link to the ISP router
    NetAnim             Network visualisation
    Linux terminal      Build, run, inspect and package the project

ns-3 is a discrete-event network simulator designed for networking research and education.

## Network skills demonstrated

### 1. Network topology design

The project converts a topology diagram into an executable simulation containing end devices, switches, routers and servers.

### 2. IP addressing and subnetting

The network is divided into separate IP networks for the access LAN, wireless link, server LAN and serial link.

The personalised addressing uses 49 in every IP address.

### 3. Wired and wireless networking

The simulation combines Ethernet/CSMA connections with an 802.11b ad-hoc wireless connection.

### 4. Routing

IPv4 global routing is used so that devices on different network segments can communicate.

### 5. Network testing

PC1 and the Authentication Server both send ICMP traffic to the ISP router.

The completed simulation achieved:

-   PC1 → ISP: 8 packets transmitted, 8 received, 0% loss
-   Authentication Server → ISP: 8 packets transmitted, 8 received,
    0% loss
-   PC1 ICMP payload: 49 bytes

### 6. Traffic analysis

The project produces:

-   .tr --- ASCII trace of traffic on the serial link
-   .pcap --- packet capture from the Authentication Server
-   .xml --- NetAnim visualisation of the simulation

These outputs make the simulation more than a diagram: they provide evidence that the network actually ran and generated traffic.

## Personalisation

The project uses X = 49.

  Requirement             Implementation
  Personalisation value   X = 49
  Server switch           49 ports
  Authentication Server   Port 49
  Serial link             49 kbps
  PC1 ICMP payload        49 bytes
  IP addressing           Every IP contains 49

## Repository structure

 text
ns3-network-simulation/
│
├── README.md
├── docs/
│   └── PROJECT_DOCUMENTATION.md
│
├── src/
│   └── shikongo.cc
│
├── results/
│   ├── shikongo.pcap
│   ├── shikongo.tr
│   └── shikongo.xml
│
└── screenshots/
└── netanim-topology.png


## Running the simulation

This project is intended to run inside an ns-3 installation.

From the ns-3 directory:

bash
./ns3 build
./ns3 run scratch/shikongo


The simulation creates the trace, packet capture and NetAnim files in
the working directory.

## Why this project matters

The value of this project is not simply that it "uses ns-3". It demonstrates the ability to move from a network requirement to a working technical model:

requirement → topology → implementation → addressing → routing → testing → traffic capture → visualisation

That workflow is directly relevant to practical networking, systems and infrastructure work.

## Evidence

The results/ directory contains the generated simulation outputs. The project documentation in docs/PROJECT_DOCUMENTATION.md explains the design and the skills demonstrated.

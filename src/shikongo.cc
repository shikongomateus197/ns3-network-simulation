#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/applications-module.h"
#include "ns3/csma-module.h"
#include "ns3/bridge-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int
main(int argc, char *argv[])
{
    const uint32_t X = 49;

    Time::SetResolution(Time::NS);

    // Create the network nodes
    NodeContainer pc1;
    pc1.Create(1);

    NodeContainer pc2;
    pc2.Create(1);

    NodeContainer siteRouter;
    siteRouter.Create(1);

    NodeContainer exitRouter;
    exitRouter.Create(1);

    NodeContainer webServer;
    webServer.Create(1);

    NodeContainer authenticationServer;
    authenticationServer.Create(1);

    NodeContainer ispRouter;
    ispRouter.Create(1);

    // Create Ethernet switch nodes
    NodeContainer accessSwitch;
    accessSwitch.Create(1);

    NodeContainer serverSwitch;
    serverSwitch.Create(1);

    // Install the Internet stack on IP-capable devices
    InternetStackHelper internet;

    internet.Install(pc1);
    internet.Install(pc2);
    internet.Install(siteRouter);
    internet.Install(exitRouter);
    internet.Install(webServer);
    internet.Install(authenticationServer);
    internet.Install(ispRouter);

    // ACCESS SWITCH
    // PC1 -> Access Switch
    // PC2 -> Access Switch
    // Site Router -> Access Switch

    CsmaHelper accessLink;
    accessLink.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    accessLink.SetChannelAttribute("Delay", TimeValue(MicroSeconds(10)));

    NetDeviceContainer pc1AccessDevices;
    NetDeviceContainer pc2AccessDevices;
    NetDeviceContainer routerAccessDevices;

    pc1AccessDevices = accessLink.Install(
        NodeContainer(pc1.Get(0), accessSwitch.Get(0)));

    pc2AccessDevices = accessLink.Install(
        NodeContainer(pc2.Get(0), accessSwitch.Get(0)));

    routerAccessDevices = accessLink.Install(
        NodeContainer(siteRouter.Get(0), accessSwitch.Get(0)));

    NetDeviceContainer accessBridgeDevices;

    accessBridgeDevices.Add(pc1AccessDevices.Get(1));
    accessBridgeDevices.Add(pc2AccessDevices.Get(1));
    accessBridgeDevices.Add(routerAccessDevices.Get(1));

    BridgeHelper accessBridge;
    accessBridge.Install(
        accessSwitch.Get(0),
        accessBridgeDevices);

    // SERVER SWITCH
    //
    // The server switch has exactly 49 ports.
    //
    // Port 1  -> Exit Router
    // Port 2  -> Web Server
    // Port 49 -> Authentication Server
    //
    // Ports 3 through 48 are unused switch ports.

    CsmaHelper serverLink;
    serverLink.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    serverLink.SetChannelAttribute("Delay", TimeValue(MicroSeconds(10)));

    NetDeviceContainer serverBridgeDevices;

    // Port 1: Exit Router
    NetDeviceContainer exitServerDevices;
    exitServerDevices = serverLink.Install(
        NodeContainer(exitRouter.Get(0), serverSwitch.Get(0)));

    serverBridgeDevices.Add(exitServerDevices.Get(1));

    // Port 2: Web Server
    NetDeviceContainer webServerDevices;
    webServerDevices = serverLink.Install(
        NodeContainer(webServer.Get(0), serverSwitch.Get(0)));

    serverBridgeDevices.Add(webServerDevices.Get(1));

    // Ports 3 through 48: unused ports
    for (uint32_t port = 3; port <= 48; ++port)
    {
        Ptr<Node> unusedNode = CreateObject<Node>();

        NetDeviceContainer unusedDevices;
        unusedDevices = serverLink.Install(
            NodeContainer(unusedNode, serverSwitch.Get(0)));

        serverBridgeDevices.Add(unusedDevices.Get(1));
    }

    // Port 49: Authentication Server
    NetDeviceContainer authenticationDevices;
    authenticationDevices = serverLink.Install(
        NodeContainer(authenticationServer.Get(0), serverSwitch.Get(0)));

    serverBridgeDevices.Add(authenticationDevices.Get(1));

    BridgeHelper serverBridge;
    serverBridge.Install(
        serverSwitch.Get(0),
        serverBridgeDevices);

    // 802.11b AD-HOC WIRELESS LINK
    // Site Router <-> Exit Router

    YansWifiChannelHelper wifiChannel =
        YansWifiChannelHelper::Default();

    YansWifiPhyHelper wifiPhy;
    wifiPhy.SetChannel(wifiChannel.Create());

    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);

    WifiMacHelper wifiMac;
    wifiMac.SetType("ns3::AdhocWifiMac");

    NodeContainer wirelessNodes;
    wirelessNodes.Add(siteRouter.Get(0));
    wirelessNodes.Add(exitRouter.Get(0));

    NetDeviceContainer wirelessDevices =
        wifi.Install(
            wifiPhy,
            wifiMac,
            wirelessNodes);

    // SERIAL LINK
    // Exit Router <-> ISP Router
    //
    // Personalised speed = X kbps = 49 kbps

    PointToPointHelper serialLink;

    serialLink.SetDeviceAttribute(
        "DataRate",
        StringValue("49kbps"));

    serialLink.SetChannelAttribute(
        "Delay",
        StringValue("2ms"));

    NetDeviceContainer serialDevices =
        serialLink.Install(
            exitRouter.Get(0),
            ispRouter.Get(0));

    // IP ADDRESSING
    //
    // X = 49 must appear in every IP address.

    Ipv4AddressHelper address;

    // Access LAN
    address.SetBase(
        "10.49.1.0",
        "255.255.255.0");

    Ipv4InterfaceContainer pc1Interface;
    pc1Interface = address.Assign(
        pc1AccessDevices.Get(0));

    Ipv4InterfaceContainer pc2Interface;
    pc2Interface = address.Assign(
        pc2AccessDevices.Get(0));

    Ipv4InterfaceContainer siteRouterAccessInterface;
    siteRouterAccessInterface = address.Assign(
        routerAccessDevices.Get(0));

    // Wireless network
    address.SetBase(
        "10.49.2.0",
        "255.255.255.0");

    Ipv4InterfaceContainer wirelessInterfaces;
    wirelessInterfaces = address.Assign(
        wirelessDevices);

    // Server LAN
    address.SetBase(
        "10.49.3.0",
        "255.255.255.0");

    Ipv4InterfaceContainer exitRouterServerInterface;
    exitRouterServerInterface = address.Assign(
        exitServerDevices.Get(0));

    Ipv4InterfaceContainer webServerInterface;
    webServerInterface = address.Assign(
        webServerDevices.Get(0));

    Ipv4InterfaceContainer authenticationServerInterface;
    authenticationServerInterface = address.Assign(
        authenticationDevices.Get(0));

    // Serial network
    address.SetBase(
        "10.49.4.0",
        "255.255.255.252");

    Ipv4InterfaceContainer serialInterfaces;
    serialInterfaces = address.Assign(
        serialDevices);

    // Enable routing between all networks
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // PC1 PING TO ISP ROUTER
    //
    // Personalised ICMP payload = X bytes = 49 bytes

    PingHelper pc1Ping(
        serialInterfaces.GetAddress(1));

    pc1Ping.SetAttribute(
        "Size",
        UintegerValue(X));

    pc1Ping.SetAttribute(
        "Interval",
        TimeValue(Seconds(1.0)));

    pc1Ping.SetAttribute(
        "VerboseMode",
        EnumValue(Ping::VerboseMode::VERBOSE));

    ApplicationContainer pc1PingApplication =
        pc1Ping.Install(pc1.Get(0));

    pc1PingApplication.Start(
        Seconds(2.0));

    pc1PingApplication.Stop(
        Seconds(10.0));

    // AUTHENTICATION SERVER PING TO ISP ROUTER

    PingHelper authenticationPing(
        serialInterfaces.GetAddress(1));

    authenticationPing.SetAttribute(
        "Size",
        UintegerValue(X));

    authenticationPing.SetAttribute(
        "Interval",
        TimeValue(Seconds(1.0)));

    authenticationPing.SetAttribute(
        "VerboseMode",
        EnumValue(Ping::VerboseMode::VERBOSE));

    ApplicationContainer authenticationPingApplication =
        authenticationPing.Install(
            authenticationServer.Get(0));

    authenticationPingApplication.Start(
        Seconds(2.0));

    authenticationPingApplication.Stop(
        Seconds(10.0));

    // ASCII TRACE FILE
    //
    // Trace traffic on the serial link.
    // Output file: shikongo.tr

    AsciiTraceHelper asciiTrace;

    Ptr<OutputStreamWrapper> serialTrace =
        asciiTrace.CreateFileStream("shikongo.tr");

    serialLink.EnableAsciiAll(serialTrace);

    // PCAP FILE
    //
    // Capture traffic on the Authentication Server.

    serverLink.EnablePcap(
        "shikongo",
        authenticationDevices.Get(0),
        false);

    // NETANIM

    AnimationInterface animation(
        "shikongo.xml");

    // Give all nodes fixed positions for NetAnim
    MobilityHelper mobility;

    mobility.SetMobilityModel(
        "ns3::ConstantPositionMobilityModel");

    NodeContainer allNodes;

    allNodes.Add(pc1.Get(0));
    allNodes.Add(pc2.Get(0));
    allNodes.Add(siteRouter.Get(0));
    allNodes.Add(exitRouter.Get(0));
    allNodes.Add(webServer.Get(0));
    allNodes.Add(authenticationServer.Get(0));
    allNodes.Add(ispRouter.Get(0));
    allNodes.Add(accessSwitch.Get(0));
    allNodes.Add(serverSwitch.Get(0));

    mobility.Install(allNodes);

    // PC1
    animation.SetConstantPosition(
        pc1.Get(0),
        1.0,
        3.0);

    // PC2
    animation.SetConstantPosition(
        pc2.Get(0),
        1.0,
        5.0);

    // Access switch
    animation.SetConstantPosition(
        accessSwitch.Get(0),
        3.0,
        4.0);

    // Site router
    animation.SetConstantPosition(
        siteRouter.Get(0),
        5.0,
        4.0);

    // Exit router
    animation.SetConstantPosition(
        exitRouter.Get(0),
        8.0,
        4.0);

    // Server switch
    animation.SetConstantPosition(
        serverSwitch.Get(0),
        11.0,
        4.0);

    // Web server
    animation.SetConstantPosition(
        webServer.Get(0),
        13.0,
        3.0);

    // Authentication server
    animation.SetConstantPosition(
        authenticationServer.Get(0),
        13.0,
        5.0);

    // ISP router
    animation.SetConstantPosition(
        ispRouter.Get(0),
        11.0,
        7.0);

    // Run the simulation
    Simulator::Stop(
        Seconds(12.0));

    Simulator::Run();

    Simulator::Destroy();

    return 0;
}

#!/usr/bin/env python

# legacy_network.py for CST311 @ CSUMB by BayTech: Luis Jimenez-Barrios, 
#   Warren Ngoun, Yukio Rivera, Jennah Yasin.
# A Mininet topology script that sets up two individual subnets 
# connected by the "internet" and allows for communication between both.
# Also runs a chat server and client on 3 total hosts, 1 server, 2 clients
# & a SSL web server (assuming CAGen.sh has been run already) in the background.

from mininet.net import Mininet
from mininet.node import Controller, RemoteController, OVSController
from mininet.node import CPULimitedHost, Host, Node
from mininet.node import OVSKernelSwitch, UserSwitch
from mininet.node import IVSSwitch
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.link import TCLink, Intf
from subprocess import call
from mininet.term import makeTerm
import time

def myNetwork():

    net = Mininet(topo=None, build=False, ipBase='10.0.0.0/24')

    info('*** Adding Controller \n')
    c0 = net.addController(name='c0', controller=Controller, protocol='tcp',port=6633)

    info('*** Adding Switches \n')
    info('- Created S1 & S2 \n')
    s1 = net.addSwitch('s1', cls=OVSKernelSwitch)
    s2 = net.addSwitch('s2', cls=OVSKernelSwitch)
    info('\n')

    # -------------------------------------------------------------------------
    
    # SUBNET 1's will be 10.0.1.X/24
    info('*** Creating Subnet 1: \n')
    # Lines to create and establish R3 aka Subnet 1's border router
    r3 = net.addHost('r3', cls=Node, ip='10.0.1.1/24')
    r3.cmd('sysctl -w net.ipv4.ip_forward=1')
    info('- R3 ')
    # Create H1 w/ proper forwarding to R3
    h1 = net.addHost('h1', cls=Host, ip='10.0.1.2/24', defaultRoute='via 10.0.1.1')
    info('H1 ')
    # Create H2 w/ proper forwarding to R3
    h2 = net.addHost('h2', cls=Host, ip='10.0.1.3/24', defaultRoute='via 10.0.1.1')
    info('H2 \n')
    # Setup all links and we're done w/ "Subnet 1"
    info('- Establishing Links Between Devices \n')
    net.addLink(h1, s1)
    net.addLink(h2, s1)
    net.addLink(s1, r3)
    info('- Subnet Done \n')
    info('\n')

    # -------------------------------------------------------------------------

    # SUBNET 2's will be 10.0.2.X/24
    info('*** Creating Subnet 2: \n')
    # Create R5, Subnet 2's border router.
    r5 = net.addHost('r5', cls=Node, ip='10.0.2.1/24')
    r5.cmd('sysctl -w net.ipv4.ip_forward=1')
    info('- R5 ')
    # Create H3 and set forwarding to R5
    h3 = net.addHost('h3', cls=Host, ip='10.0.2.2/24', defaultRoute='via 10.0.2.1')
    info('H3 ')
    # Create H4 and set forwarding to R5
    h4 = net.addHost('h4', cls=Host, ip='10.0.2.3/24', defaultRoute='via 10.0.2.1')
    info('H4 \n')
    # Setup all links and we're done w/ "Subnet 2"
    info('- Establishing Links Between Devices \n')
    net.addLink(h3, s2)
    net.addLink(h4, s2)
    net.addLink(s2, r5)
    info('- Subnet Done \n')
    info('\n')

    # -------------------------------------------------------------------------
    
    # This block handles creating R4 and all the linkages between
    info('*** Creating "Internet": \n')
    # Create R4, IP is not X.X.1.1 due to R4 being the "2nd" link, see below.
    r4 = net.addHost('r4', cls=Node, ip='192.168.1.2/30')
    r4.cmd('sysctl -w net.ipv4.ip_forward=1')
    info('- R4 \n')
    # Special /30 linkages needed to handle the P-P links between the routers. 
    info('- Establishing Links \n')
    # R3/R4 will be 192.168.1.X/30, for handling Subnet 1 & links to "internet" 
    # R4/R5 will be 192.168.2.X/30, for handling Subnet 2 & links to "internet"
    net.addLink(r3, r4, intfName1='r3-eth1', params1={'ip': '192.168.1.1/30'},intfName2='r4-eth0', params2={'ip': '192.168.1.2/30'})
    net.addLink(r4, r5, intfName1='r4-eth1', params1={'ip': '192.168.2.1/30'},intfName2='r5-eth1', params2={'ip': '192.168.2.2/30'})
    
    # Setting up the static routes (routing tables for each router) for R3-R5.
    info('- Establishing Routing Tables \n')
    # For each border router, need route to "other" links & one to R4 for 
    # packets bound to the "other" subnet.

    # On R3, for packets going to Subnet 2's Links, sent to R4 via IP/Intf
    r3.cmd('route add -net 192.168.2.0/30 gw 192.168.1.2 r3-eth1')
    # On R3, for packets going to Subnet 2, also sent to R4 via same
    r3.cmd('route add -net 10.0.2.0/24 gw 192.168.1.2 r3-eth1')
    # On R5, for packets going to Subnet 1, sent to via R4's Link IP/Inft
    r5.cmd('route add -net 10.0.1.0/24 gw 192.168.2.1 r5-eth1')
    # On R5, outbound packets to Subnet 1's links, sent to R4 via same
    r5.cmd('route add -net 192.168.1.0/30 gw 192.168.2.1 r5-eth1')

    # "Internet" just routes packets to the other border router.
    # On R4, outbound packets to Subnet 1 routed to R3 (using LINK IPs).
    r4.cmd('route add -net 10.0.1.0/24 gw 192.168.1.1 r4-eth0')
    # On R4, outbound packets to Subnet 2 routed to R5 (same idea as last).
    r4.cmd('route add -net 10.0.2.0/24 gw 192.168.2.2 r4-eth1')
    # Done w/ most setup now.
    info('- Routing Tables Done \n')
    info('- "Internet" Done \n')
    info('\n')

    # -------------------------------------------------------------------------

    info('*** Starting network\n')
    net.build()
    info('*** Starting controllers\n')
    for controller in net.controllers:
        controller.start()

    info('*** Starting switches\n')
    net.get('s2').start([c0])
    net.get('s1').start([c0])

    # -------------------------------------------------------------------------
    
    # Start our XTERM windows w/ commands for each script. Make subsequent ones 
    # wait 1s to ensure they don't fight and all appear properly.
    info('*** Starting Xterms \n')
    makeTerm(h4, title='Chat Server', term='xterm', display=None, cmd='sudo python3 server.py')
    time.sleep(1)
    makeTerm(h3, title='Chat Client', term='xterm', display=None, cmd='sudo python3 client.py')
    time.sleep(1)
    makeTerm(h1, title='Chat Client', term='xterm', display=None, cmd='sudo python3 client.py')
    # Now startup our ssl webserver, filename is based on Lab 6
    info('*** Starting SSL Web Server \n')
    h2.cmd('python3 ./sslserver.py &')

    # -------------------------------------------------------------------------

    info( '*** Post configure switches and hosts\n')
    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    myNetwork()
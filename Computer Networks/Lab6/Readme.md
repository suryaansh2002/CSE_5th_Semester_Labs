## Lab 6


1. Switching Cisco IOS Command Modes

This exercise demonstrates how to log into a router and how to work with the different Cisco IOS command modes. It is important to understand the different modes so you know where you are and what commands are accepted at any time.

i. Connect the Ethernet interfaces of the Linux PCs and the Cisco router as shown in Figure 7.7.

Do not turn on the Linux PCs yet.

ii. Right-click on Router1 and choose Start.

iii. Right-click on Router1 and choose Console. Wait a few seconds until the router is initialized.

If everything is fine, you should see the prompt shown below. This is the User EXEC mode. If the prompt does not appear, try to restart GNS3 and repeat the setup again.
Router1>


iv. To see which commands are available in this mode, type ?:

Router1>?

v. To view and change system parameters of a Cisco router, you must enter the Privileged EXEC mode by typing:

Router1>enable

Router1#

vi. Type the following command to disable the Privileged EXEC mode
Router1# disable

NOTE: The Cisco routers in GNS3 sometimes start up in 

Privileged instead of the User EXEC mode.


vii. To modify system wide configuration parameters, you must enter the global configuration mode. This mode is entered by typing:

Router1#configure terminal

Router1(config)#

or

Router1#conf t

Router1(config)#


viii. To make changes to a network interface, enter the interface configuration mode, with the
command:

Router1(config)#interface FastEthernet0/0

Router1(config-if)#

The name of the interface is provided as an argument. Here, the network interface that is configured is FastEthernet0/0.
ix. To return from the interface configuration to the global configuration mode, or from the global configuration mode to the Privileged EXEC mode, use the exit command:

Router1(config-if)#exit

Router1(config)#exit

Router1#


The exit command takes you one step up in the command hierarchy. To directly return to the Privileged EXEC mode from any configuration mode, use the end command:

Router1(config-if)#end

Router1#


x. To terminate the console session from the User EXEC mode, type logout or exit:

Router1>logout

Router con0 is now available

Press RETURN to get started


1. Configuring a Cisco Router via the console
The following exercises use basic commands from the Cisco IOS that are needed to configure aCisco router.

i. Right-click on Router1 and choose Start.

ii. Right-click on Router1 and choose Console. Wait some 
seconds until the initial console window is set up. When the router is ready to receive commands, proceed to the next step.

iii. Configure Router1 and Router 2 with the IP addresses given in Figure 7.7.

In Router 1

Interface Fastethernet0/0 in global configuration mode
R1(config)#inter f 0/0

R1(config-if)#ip address 10.0.0.1 255.0.0.0

R1(config-if)#no shutdown

R1(config-if)#exit

Interface Serial 2/0

R1(config)#inter s2/0

R1(config-if)#ip address 20.0.0.1 255.0.0.0

R1(config-if)#clock rate 64000

R1(config-if)#encapsulation ppp

R1(config-if)#no shutdown

R1(config-if)#exit


In Router 2

Interface Fastethernet 0/0

R2(config)#inter f0/0

R2(config-if)#ip address 30.0.0.1 255.0.0.0

R2(config-if)#no shutdown

R2(config-if)#exit

Interface Serial 2/0

R2(config)#inter s2/0

R2(config-if)#ip address 20.0.0.2 255.0.0.0

R2(config-if)#encapsulation ppp

R2(config-if)#no shutdown

Note: In IOS Mode under Global Configuration,we can enable or disable IP Forwarding. When it is disabled it also deletes the contents of the routing table.

Router1(config)#ip routing
Router1(config)#no ip routing

In IOS Mode under Interface Configuration,we can enable or disable a network interface

Router1(config-if)#no shutdown
Router1(config-if)#shutdown


Tip: “no ip routing” is used to guarantee that the routing cache is empty, not routing table.

R2(config-if)#exit


iv. When you are done, use the following command to check the changes you made to the router configuration, and save the outputs:

R1# show interfaces

R1#show running-config


v. Assign ip address for both PC's as mentioned in Figure 7.7 with appropriate ip and subnetmask and default gateway.


3. Setting static routing table entries on a Cisco router In this exercise, you will add static routes to the routing table of Router1. The routing table must be configured so that it conforms to the network topology shown in Figure 7.7. The routes are configured manually, which is also referred to as static routing.


The IOS command to configure static routing is ip route. The command can be used to show, clear, add, or delete entries in the routing table. The commands are summarized in the list below.


Tip to save Time: It will be tiring to manually type in the configuration data for a router, everytime you set a lab, you can save time by saving all this configurations in an excel file and simply copying and pasting in the router console window.

Note : Whenever an IP address is configured for a network interface on a router, routing table entries for the directly connected network are added automatically.


By default, Routers know only directed connected networks here Router 1 know only 10.0.0.0 and 20.0.0.0 it doesn't know the 30.0.0.0 like this R2 doesn't know about 10.0.0.0.So we are going to add Static route to this both router.


R1(config)#ip route Destination Network| Destination N/W SubnetMask |Next Hop Address


In Router R1,just give this command, in this case Destination is 30.0.0.0 and its subnet mask is 255.0.0.0 next hop address is 20.0.0.2


R1(config)#ip route 30.0.0.0 255.0.0.0 20.0.0.2

In Router R2

R2(config)#ip route 10.0.0.0 255.0.0.0 20.0.0.1

Now both routers know all networks.


i. Issue a ping command from PC1 to PC2, Router1 and PC4, respectively

ii. Save the captured Wireshark output.

iii. Use the saved data to answer the following questions:

• What is the output on PC1 when the ping commands are issued?

• Which packets, if any, are captured by Wireshark?

• Do you observe any ARP packets? If so, what do they 
indicate?

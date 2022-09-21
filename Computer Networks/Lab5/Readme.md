## Lab 5

1. Design network configuration shown in Figure 6.29 for all parts. Connect all four VMs to a single Ethernet segment via a single hub as shown in Figure 6.29. Configure the IP addresses for the PCs as shown in Table 6.1.


a. On PC1, view the ARP cache with show arp


b. Start Wireshark on PC1-Hub1 link with a capture filter set to the IP address of PC2.


c. Issue a ping command from PC1 to PC2: PC1% ping 10.0.1.13 –c 3

Observe the ARP packets in the Wireshark window. Explore the 
MAC addresses in the

Ethernet headers of the captured packets.
Direct our attention to the following fields:


• The destination MAC address of the ARP Request packets.


• The Type Field in the Ethernet headers of ARP packets.


d. View the ARP cache again with the command arp -a. Note that ARP cache entries can get refreshed/deleted fairly quickly (~2 minutes).


show arp


e. Save the results of Wireshark.


1. To observe the effects of having more than one host with the same (duplicate) IP address in a network.

After completing Exercise 1, the IP addresses of the Ethernet interfaces on the four PCs are as shown in Table 6.2 below. Note that PC1 and PC4 are assigned the same IP address.
Table 6.2: IP addresses


a. Delete all entries in the ARP cache on all PCs.

b. Run Wireshark on PC3-Hub1 link and capture the network traffic to and from the duplicate IP address 10.0.1.11.
c. From PC3, issue a ping command to the duplicate IP address, 10.0.1.11, by typing

PC3% ping 10.0.1.11 –c 5


d. Stop Wireshark, save all ARP packets and screenshot the ARP cache of PC3 using


the arp –a command:


PC3% arp – a


e. When you are done with the exercise, reset the IP address of PC4 to its original value as given


1. To test the effects of changing the netmask of a network configuration.

a. Design the configuration as Exercise 1 and replace the hub with a switch, two hosts (PC2 and PC4) have been assigned different network prefixes. Setup the interfaces of the hosts as follows:

VPCS IP Address of eth0 Network Mask

PC1 10.0.1.100 / 24 255.255.255.0

PC2 10.0.1.101 / 28 255.255.255.240

PC3 10.0.1.120 / 24 255.255.255.0

PC4 10.0.1.121 / 28 255.255.255.240


b. Run Wireshark on PC1-Hub1 link and capture the packets for the following scenarios

i. From PC1 ping PC3.

ii. From PC1 ping PC2.

iii. From PC1 ping PC4.

iv. From PC4 ping PC1.

v. From PC2 ping PC4.

vi. From PC2 ping PC3.


c. Save the Wireshark output to a text file (using the “Packet Summary” option from “Print”) , and save the output of the ping commands. Note that not all of the above scenarios are successful. Save all the output including any error messages.


d. When you are done with the exercise, reset the interfaces to their original values as given Table 6.1. (Note that /24 corresponds to network mask 255.255.255.0. and /28 to network
mask 255.255.255.240).

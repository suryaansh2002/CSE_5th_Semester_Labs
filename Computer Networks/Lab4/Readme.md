## Lab 4


1. While tcpdump host your_host is running in one command window, run ping 127.0.0.1 from another command window. From the ping output, is the 127.0.0.1 interface on? Can you see any ICMP message sent from your host in the tcpdump output? Why?


2. While tcpdump host your_host is running to capture traffic from your machine, execute telnet 128.238.66.200. Note there is no host with this IP address in the current configuration of the lab network. Save the tcpdump output of the first few packets for the lab report. After getting the necessary output, terminate the telnet session. From the saved tcpdump output, describe how the ARP timeout and retransmission were performed. How many attemps were made to resolve a
non-existing IP address?



3. Explain briefly the purposes of the following tcpdump expressions.


a. tcpdump udp port 520

b. tcpdump -x -s 120 ip proto 89

c. tcpdump -x -s 70 host ip addr1 and (ip addr2 or ip addr3)

d. tcpdump -x -s 70 host ip addr1 and not ip addr2

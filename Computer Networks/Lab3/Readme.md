## Lab 3

1. Write a UDP client-server program where client sends rows of a matrix and the server combines them together as a matrix.


2. Write a Client program to send a manually crafted HTTP request packet to a Web Server and display all fields received in HTTP Response at client Side.


2. Analyzing UDP datagrams using Wireshark:


 Start your web browser and clear the browser's cache memory, but do not access any website yet.

 Open Wireshark and start capturing.

 Go back to your web browser and retrieve any file from a website. Wireshark starts capturing packets.

 After enough packets have been captured, stop Wireshark and save the captured file.

 Using the captured file, analyze TCP & UDP packets captured
Note: DNS uses UDP for name resolution , HTTP uses TCP.
Using the captured information, answer the following questions in your lab report.


A. In the packet list pane, select the first DNS packet. In the packet detail pane, select the
User Datagram Protocol. The UDP hexdump will be highlighted in the packet byte lane.


Using the hexdump, Answer the following:

a. the source port number.

b. the destination port number.

c. the total length of the user datagram.

d. the length of the data.

e. whether the packet is directed from a client to a server or vice versa.

f. the application-layer protocol.

g. whether a checksum is calculated for this packet or not.


B. What are the source and destination IP addresses in the DNS query message? What are those addresses in the response message? What is the relationship between the two?


C. What are the source and destination port numbers in the query message? What are those addresses in the response message? What is the relationship between the two? Which port
number is a well-known port number?


D. What is the length of the first packet? How many bytes of payload are carried by the first packet?


2b. Analyzing TCP packets using Wireshark:

Start your web browser and clear the browser's cache memory, but do not access any website yet.

■ Open Wireshark and start capturing.

■ Go back to your web browser and retrieve any file from a website. Wireshark starts capturing packets.

■ After enough packets have been captured, stop Wireshark and save the captured file.

■ Using the captured file, select only those packets that use the service of TCP. For this purpose, type tcp (lowercase) in the filter field and press Apply. The packet list pane of the Wireshark window should now display a bunch of packets.


Part I: Connection-Establishment Phase


Identify the TCP packets used for connection establishment. 


Note that the last packet used for connection establish may have the application-layer as the source protocol.


Questions


Using the captured information, answer the following question in your lab report about packets


used for connection establishment.


1. What are the socket addresses for each packet?

2. What flags are set in each packet?

3. What are the sequence number and acknowledgment number of each packet?

4. What are the window size of each packet?


Part II: Data-Transfer Phase


The data-transfer phase starts with an HTTP GET request message and ends with an HTTP OK message.


Questions


Using the captured information, answer the following question in your lab report about packets used for data transfer.


1. What TCP flags are set in the first data-transfer packet (HTTP GET message)?


2. How many bytes are transmitted in this packet?


3. How often the receiver generates an acknowledgment? To which acknowledgment rule (defined in Page 200 in the textbook) does your answer corresponds to?


4. How many bytes are transmitted in each packet? How are the sequence and acknowledgment numbers related to number of bytes transmitted?


5. What are the original window sizes that are set by the client and the server? Are these numbers expected? How do they change as more segments are received by the client?


6. Explain how the window size is used in flow control?


7. What is purpose of the HTTP OK message in the data transfer phase?


Part III: Connection Termination Phase


The data-transfer phase is followed by the connection termination phase. Note that some packets used in the connection-termination phase may have the source or sink protocol at the application layer. Find the packets used for connection termination.


Questions


Using the captured information, answer the following question in your lab report about packets used for connection termination.


1. How many TCP segments are exchanged for this phase?

2. Which end point started the connection termination phase?

3. What flags are set in each of segments used for connection termination?

## Lab 1


Write an iterative TCP client server ‘C’ program


1. Rewrite the above solved program using modular programming techniques using
following modules at least.


CreateClientSocket(): Creates a Socket and establishes connection to server at
given IP address and port. (At client program)


CreateServerSocket(): Create a Socket and accepts connections from various
clients and creates client specific socket for each.


PerformClientTask() : Worker function at client side.


PerformServerTask() : Worker function at server side.


TerminateSocket() ...etc with suitable arguments list.


2. DayTime Server: Where client sends request to time server to send current time.
Server responds to the request and sends the current time of server to client. [Hint:
read man pages of asctime() and localtime()] . Display server process id at client side
along with time.


3. Write a TCP client which sends sentences to a server program. Server displays the
sentence along with client IP and ephemeral port number. Server then responds to the
client by echoing back the sentence in uppercase. The process continues until one of
them types “QUIT”.

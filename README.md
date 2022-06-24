# Tic-tac-toe-Multithreaded-Server
I have used the Multithreaded client-server model to create a client server based, multiplayer tic-tac-toe game. Two players will connect to the server in order to play the game. Mutex locks the turn of each player so that they do not make simultaneous moves. 


## How to run the project:
Install ruby and c++ on your computer.

### Server side:
Open the terminal and run the following command-

`g++ server.cpp -lpthread`

` ./a.out `

### CLient side:
Open the terminal and run the following command-

`ruby client.rb`

## Working of the project:
Multithreading is the concept of using multiple threads to execute concurrently. Various requests by different clients are assigned different threads by the server, so that the requests can be processed concurrently. 

Client-server communication happens through socket programming. Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket(node) listens on a particular port at an IP, while the other socket reaches out to the other to form a connection. The server forms the listener socket while the client reaches out to the server. In order to create a *socket()*, we need to assign a *domain*(AF_INET), *type*(SOCK_STREAM, i.e. TCP in this case) as well as *protocol*(IP) to it. After creation of the socket, *bind()* function binds the socket to the address and port number specified in addr. Then *listen()* puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. 

When a client file is executed, it sends a request to the server to exeute a fileUsing many threads would lead to a situation where two threads are accessing the same code or the same shared variable and there is a possibility of wrong output. To tackle this situation we use mutex locks to allow only one thread to access the shared code and do the necessary changes and synchronize all the threads. Using too many threads may also slow down. In order to tackle this problem, we would be using a thread pool having a definite number of threads and with the use of mutex we would be assigning each request to a thread. This would speed up the response time and would aim for more user satisfaction.

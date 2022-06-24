# Tic-tac-toe-Multithreaded-Server
I have used the Multithreaded client-server model to create a client server based, multiplayer tic-tac-toe game. Two players will connect to the server in order to play the game. Mutex locks the turn of each player so that they do not make simultaneous moves. 
##How to run the project:
Install ruby and c++ on your computer.
###Server side:
Open the terminal and run the following command-
'g++ server.cpp -lpthread'
'./a.out'
###CLient side:
Open the terminal and run the following command-
'ruby client.rb'
##Working of the project:
Multithreading is the concept of using multiple threads to execute concurrently. In order to make the server more responsive we would assign the requests to different threads, so that the maximum number of requests can be processed concurrently. Using many threads would lead to a situation where two threads are accessing the same code or the same shared variable and there is a possibility of wrong output. To tackle this situation we use mutex locks to allow only one thread to access the shared code and do the necessary changes and synchronize all the threads. Using too many threads may also slow down. In order to tackle this problem, we would be using a thread pool having a definite number of threads and with the use of mutex we would be assigning each request to a thread. This would speed up the response time and would aim for more user satisfaction.

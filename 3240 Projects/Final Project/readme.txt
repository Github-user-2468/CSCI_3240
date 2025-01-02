Project Overview 
This project aims to implement a multi-user chat server using a client-server model with thread- based concurrent programming. The goal for this project is to provide mental health support group for users to anonymously connect and support each other. This project allows multiple clients to connect and communicate in real time. It has the capacity to handle and manage multiple clients using threads to handle each of the clients independently. The client side will allow the user to send and receive messages with each other, while the server side of the project will manage the communication between the clients, ensuring that the messages are properly routed and are displayed to all clients connected to the server. This project will demonstrate socket programming and thread based concurrency.

DEMO VIDEO:
https://www.youtube.com/watch?v=wg8cr6dMA20&ab_channel=Blah

---------------------------How to run the project-------------------------------

This project was programmed and tested inside the jupyter hub enviroment

1.) load files into jupyter hub

2.) in a terminal window compile program files using "make" command 

EX: (base) jovyan@jupyter-kas2dq:~/FINAL$ make

3.) Run the server using ./server <port number>
EX (base) jovyan@jupyter-kas2dq:~/FINAL$ ./server 3240

4.) Starting client connection in terminal use ./client localhost <port number used in server call> 
EX (base) jovyan@jupyter-kas2dq:~/TRYING FINAL$ ./client localhost 3240

5.) To exit the client connection  type ctrl + c or exit in the client chat

6.) To terminate the server type ctrl+C


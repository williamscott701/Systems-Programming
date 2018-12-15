Goal:
In a client-server program
	- Send a message string from the client to the server.
	- Server should print the message on it’s console.
	- Server should reply with reversing the message string. Reversing needs to be done at the Server side.
	- Client should print the reversed message received from the server on it’s console.


Commands:
	- gcc server.c -o server
	- gcc client.c -o client
	- ./server
	- ./client 178.0.0.1

How to Run:
	- Run the server first
	- Run the client passing ip address as a command line argument (./client 178.0.0.1)
	- Input a string in the client

Working
	- the input taken in the client is sent to sever
	- that output is printed in the server
	- reverse is calculated
	- sent back to client
	- client prints the reverse sent by server
Goal:
Create Banking application that provides a live chat facility as a customer care service.

So multiple clients can connect to the representative/server and exchange messages with it. The server may receive all messages over a single window but a reply from the server must reach ​(a) the respective client only​ and ​(b) depending on order of message(query) arrival​.

Scenario: ​Client 1’s query/message came first and before server could reply to Client 1, server has a query from Client 2.

Solution:​ First ​appropriate reply ​from the Server will go to Client 1 and the second appropriate reply​ from the Server goes to Client 2. You may make other necessary assumptions and state them clearly in the readme file. (By appropriate reply we mean that Server must respond with the correct response according to the query of the client.)

How to Run?
- Compile the server.c and client.c
    - gcc server.c -o server -lpthread
    - gcc client.c -o client
- Run the server first
    - ./server
- Then run the client passing the IP address
    - ./client 127.0.0.1 (please give your local host IP address)

Features:
- Try running multiple clients and connect to the same sever.
- The server will respond to the clients appropriately
- Thread is used to create multiple connections
- Max of 40 connections can be given.
- server and client will exit the connection if exit message is sent, in client or server

References:
- GeeksForGeeks

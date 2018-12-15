
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

//Defining port variable in PORT so that we can use it globally
#define PORT 5555

//taking IP address as the first argument

int main(int argc, char *argv[]) {

    //initializing sock variable with 0, we will be using this to check if the socket creation is successful
    int sock = 0;


    //using the default struct sockaddr_in for setting server settings
    struct sockaddr_in serv_addr;

    //if there is no IP address passed in the command line argument, returning -1
    if (argc != 2) {
        printf("\n Usage: %s <Server IP address>\n", argv[0]);
        return -1;
    }

    //creating a TCP socket connection, and printing error message if not successful.
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    //reseting the bytes of data in server_addr
    memset(&serv_addr, '0', sizeof (serv_addr));


    //setting the values of the struct used, ip and port (htons is used to convert the address to host 32bit)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    //connecting using the socket and the server_addr
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    //making a infinite loop, as we want the data exchange to go on.
    while (1) {

        int readbytes = 0;
        char recvBuff[500], sendBuff[500];

        //getting the input from user using fgets
        printf("Enter Message: ");
        fgets(sendBuff, 500, stdin);

        //using this to get rid of extra garbage values
        sendBuff[strlen(sendBuff)] = 0;

        //sending the message in sendBuff to the socket
        send(sock, sendBuff, strlen(sendBuff), 0);

        //resetting the values of receive buffer before receiving
        memset(recvBuff, 0, sizeof (recvBuff));

        //reading the message from the socket and storing in recvbuffer that we cleared
        readbytes = recv(sock, recvBuff, 500, 0);

        //using this to get rid of extra garbage values
        recvBuff[readbytes] = 0;

        //checking if the server sent exit and then closing the socket if if sent
        if (strcmp(recvBuff, "exit\n") == 0) {
            close(sock);
        }
        
        //Printing the message sent by server
        printf("\nMeasage from Server: %s\n", recvBuff);
    }
    return 0;
}

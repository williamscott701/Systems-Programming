
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define PORT 5555

int main(int argc, char *argv[]) {
    
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[500], receiveBuff[500];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof (serv_addr));
    memset(sendBuff, '0', sizeof (sendBuff));
    memset(receiveBuff, '0', sizeof (receiveBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    
    
    //binds address to socket
    bind(listenfd, (struct sockaddr*) &serv_addr, sizeof (serv_addr));

    
    //Waits for clients to connect
    listen(listenfd, 5);
    printf("\nServer listening for connections!\n");

    //accepts the connection and stores the value in the connfd
    connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);
    printf("\nAccepted a connection\n");

    //receives the data, and then checks if its properly received.
    if (recv(connfd, receiveBuff, strlen(receiveBuff), 0) < 0) {
        printf("Not Received\n");
    } else {
        printf("Received : %s", receiveBuff);

        
        //logic to reverse the string
        int l = strlen(receiveBuff);

        int i = 0, j = 0, length = 0, m=0;

        //finding the length of the array as its giving some garbage value
        while (receiveBuff[length] != '\0') {
            length++;
        }

        j = length - 1;

        //storing the reverse order in sendBuff
        for (i = 0; i < length; i++) {
            sendBuff[i] = receiveBuff[j];
            j--;
        }

        //ending sendBuff to avoid garbage value
        sendBuff[i] = '\0';

        printf("Reverse: %s\n", sendBuff);
    }

    //sending the data to the client, and will check and print appropriate message.
    if (send(connfd, sendBuff, sizeof (sendBuff), 0) < 0) {
        printf("Send Error\n");
    } else {
        printf("Sent successfully\n");
    }

    //closing connection
    close(connfd);

}

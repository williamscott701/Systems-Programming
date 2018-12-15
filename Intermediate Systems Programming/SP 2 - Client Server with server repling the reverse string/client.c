
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
    int sock = 0;
    struct sockaddr_in serv_addr;

    if (argc != 2) {
        printf("\n Usage: %s <Server IP address>\n", argv[0]);
        return -1;
    }


    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) //convert IPv4 and IPv6 addresses from text to binary form
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    //connects to the server using ip and port
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char recvBuff[500], sendBuff[500];
    memset(recvBuff, '0', sizeof (recvBuff));
    memset(sendBuff, '0', sizeof (sendBuff));

    printf("Enter Message: ");

    //gets the input from user
    fgets(sendBuff, 500, stdin);

    if (send(sock, sendBuff, sizeof (sendBuff), 0) < 0) {
        printf("Send Error\n");
    } else {
        printf("Sent successfully\n");
    }

    //receives the data, and then goes to the appropriate loop.
    if (recv(sock, recvBuff, strlen(recvBuff), 0) < 0) {
        printf("Not Received\n");
    } else {
        printf("Received : %s", recvBuff);
        printf("\n");
    }

    //closing connection
    close(sock);

    return 0;
}

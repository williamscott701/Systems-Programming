
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>

#define PORT 5555

//method to have a chat functionality, taking and sending data
void *chat(void *);

//creating a global variable to store the number of clients present
int clients = 1;

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1024];

    //creating a socket setting IP and TCP in socket function
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //clearing the values in the serveraddr and sendbuffer
    memset(&serv_addr, '0', sizeof (serv_addr));
    memset(sendBuff, '0', sizeof (sendBuff));

    //setting the values for the variables in serveraddr struct
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    //binding the socket to the port.
    bind(listenfd, (struct sockaddr*) &serv_addr, sizeof (serv_addr));

    //listens or waits for the incoming connections, with limit 40
    listen(listenfd, 40);

    //maximum number of threads that we will use.
    pthread_t thread_id[40];

    int thread_index = 0;
    printf("Server Running...\n");

    //infinite loop to accept connections.
    while (connfd = accept(listenfd, (struct sockaddr*) NULL, NULL)) {
        printf("\nAccepted a connection\n");

        //creating thread. and calling the chat function
        pthread_create(&thread_id[thread_index++], NULL, chat, (void *) &connfd);

        //listens for another connections
        listen(listenfd, 40);
    }
}

//method to have a exchange messages functionality

void *chat(void *arg) {
    //incrementing the clients count on new connection
    int clientCount = clients++;
    printf("Connected to client %d\n", clientCount);
    int connfd = *(int *) arg;
    char request[1024], response[1024];
    int fd;

    while (1) {

        //file descriptor for recv
        fd = recv(connfd, request, 1024, 0);
        request[fd] = 0;

        //if exit is sent as a message, closing the connection and decrementing the clients value
        if (strcmp(request, "exit\n") == 0) {
            send(connfd, "exit", 4, 0);
            clients--;
            //closing the connection
            close(connfd);
            //exiting thread
            pthread_exit(0);
        }

        //printing the message from the client
        printf("Client Message %d : %s\n", clientCount, request);

        //getting the message from server to send to client
        printf("Enter Message: ");
        fgets(response, 1024, stdin);

        //clearing the values for garbage values
        response[strlen(response)] = 0;

        //sending the data to the connected stream
        send(connfd, response, strlen(response), 0);
    }

    return NULL;

}

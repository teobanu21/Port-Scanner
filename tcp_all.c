#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "netdb.h"

int main()
{

    int portno = 0;         // portul pe care vrem sa-l scanam
    struct in_addr address; //

    int sockfd;                   // socket descriptor

    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // creare socket

    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    // dns
    inet_aton("8.8.8.8", &address);                             // verificam portul 53 pe 8.8.8.8
    server = gethostbyaddr(&address, sizeof(address), AF_INET); // hostname of address 8.8.8.8

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    printf("%s\n", server->h_name);

    // initializarea structurii cu ajutorul careia verificam conexiuneaa

    for (int portno = 50; portno < 60; portno++)
    {
        struct sockaddr_in serv_addr; // structura care contine port + ip pt stabilirea conexiunii

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);

        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("Port %d is closed\n", portno);
        }
        else
        {
            printf("Port %d is active\n", portno);
        }
    }
    close(sockfd);
    return 0;
}
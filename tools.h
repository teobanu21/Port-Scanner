#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //pt sockets
#include <arpa/inet.h>
#include "netdb.h" //defines the hostent structure, aici folosit pentru DNS
#include "pthread.h"

#define NUMTHREADS 5
#define NUMPORTS 54

// pt functia ./main [IP address] ->scaneaza toate porturile entitatii targetate
struct ThreadData
{
    int start, stop;
    struct hostent *server;
    int sockfd;
};

// initSock()
int initSocket()
{
    int sockfd; // socket descriptor

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //  //creare socket
                                              // domain: Specifies the communications domain in which a socket is to be created
                                              //->AF_INET: address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses)
    // type: Specifies the type of socket to be created.
    //-> SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams, and may provide a transmission mechanism for out-of-band data.
    // protocol: Specifies a particular protocol to be used with the socket
    //->Specifying a protocol of 0 causes socket() to use an unspecified default protocol appropriate for the requested socket type.

    if (sockfd < 0)
    {
        printf("ERROR opening socket");
        exit(1);
    }

    return sockfd;
}

void wrongCall()
{
    printf("Usage: nscan [Option/IP] {Port} {IP}...\nTry 'nscan --help' for more information.\n");
    exit(1);
}

// verifica daca format-ul adresei IP este corect
int isValidIpAddress(char *ipAddress)
{
    // also check for number of '.' to be sure they are 4, then run the following code lines
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr)); // inet_pton - convert IPv4 and IPv6 addresses from text to binary form
                                                                //  returns 1 on success (network address was successfully converted).
                                                                //  0 is returned if src does not contain a character string representing a valid network address in the specified address family.
                                                                //  If af does not contain a valid address family, -1 is returned and errno is set to EAFNOSUPPORT.

    return result != 0;
}

void verifyConnection(int sockfd, struct sockaddr_in serv_addr, int port_no)
{
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Port %d is closed\n", port_no);
    }
    else
    {
        printf("Port %d is active\n", port_no);
    }
}

// printeaza fisiere dupa caz
void myprint(const char *filename)
{
    FILE *infile;
    char *buffer;
    long numbytes;

    infile = fopen(filename, "r");

    if (infile == NULL)
        exit(1);

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    fseek(infile, 0L, SEEK_SET);
    buffer = (char *)calloc(numbytes, sizeof(char));

    if (buffer == NULL)
        exit(1);

    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    printf("%s", buffer);

    free(buffer);

    printf("\n");
}

// todo: ip to domain_name func() for initializing struct hostent *server
struct hostent *rev_dns_convert(struct in_addr address)
{

    struct hostent *server;

    server = gethostbyaddr(&address, sizeof(address), AF_INET);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    printf("%s\n", server->h_name);

    return server;
}

// domain_name to ip for initializing struct hostent *server
struct hostent *dns_convert(const char *address)
{
    struct hostent *server;
    server = gethostbyname(address);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }

    return server;
}

// domain name to ip func for printing an ip address given a domain name -> used in printing ip in tcp_connect_dns
void dns_lookup(const char *addr_host)
{
    struct hostent *host_entity;
    char *ip = (char *)malloc(NI_MAXHOST * sizeof(char));
    int i;

    if ((host_entity = gethostbyname(addr_host)) == NULL)
    {
        return NULL;
    }

    // filling up address structure
    strcpy(ip, inet_ntoa(*(struct in_addr *)host_entity->h_addr));

    printf("IP: %s\n", ip);

}

// tcp multithread rev dns helper function
void iterate_ports(struct ThreadData *td)
{

    struct ThreadData *data = (struct ThreadData *)td;
    int start = data->start;
    int stop = data->stop;
    struct hostent *server = data->server;
    int i;

    printf("%d %d\n", start, stop);

    for (i = start; i < stop; i++)
    {
        struct sockaddr_in serv_addr; // structura care contine port + ip pt stabilirea conexiunii

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(i);

        printf("Connecting to %d..\n", i);
        if (connect(data->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) > 0)
        {
            printf("Port %d is active\n", i);
        }
    }

    // return NULL;
}

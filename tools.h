#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>     //pt sockets
#include <arpa/inet.h>
#include "netdb.h"          //defines the hostent structure, aici folosit pentru DNS
#include "pthread.h"

#define NUMTHREADS 5
#define NUMPORTS 54

//pt functia ./main [IP address] ->scaneaza toate porturile entitatii targetate
struct ThreadData
{
    int start, stop;
    struct hostent *server;
    int sockfd;
};

//initSock() todo...


//verifica daca format-ul adresei IP este corect
int isValidIpAddress(char *ipAddress)
{
    //also check for number of '.' to be sure they are 4, then run the following code lines
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

//printeaza fisiere dupa caz
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

//todo: ip to domain_name func() more precisely a rev dns func 


//domain name to ip func -> dns functionality
char *dns_lookup(const char *addr_host, int PORT_NO)
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

    return ip;
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
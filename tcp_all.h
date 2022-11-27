#pragma once
#include "tools.h"

//pentru tcp_all
#define NUMTHREADS 5
#define NUMPORTS 54

// pt functia ./main -scan [IP address] ->scaneaza toate porturile entitatii targetate
struct ThreadData
{
    int start, stop;
    struct hostent *server;
    int sockfd;
};

// function for iterating through all ports
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
}

void tcp_all(const char *addr_read)
{
    struct in_addr address;
    struct hostent *server;
    int sockfd = initSocket();

    if (isValidIpAddress(addr_read))
    {
        inet_aton(addr_read, &address);
        server = rev_dns_convert(address);
    }
    else
    {
        dns_lookup(addr_read);
        server = dns_convert(addr_read);
    }

    // this stays for now
    int tasksPerThread = (NUMPORTS + NUMTHREADS - 1) / NUMTHREADS;

    struct ThreadData data[NUMTHREADS];

    for (int i = 0; i < NUMTHREADS; i++)
    {
        data[i].start = i * tasksPerThread;
        data[i].stop = (i + 1) * tasksPerThread;
        data[i].sockfd = sockfd;
        data[i].server = server;
    }

    data[NUMTHREADS - 1].stop = NUMPORTS;
    pthread_t thread[NUMTHREADS];

    for (int i = 0; i < NUMTHREADS; i++)
    {
        pthread_create(&thread[i], NULL, iterate_ports, &data[i]);
    }

    for (int i = 0; i < NUMTHREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    close(sockfd);
}
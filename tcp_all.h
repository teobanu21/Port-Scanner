#pragma once
#include "tools.h"

// pentru tcp_all
#define NUMTHREADS 5
#define NUMPORTS 54

// pt functia ./main -scan [IP address] ->scaneaza toate porturile entitatii targetate
struct ThreadData
{
    int start, stop;
    struct hostent *server;
    int sockfd;
    const char *address;
};

// function for iterating through all ports
void iterate_ports(struct ThreadData *td)
{
    struct ThreadData *data = (struct ThreadData *)td;
    int start = data->start;
    int stop = data->stop;
    struct hostent *server = data->server;
    int i;

    char addr[17];
    strcpy(addr, td->address);

    printf("%d %d\n", start, stop);

    for (i = start; i < stop; i++)
    {
        printf("Connecting to %d..\n", i);

        int port = i;
        fd_set fdset;
        struct timeval tv;

        struct sockaddr_in serv_addr; // structura care contine port + ip pt stabilirea conexiunii

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;

        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(i);

        serv_addr.sin_addr.s_addr = inet_addr(addr);

        td->sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if(td->sockfd < 0)
        {
            exit(0);
        }

        fcntl(td->sockfd, F_SETFL, O_NONBLOCK);
        connect(td->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        FD_ZERO(&fdset);
        FD_SET(td->sockfd, &fdset);
        tv.tv_sec = 10; // 5sec timeout
        tv.tv_usec = 0;

        if (select(td->sockfd + 1, NULL, &fdset, NULL, &tv) == 1)
        {
            int so_error;
            socklen_t len = sizeof(so_error);

            getsockopt(td->sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);

            if (so_error == 0)
            {
                printf("%s:%d is open \n", addr, port);
            }
        }

        close(td->sockfd);
        // if (connect(data->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) > 0)
        // {
        //     printf("Port %d is active\n", i);
        // }
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
        //data[i].sockfd = sockfd;
        data[i].server = server;
        data[i].address = strdup(addr_read);
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
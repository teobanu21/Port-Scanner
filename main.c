#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "tcp_connect_rev_dns.h"
#include "tcp_connect_dns.h"

// todo:
// check if command is wrong for argv[1]

int main(int argc, char *argv[])
{
    // program side
    if (argc == 1) // apel incorect al programului => mini descriere a modului in care trebuie apelat programul
    {
        myprint("_ascii_art.txt");
        printf("\n\nPress any key to continue...");
        getchar();
    }
    else if (argc == 2) // doar pentru cazul cu --help
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            system("clear");
            myprint("_man.txt");
        }
        else
        {
            wrongCall();
        }
    }
    else if (argc == 3) // to do scan all ports for given domain name
    {                   
        //tcp_all pt given ip
        if (strcmp(argv[1], "--ip") == 0 && isValidIpAddress(argv[2])) // fix isValidIpAddress()!!! works for invalid ip addresses like 32.3
        {
            // initSock()
            struct in_addr address; //
            int sockfd;             // socket descriptor
            struct hostent *server;

            sockfd = socket(AF_INET, SOCK_STREAM, 0); // creare socket

            if (sockfd < 0)
            {
                printf("ERROR opening socket");
                exit(1);
            }

            // todo: reverse dns func()
            inet_aton(argv[2], &address);
            server = gethostbyaddr(&address, sizeof(address), AF_INET);

            if (server == NULL)
            {
                fprintf(stderr, "ERROR, no such host\n");
                exit(0);
            }

            printf("%s\n", server->h_name);

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
        else if (strcmp(argv[1], "--file") == 0)
        {
            //todo...
        }
        else
        {
            wrongCall();
        }
    }
    else if (argc == 4) // argv[2] = port si argv[3] = ip
    {
        if (strcmp(argv[1], "--port") == 0)
        {
            printf("./main --port %d %s\n", atoi(argv[2]), argv[3]);
            if (isValidIpAddress(argv[3]))
            {
                tcp_connect_rev_dns(argv[3], atoi(argv[2]));
            }
            else
            {
                tcp_connect_dns(argv[3], atoi(argv[2]));
            }
        }
    }
    return 0;
}
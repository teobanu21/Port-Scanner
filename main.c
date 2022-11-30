#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "tcp_connect_rev_dns.h"
#include "tcp_connect_dns.h"
#include "tcp_all.h"
#include "tcp_file.h"
#include "myping.h"

// todo:
// check if command is wrong for argv[1]

int main(int argc, char *argv[])
{

    // program side
    struct timeval start = getTime();
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
            system("man ./_man.1");
            exit(0);
        }
        else
        {
            wrongCall();
            exit(-1);
        }
    }
    else if (argc == 3) // to do scan all ports for given domain name
    {
        // tcp_all pt given ip
        if (strcmp(argv[1], "--scan") == 0)
        {
            if (isValidIpAddress(argv[2]))
            {
                tcp_all(argv[2]);
            }
            else
            {
                // struct hostent *host_entity;
                char *ip = (char *)malloc(NI_MAXHOST * sizeof(char));
                ip = dns_lookup(argv[2]);
                tcp_all(ip);
            }

            //printExecutionTime(start);
            calculateTime(start);
            exit(0);
        }
        else if (strcmp(argv[1], "--file") == 0)
        {
            tcp_file(argv[2]);
            calculateTime(start);
            exit(0);
        }
        else if (strcmp(argv[1], "--ping") == 0)
        {
            int sockfd;
            char *ip_addr, *reverse_hostname;
            struct sockaddr_in addr_con;
            int addrlen = sizeof(addr_con);
            char net_buf[NI_MAXHOST];

            ip_addr = dns_lookup_ping(argv[2], &addr_con);
            if (ip_addr == NULL)
            {
                printf("\nDNS lookup failed! Could not resolve hostname!\n");
                exit(-1);
            }

            reverse_hostname = reverse_dns_lookup(ip_addr);
            printf("\nTrying to connect to '%s' IP: %s\n", argv[2], ip_addr);
            printf("\nReverse Lookup domain: %s", reverse_hostname);

            // socket()
            sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
            // sockfd = initSocket();
            if (sockfd < 0)
            {
                printf("\nSocket file descriptor not received!!\n");
                exit(-1);
            }
            else
            {
                printf("\nSocket file descriptor %d received\n", sockfd);
                // signal(SIGINT, intHandler); // catching interrupt
                // raise(SIGINT);
            }

            signal(SIGINT, intHandler);

            // send pings continuously
            send_ping(sockfd, &addr_con, reverse_hostname, ip_addr, argv[2]);

            if (isReachable == 1)
            {
                printf("\nThe destination is reachable!\n\n");
            }

            //printExecutionTime(start);
            calculateTime(start);
            exit(0);
        }
        else
        {
            wrongCall();
            exit(-1);
        }
    }
    else if (argc == 4) // argv[2] = port si argv[3] = ip
    {
        if (strcmp(argv[1], "--port") == 0)
        {
            printf("nscan --port %d %s\n", atoi(argv[2]), argv[3]);

            if (atoi(argv[2]) == 0)
            {
                exit(-1);
            }

            if (isValidIpAddress(argv[3]))
            {
                // printf("ip\n");
                tcp_connect_rev_dns(argv[3], atoi(argv[2]));
            }
            else
            {
                // printf("domain");
                tcp_connect_dns(argv[3], atoi(argv[2]));
            }

            //printExecutionTime(start);
            calculateTime(start);
            exit(0);
        }
        else
        {
            wrongCall();
            exit(-1);
        }
    }

    return 0;
}
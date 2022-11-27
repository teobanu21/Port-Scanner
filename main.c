#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "tcp_connect_rev_dns.h"
#include "tcp_connect_dns.h"
#include "tcp_all.h"
#include "myping.h"

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
        // tcp_all pt given ip
        if (strcmp(argv[1], "--scan") == 0)
        {
            tcp_all(argv[2]);
        }
        else if (strcmp(argv[1], "--file") == 0)
        {
            //put --file into a header
            FILE *f = fopen(argv[2], "r");

            if (f == NULL)
            {
                printf("Error opening the file\n");
                exit(1);
            }

            printf("Reading from: %s\n", argv[2]);
            char addr[60];

            while (fgets(addr, 60, f))
            {
                if (strchr(addr, '\n') != 0)
                {
                    addr[strlen(addr) - 1] = '\0';
                }

                tcp_all(addr);
            }

            fclose(f);
        }
        else if (strcmp(argv[1], "--ping") == 0)
        {
            //put --ping in a header file 
            int sockfd;
            char *ip_addr, *reverse_hostname;
            struct sockaddr_in addr_con;
            int addrlen = sizeof(addr_con);
            char net_buf[NI_MAXHOST];

            ip_addr = dns_lookup_ping(argv[2], &addr_con);
            if (ip_addr == NULL)
            {
                printf("\nDNS lookup failed! Could not resolve hostname!\n");
                return 0;
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
                return 0;
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
                printf("\nThe destination is reachable, you can start scanning!\n\n");
            }
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
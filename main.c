#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "tcp_connect_rev_dns.h"
#include "tcp_connect_dns.h"

int main(int argc, char *argv[])
{
    // program side
    if (argc == 1)
    {
        myprint("_ascii_art.txt");
        printf("\n\nPress any key to continue...");
        getchar();
        // system("gnome-terminal");
    }
    else if (strcmp(argv[1], "--port") == 0)
    {
        printf("./main --ports %s %d\n", argv[3], atoi(argv[2]));
        if (isValidIpAddress(argv[3]))
        {
            tcp_connect_rev_dns(argv[3], atoi(argv[2]));
        }
        else
        {
            tcp_connect_dns(argv[3], atoi(argv[2]));
        }
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        system("clear");
        myprint("_man.txt");
    }

    return 0;
}
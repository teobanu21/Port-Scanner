#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //pt sockets
#include <arpa/inet.h>
#include "netdb.h" //defines the hostent structure, aici folosit pentru DNS

int isValidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

void myprint(const char* filename)
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
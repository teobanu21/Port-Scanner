#include "tools.h"

void tcp_connect(const char* addr, int port_no){
    struct in_addr address;         // 

    int sockfd;                     // socket descriptor
    struct sockaddr_in serv_addr;   // structura care contine port + ip pt stabilirea conexiunii
    
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);        //creare socket
                                                     //domain: Specifies the communications domain in which a socket is to be created
                                                        //->AF_INET: address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses)
                                                     //type: Specifies the type of socket to be created.
                                                        //-> SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams, and may provide a transmission mechanism for out-of-band data.
                                                     //protocol: Specifies a particular protocol to be used with the socket 
                                                        //->Specifying a protocol of 0 causes socket() to use an unspecified default protocol appropriate for the requested socket type.
    
    if (sockfd < 0)
    {
        printf("Socket failed\n");
    }
    
    //dns server
    inet_aton(addr, &address);                                      //verificam portul 53 pe 8.8.8.8
    server = gethostbyaddr(&address, sizeof(address), AF_INET);     //hostname of address 8.8.8.8

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

     printf("%s\n", server->h_name);

//initializarea structurii cu ajutorul careia verificam conexiunea
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port_no);
   
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Port is closed\n");
    }
    else
    {
        printf("Port is active\n");
    }

    close(sockfd);
}
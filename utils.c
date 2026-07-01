#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>

void initialize_socklib()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET createtcpipv4sock()
{
    SOCKET socketfd;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    return socketfd;
}
struct sockaddr_in *createipv4address(char *ip, int port)
{
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_port = htons(port);
    address->sin_family = AF_INET;
    if (strlen(ip) == 0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

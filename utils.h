#ifndef UTILS_H
#define UTILS_H

#include <winsock2.h>
#include <ws2tcpip.h>

void initialize_socklib(void);

SOCKET createtcpipv4sock(void);

struct sockaddr_in *createipv4address(char *ip, int port);

#endif
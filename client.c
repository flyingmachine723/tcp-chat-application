#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
DWORD WINAPI recievemessage(LPVOID arg)
{
    SOCKET socketfd = *(SOCKET *)(arg);
    char buffer[1025];
    while (1)
    {
        int bytes = recv(socketfd, buffer, sizeof(buffer), 0);
        if (bytes <= 0)
            break;
        buffer[bytes] = '\0';
        printf("\r%s\n", buffer);
    }
    return 0;
}
int main()
{
    initialize_socklib();
    SOCKET socketfd;

    socketfd = createtcpipv4sock();
    char ip[100];
    printf("Enter the server ip:");
    scanf("%99s", ip);

    struct sockaddr_in *address = createipv4address(ip, 8080);

    int result = connect(socketfd, (struct sockaddr *)address, sizeof(struct sockaddr_in));

    if (result != 0)
    {
        printf("Connection failed\n");
        closesocket(socketfd);
        return 1;
    }

    printf("connection was successful\n");

    printf("Enter Username:");
    char name[100];

    scanf(" %99[^\n]", name);
    send(socketfd, name, strlen(name), 0);

    CreateThread(NULL, 0, recievemessage, &socketfd, 0, NULL);
    while (1)
    {
        char msg[1024];

        scanf(" %1023[^\n]", msg);
        if (strcmp(msg, "exit") == 0)
            break;
        send(socketfd, msg, strlen(msg), 0);
    }
    closesocket(socketfd);
    return 0;
}
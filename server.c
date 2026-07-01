#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
struct acceptedsocket
{
    char username[100];
    SOCKET clientsocket;
    struct sockaddr_in address;
    int error;
    bool acceptedsuccessfully;
};
struct acceptedsocket *acceptincomingconnections(SOCKET serversocket)
{
    struct acceptedsocket *Acceptedsocket = malloc(sizeof(struct acceptedsocket));
    struct sockaddr_in address;
    int addressize = sizeof(struct sockaddr_in);

    Acceptedsocket->clientsocket = accept(serversocket, (struct sockaddr *)&address, &addressize);
    Acceptedsocket->address = address;
    Acceptedsocket->acceptedsuccessfully = Acceptedsocket->clientsocket != INVALID_SOCKET;
    if (!Acceptedsocket->acceptedsuccessfully)
    {
        Acceptedsocket->error = WSAGetLastError();
        ;
    }
    return Acceptedsocket;
}
struct acceptedsocket *clients[100];
static int clientsconnected = 0;
DWORD WINAPI handleclient(LPVOID arg)
{
    struct acceptedsocket *client = (struct acceptedsocket *)arg;
    char buffer[1024];
    char temp[1024];
        int recievedbytes = recv(client->clientsocket, temp, sizeof(temp), 0);
        if (recievedbytes > 0)
        {
            temp[recievedbytes] = '\0';
            strcpy(client->username,temp);
        }
    while (1)
    {
        int bytes = recv(client->clientsocket, buffer, sizeof(buffer), 0);
        if (bytes <= 0)
            break;
        buffer[bytes] = '\0';
        if (strcmp(buffer, "exit") == 0)
            break;
        char name[1024];
        strcpy(name,client->username);
        strcat(name, ":");
        strcat(name, buffer);
        for (int i = 0; i < clientsconnected; i++)
        {
            if (clients[i]->clientsocket != client->clientsocket)
                send(clients[i]->clientsocket,name, strlen(name), 0);
        }
    }
    closesocket(client->clientsocket);
    free(client);
    return 0;
}

int main()
{
    initialize_socklib();
    SOCKET serversocket;
    serversocket = createtcpipv4sock();
    struct sockaddr_in *address = createipv4address("", 8080);         // done to listen to all possible addresses of the server
    bind(serversocket, (struct sockaddr *)address, sizeof(struct sockaddr_in)); // bind accepts struct sockaddr* not struct sockaddr_in*
    listen(serversocket, 100);
    int i = 0;
    while (1)
    {
        clients[i] = acceptincomingconnections(serversocket);
        if (clients[i]->acceptedsuccessfully)
        {
            printf("client%d connected\n", i + 1);
            clientsconnected++;
        }
        else
            printf("Couldnt connect to client error code:%d", clients[i]->error);
        CreateThread(NULL, 0, handleclient, clients[i], 0, NULL);
        i++;
    }
    return 0;
}
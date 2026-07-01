# TCP Chat Application

A multithreaded client-server chat application built in **C** using the **Winsock API**. This project demonstrates TCP socket programming, multithreading, concurrent client handling, and real-time messaging over a Local Area Network (LAN).

## Features

* TCP client-server architecture
* Multithreaded server using Windows threads (`CreateThread`)
* Supports multiple concurrent client connections
* Real-time message broadcasting
* Username-based messaging
* LAN communication using IPv4 sockets

## Technologies Used

* C
* Winsock2
* Windows Threads (`CreateThread`)
* TCP/IP Sockets

## Project Structure

```text
.
├── client.c
├── server.c
├── utils.c
├── utils.h
└── README.md
```

## Building

Compile the server:

```bash
gcc server.c utils.c -o server.exe -lws2_32
```

Compile the client:

```bash
gcc client.c utils.c -o client.exe -lws2_32
```

## Running

1. Compile both the server and client.
2. Start `server.exe` on the host machine.
3. Find the server's local IP address using:

```cmd
ipconfig
```

4. Run `client.exe` on the client device(s).
5. Enter the server's IP address if prompted (or update the client configuration).
6. Enter a username and begin chatting.

## Concepts Demonstrated

* TCP socket programming
* Client-server architecture
* Concurrent programming with threads
* Network communication over LAN
* Message broadcasting
* Winsock API usage

## Future Improvements

* Private messaging
* Graphical user interface (GUI)
* File transfer
* End-to-end encryption
* Cross-platform support
* Internet-based communication via a cloud server

## License

This project is intended for educational purposes and to demonstrate networking concepts using C and the Winsock API.

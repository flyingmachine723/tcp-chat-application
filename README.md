# TCP Chat Application
A multithreaded client-server chat application built in **C** using the **Winsock API**. This project demonstrates TCP socket programming, multithreading, concurrent client handling, and real-time messaging over the internet using a cloud-hosted server.

## Features
* TCP client-server architecture
* Multithreaded server using Windows threads (`CreateThread`)
* Supports multiple concurrent client connections
* Real-time message broadcasting to all connected clients
* Username-based messaging
* Internet-based communication via a cloud VM (Azure)
* IPv4 socket communication

## Technologies Used
* C
* Winsock2
* Windows Threads (`CreateThread`)
* TCP/IP Sockets
* Microsoft Azure (VM hosting)

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

### Server (on the VM)
1. Deploy `server.exe` on a cloud VM (Azure in this case).
2. Ensure port `8080` is open on the VM's network security group (inbound TCP rule).
3. Ensure port `8080` is allowed through the VM's Windows Defender Firewall.
4. Run the server:
```bash
./server.exe
```
The server will start listening on `0.0.0.0:8080`, accepting connections from any client over the internet.

### Client (on any machine)
1. Update the IP address in `client.c` to the VM's public IP address.
2. Compile and run `client.exe`.
3. Enter a username when prompted.
4. Start chatting — messages are broadcast in real time to all connected clients.

## Architecture
The server runs a continuous accept loop in the main thread, spawning a dedicated `handleclient` thread for every new connection. Each thread independently handles receiving messages from its client and broadcasting them to all other connected clients. The username is captured once at the start of each thread before entering the main message loop.

```
                        +------------------+
                        |   Server (VM)    |
                        |  0.0.0.0 : 8080  |
                        +--------+---------+
                                 |
          +----------------------+----------------------+
          |                      |                      |
   +------+------+        +------+------+        +------+------+
   |   Client 1  |        |   Client 2  |        |   Client 3  |
   |  (Thread 1) |        |  (Thread 2) |        |  (Thread 3) |
   +-------------+        +-------------+        +-------------+
```

## Concepts Demonstrated
* TCP socket programming
* Client-server architecture
* Concurrent programming with threads
* Message broadcasting across multiple clients
* Winsock API usage
* Cloud VM deployment and network configuration (Azure NSG, Windows Firewall)
* Internet-based socket communication

## Future Improvements
* Private / direct messaging between specific users
* Graceful disconnect cleanup with thread-safe client removal
* CRITICAL_SECTION lock for safe concurrent access to the client list
* Graphical user interface (GUI)
* File transfer
* End-to-end encryption
* Cross-platform support (POSIX sockets for Linux/macOS)

## License
This project is intended for educational purposes and to demonstrate networking and systems programming concepts using C and the Winsock API.

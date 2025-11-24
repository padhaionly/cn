/*
    THEORY:
    -------
    UDP (User Datagram Protocol) is a connectionless transport layer protocol.
    Features:
      • No connection establishment
      • No guarantee of delivery
      • Fast and lightweight
      • Used for real-time applications (video, gaming, VoIP)

    This program implements BOTH:
        1) UDP Server
        2) UDP Client

    Server:
        • Binds to port 9090
        • Waits for a message from the client
        • Prints message
        • Sends a reply

    Client:
        • Sends a message to server (127.0.0.1:9090)
        • Waits for reply

    NOTE:
    Windows uses Winsock library for networking.
    Must compile with:  -lws2_32
*/

#define _WIN32_WINNT 0x0601
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;


// ========================= UDP SERVER =========================
void udpServer()
{
    WSADATA wsa;                                          // Winsock data structure
    WSAStartup(MAKEWORD(2, 2), &wsa);                     // Initialize Winsock

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);            // Create UDP socket

    sockaddr_in server{}, client{};                       // Server + client address structs
    server.sin_family = AF_INET;                          // IPv4
    server.sin_port = htons(9090);                        // Port 9090
    server.sin_addr.s_addr = INADDR_ANY;                  // Accept all incoming IPs

    bind(s, (sockaddr *)&server, sizeof(server));         // Bind socket to port

    cout << "UDP Server listening on port 9090...\n";

    char buffer[1024];                                    // Buffer for message
    int clientLen = sizeof(client);                       // Size of client struct

    int bytes = recvfrom(                                   // Receive message
        s, buffer, sizeof(buffer) - 1, 0,
        (sockaddr *)&client, &clientLen
    );

    buffer[bytes] = '\0';                                 // Null-terminating string
    cout << "Client: " << buffer << endl;                 // Print client message

    cout << "Enter reply: ";
    string reply;
    getline(cin, reply);                                  // Read input from user

    sendto(                                                // Send reply to client
        s, reply.c_str(), reply.size(), 0,
        (sockaddr *)&client, clientLen
    );

    closesocket(s);                                       // Close socket
    WSACleanup();                                         // Shutdown Winsock
}


// ========================= UDP CLIENT =========================
void udpClient()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);                     // Initialize Winsock

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);            // Create UDP socket

    sockaddr_in server{};
    server.sin_family = AF_INET;                          // IPv4
    server.sin_port = htons(9090);                        // Server port
    server.sin_addr.s_addr = inet_addr("127.0.0.1");      // Localhost

    cout << "Enter message: ";
    string msg;
    getline(cin, msg);                                    // Read user input

    sendto(s, msg.c_str(), msg.size(), 0,                 // Send message to server
           (sockaddr *)&server, sizeof(server));

    char buffer[1024];
    int slen = sizeof(server);

    int bytes = recvfrom(                                  // Receive server reply
        s, buffer, sizeof(buffer) - 1, 0,
        (sockaddr *)&server, &slen
    );

    buffer[bytes] = '\0';                                 // Terminate string
    cout << "Server: " << buffer << endl;                 // Print response

    closesocket(s);                                       // Cleanup
    WSACleanup();
}


// ============================= MAIN =============================
int main()
{
    int choice;

    cout << "1. UDP Server\n";
    cout << "2. UDP Client\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();                                         // Clear newline from buffer

    if (choice == 1) udpServer();                         // Start server
    else if (choice == 2) udpClient();                    // Start client
    else cout << "Invalid choice\n";

    return 0;
}


/*
    ===========================
    SAMPLE UDP RUN (COMMENTED)
    ===========================

    TERMINAL 1 (SERVER):
    ---------------------
    1. UDP Server
    2. UDP Client
    Enter choice: 1
    UDP Server listening on port 9090...
    Client: Hello Server!
    Enter reply: Hello Client!


    TERMINAL 2 (CLIENT):
    ---------------------
    1. UDP Server
    2. UDP Client
    Enter choice: 2
    Enter message: Hello Server!
    Server: Hello Client!


    COMPILATION (Windows):
    ----------------------
    g++ udp.cpp -o udp.exe -lws2_32
    .\udp.exe
*/

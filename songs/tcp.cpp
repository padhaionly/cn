/*
    THEORY:
    -------
    TCP (Transmission Control Protocol)
    ------------------------------------
    TCP is a connection-oriented protocol used for reliable data transmission.

    Features of TCP:
    ✓ Connection-based (3-way handshake)
    ✓ Guarantees data delivery
    ✓ Sends data in order
    ✓ Retransmits lost packets
    ✓ Used for web, email, file transfer, etc.

    This program implements BOTH:
        1. TCP SERVER
        2. TCP CLIENT

    TCP SERVER:
        • Creates a socket
        • Binds to port 9090
        • Listens for incoming connection
        • Accepts client
        • Receives message
        • Sends reply

    TCP CLIENT:
        • Connects to server on port 9090
        • Sends message
        • Waits for reply

    Must compile with: -lws2_32  (Windows networking library)
*/

#define _WIN32_WINNT 0x0601
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


// ============================= TCP SERVER =============================
void tcpServer()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);              // Initialize Winsock

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);   // Create TCP socket
    if (serverSocket == INVALID_SOCKET)
    {
        cerr << "Socket creation failed\n";
        return;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;                   // IPv4
    server.sin_port = htons(9090);                 // Port 9090
    server.sin_addr.s_addr = INADDR_ANY;           // Accept all incoming IPs

    // Bind socket to IP + port
    if (bind(serverSocket, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cerr << "Bind failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    listen(serverSocket, 1);                       // Listen for one connection
    cout << "TCP Server listening on port 9090...\n";

    sockaddr_in client{};
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(serverSocket, (sockaddr *)&client, &clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
        cerr << "Accept failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Client connected from " << inet_ntoa(client.sin_addr)
         << ":" << ntohs(client.sin_port) << endl;

    char buffer[1024];
    int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);  // Receive data

    if (bytes > 0)
    {
        buffer[bytes] = '\0';                     // Null-terminate string
        cout << "Client: " << buffer << endl;

        cout << "Enter reply: ";
        string reply;
        getline(cin, reply);                       // Read user reply

        send(clientSocket, reply.c_str(), reply.size(), 0);  // Send reply
    }

    closesocket(clientSocket);                    // Close client connection
    closesocket(serverSocket);                    // Close server socket
    WSACleanup();                                 // Cleanup Winsock
}


// ============================= TCP CLIENT =============================
void tcpClient()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);             // Initialize Winsock

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);   // Create TCP socket

    sockaddr_in server{};
    server.sin_family = AF_INET;                  // IPv4
    server.sin_port = htons(9090);                // Server port
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost

    // Connect to server
    if (connect(s, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cerr << "Connection failed\n";
        closesocket(s);
        WSACleanup();
        return;
    }

    cout << "Enter message: ";
    string msg;
    getline(cin, msg);                            // Read user message

    send(s, msg.c_str(), msg.size(), 0);          // Send to server

    char buffer[1024];
    int bytes = recv(s, buffer, sizeof(buffer) - 1, 0);   // Receive reply

    if (bytes > 0)
    {
        buffer[bytes] = '\0';                     // Null-terminate
        cout << "Server: " << buffer << endl;     // Print reply
    }

    closesocket(s);                               // Close socket
    WSACleanup();                                 // Cleanup Winsock
}


// ================================ MAIN ================================
int main()
{
    int choice;

    cout << "1. TCP Server\n";
    cout << "2. TCP Client\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();                                 // Clear input buffer

    if (choice == 1) tcpServer();
    else if (choice == 2) tcpClient();
    else cout << "Invalid choice\n";

    return 0;
}


/*
    ============================
    SAMPLE TCP RUN (COMMENTS)
    ============================

    TERMINAL 1 (SERVER):
    ---------------------
    1. TCP Server
    2. TCP Client
    Enter choice: 1
    TCP Server listening on port 9090...
    Client connected from 127.0.0.1:53214
    Client: Hello Server!
    Enter reply: Hello Client!


    TERMINAL 2 (CLIENT):
    ---------------------
    1. TCP Server
    2. TCP Client
    Enter choice: 2
    Enter message: Hello Server!
    Server: Hello Client!


    COMPILATION (Windows):
    ----------------------
    g++ tcp.cpp -o tcp.exe -lws2_32
    .\tcp.exe
*/

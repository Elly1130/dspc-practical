#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

int main() {
    struct sockaddr_in server_addr;

    // Create socket
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    cout << "Socket successfully created" << endl;

    // Set port and IP
    int port = 9999;
    const char* ipadd = "127.0.0.1";

    // Bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ipadd);
    server_addr.sin_port = htons(port);
    bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    cout << "Socket is listening..." << endl;

    // Start listening to client
    listen(server_sockfd, 5);

    while (true) {
        std::cout << "Server is waiting..." << endl;
        struct sockaddr_in client_addr;

        // Establish connection with client
        int client_len = sizeof(client_addr);
        int client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&client_len);

        // Pending for any client acceptance... then run the following code
        char client_addr_str[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN is 16
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_addr_str, INET_ADDRSTRLEN); // Convert IP address to string
        cout << "Server connected to " << client_addr_str << endl;

        // Respond the client with server clock time
        time_point<system_clock> now = system_clock::now(); // Get current time
        time_t time = system_clock::to_time_t(now); // Convert to time_t
        string time_str = ctime(&time); // Convert to string
        const char* time_ch = time_str.c_str(); // Convert to char array
        send(client_sockfd, time_ch, time_str.size(), 0); // Send to client
        cout << "Server send time data: " << time_ch << " with size " << time_str.size() << endl;
        cout << "Server send time to " << client_addr_str << endl;

        // Close the connection with the client process
        close(client_sockfd);
    }
    // Close the server socket
    close(server_sockfd);

    return 0;
}
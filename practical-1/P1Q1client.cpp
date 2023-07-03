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
    struct sockaddr_in client_addr;

    // Create socket
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    cout << "Socket successfully created" << endl << endl;

    // Set port and IP
    int port = 9999;
    const char* ipadd = "127.0.0.1"; // localhost

    // Bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ipadd);
    server_addr.sin_port = htons(port);

    // Establish connection with server
    int server_len = sizeof(server_addr);
    connect(server_sockfd, (struct sockaddr*)&server_addr, server_len);

    time_point<system_clock> request_time_point = system_clock::now(); // Get current time
    time_t request_time = system_clock::to_time_t(request_time_point); // Convert to time_t
    duration<double> request_time_epoch = request_time_point.time_since_epoch(); // Convert to epoch

    // Receive data from the server
    char ch[24];
    recv(server_sockfd, ch, 24, 0); 

    // Extract and print exactly 24 characters
    int size_arr = sizeof(ch) / sizeof(char);
    string str = "";
    for (int x = 0; x < size_arr; x++) {
        str = str + ch[x];
    }
    cout << "Data received from server: " << str << endl << endl;

    time_point<system_clock> response_time_point = system_clock::now(); // Get current time
    time_t response_time = system_clock::to_time_t(response_time_point); // Convert to time_t
    duration<double> response_time_epoch = response_time_point.time_since_epoch(); // Convert to epoch

    // To be fixed: cannot convert received &ch to time_t correctly
    const char* time_ch = str.c_str(); // Convert to const char*
    time_t server_time = time_t(time_ch); // Convert to time_t
    string server_time_str = ctime(&server_time); // Convert to string
    cout << "Time returned by server: " << str << endl << endl;

    time_point<system_clock> actual_time_point = system_clock::now(); // Get current time
    time_t actual_time = system_clock::to_time_t(actual_time_point); // Convert to time_t
    string actual_time_str = ctime(&actual_time); // Convert to string
    duration<double> actual_time_epoch = actual_time_point.time_since_epoch(); // Convert to epoch
    duration<double> latency_time = response_time_epoch - request_time_epoch; // Calculate latency

    microseconds::rep latency_time_milis = duration_cast<microseconds>(latency_time).count(); // Convert to microseconds
    cout << "Process Delay latency: " << latency_time_milis << " microseconds\n" << endl;
    cout << "Actual clock time at client side: " << actual_time_str.c_str() << endl;

    // Synchronize process client clock time
    time_point<system_clock> client_time_point = actual_time_point;
    // To be fixed: time_t object does not have decimal point for second, cannot do calculation below a second.
    time_t client_time = actual_time; // + (latency_time / 2); 
    string client_time_str = ctime(&client_time); // Convert to string
    duration<double> client_time_epoch = client_time_point.time_since_epoch(); // Convert to epoch
    cout << "Synchronized process client time: " << client_time_str.c_str() << endl;

    // Calculate synchronization error
    duration<double> error_time = actual_time_epoch - client_time_epoch; // Calculate error
    microseconds::rep error_time_milis = duration_cast<microseconds>(error_time).count(); // Convert to microseconds
    cout << "Synchronization error: " << error_time_milis << " microseconds" << endl;

    // Close the socket
    close(server_sockfd);

    return 0;
}


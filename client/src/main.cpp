#include "utils.h"

using namespace std;

#define PORT 8000
#define LOCALHOST "127.0.0.1"

void signal_handler(int signal) {
    if (signal == SIGINT) {
        cout << "\nShutting down the connection...\n";
        exit(0);
    }
}

int main () {

    signal(SIGINT, signal_handler);

    int client_fd = 0;
    struct sockaddr_in address;

    // create client socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // convert addresses to binary form
    if (inet_pton(AF_INET, LOCALHOST, &address.sin_addr) <= 0) {
        perror("Address not supported");
        exit(EXIT_FAILURE);
    }

    // connect to the server
    if (connect(client_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    cout << "Connected to the server on port " << PORT << "\n\n";

    while (true) {
        string request;
        cin >> request;

        send(client_fd, request.c_str(), request.size(), 0);
        cout << "Message sent: " << request << "\n\n";

        char buffer[1024] = {0};
        int bytes_read = read(client_fd, buffer, 1024);
        if (bytes_read <= 0) {
            cout << "Server disconnected\n";
            break;
        }

        cout << "Server response: \n" << buffer << "\n\n";
    }

    close(client_fd);
    return 0;
}
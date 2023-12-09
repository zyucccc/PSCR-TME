//
// Created by z yu on 06/12/2023.
//
#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include "ServerSocket.h"
#include "TCPServer.h"
#include "Socket.h"

using namespace std;
int main(int argc,char * argv[]) {

    if (argc != 3) {
        perror("error parametre");
        return -1;
    }

    string adreese_ip = argv[1];
    int port = std::stoi(argv[2]);

    pr::Socket sock;
    sock.connect(adreese_ip, port);

    std::cout << "Connected to the server." << std::endl;

    string command;
    while (true) {
        std::cout << "Enter command (LIST, UPLOAD, DOWNLOAD): ";
        std::getline(std::cin, command);
        //verifier la commande
        if (command != "LIST" && command != "UPLOAD" && command != "DOWNLOAD") {
            std::cout << "Invalid command." << std::endl;
            continue;
        }
        write(sock.getFD(), command.c_str(), command.size());
        char buffer[1024];
        ssize_t reponse = read(sock.getFD(), buffer, sizeof(buffer) - 1);
        if (reponse > 0) {
            buffer[reponse] = '\0'; //
            std::cout << "Server response: " << buffer << std::endl;
        }
    }
    sock.close();
    return 0;
}
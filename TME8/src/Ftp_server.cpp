//
// Created by z yu on 06/12/2023.
//
#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include "ServerSocket.h"
#include "TCPServer.h"
#include "Socket.h"



int main(int argc,char * argv[]) {

    if(argc != 3){
        perror("error parametre");
        return -1;
    }

    int port = std::stoi(argv[1]);
    std::string directory = argv[2];

    pr::TCPServer server;

    if (server.startServer0(port,directory)) {
        std::cout << "Server started on port " << port << " with storage directory " << directory << std::endl;
    } else {
        std::cerr << "Failed to start server on port " << port << std::endl;
        return 1;
    }


    return 0;
}

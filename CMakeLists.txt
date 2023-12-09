cmake_minimum_required(VERSION 3.26)
project(PSCR_TME)

set(CMAKE_CXX_STANDARD 14)

include_directories(nov2019/exam/exo1/src)
include_directories(nov2019/exam/exo2/src)
include_directories(nov2019/exam/exo3/src)
include_directories(TME1/exo1/src)
include_directories(TME4/src)
include_directories(TME5/src)
include_directories(TME6/src)
include_directories(TME7/src)
include_directories(TME8/src)
include_directories(TME9/src)

add_executable(TME1
        TME1/exo1/src/List.cpp
        TME1/exo1/src/List.h
        TME1/exo1/src/main.cpp
        )

add_executable(TME2 TME2/main.cpp
        TME2/HashMap.h
)
add_executable(TME3 TME3/main.cpp
        TME3/HashMap.h
        TME3/tme3.h
        TME3/inverse.h
)

add_executable(TME6 TME6/src/fork_exo.cpp
        TME6/src/rsleep.cpp
        TME6/src/rsleep.h
)

add_executable(TME4 TME4/src/main.cpp
        TME4/src/Banque.cpp
        TME4/src/Banque.h
        TME4/src/Compte.cpp
        TME4/src/Compte.h
)

add_executable(TME5 TME5/src/main.cpp
        TME5/src/Color.cpp
        TME5/src/Color.h
        TME5/src/Job.h
        TME5/src/Pool.h
        TME5/src/Queue.h
        TME5/src/Rayon.h
        TME5/src/Scene.h
        TME5/src/Sphere.h
        TME5/src/Vec3D.cpp
        TME5/src/Vec3D.h)

add_executable(TME8
        TME8/src/client.cpp
        TME8/src/ConnectionHandler.h
        TME8/src/Ftp_client.cpp
        TME8/src/Ftp_server.cpp
        TME8/src/Job.h
        TME8/src/Pool.h
        TME8/src/Queue.h
        TME8/src/server.cpp
        TME8/src/server2.cpp
        TME8/src/ServerSocket.cpp
        TME8/src/ServerSocket.h
        TME8/src/Socket.cpp
        TME8/src/Socket.h
        TME8/src/TCPServer.cpp
        TME8/src/TCPServer.h
)
add_executable(Ftp_client
        TME8/src/Ftp_client.cpp
        TME8/src/ServerSocket.cpp
        TME8/src/ServerSocket.h
        TME8/src/Socket.cpp
        TME8/src/Socket.h
        TME8/src/TCPServer.cpp
        TME8/src/TCPServer.h
)
add_executable(Ftp_server
        TME8/src/Ftp_server.cpp
        TME8/src/ServerSocket.cpp
        TME8/src/ServerSocket.h
        TME8/src/Socket.cpp
        TME8/src/Socket.h
        TME8/src/TCPServer.cpp
        TME8/src/TCPServer.h
)
add_executable(pipe TME7/src/pipe.cpp)
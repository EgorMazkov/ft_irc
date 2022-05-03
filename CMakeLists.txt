cmake_minimum_required(VERSION 3.21)
project(ft_irc)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ft_irc
        Channel.cpp
        Channel.hpp
        Client.cpp
        Client.hpp
        Command.cpp
        main.cpp
        Server.cpp
        Server.hpp)

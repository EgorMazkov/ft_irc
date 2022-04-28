cmake_minimum_required(VERSION 3.19)
project(ft_irc)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ft_irc
        Client.cpp
        Client.hpp
        Command.cpp
        Command.hpp
        main.cpp
        Server.cpp
        Server.hpp)

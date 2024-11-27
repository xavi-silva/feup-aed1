cmake_minimum_required(VERSION 3.26)
project(AED_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_Project main.cpp
        Class.cpp
        Class.h
        Student.cpp
        Student.h
        UC.h
        UC.cpp
        LEIC.h
        LEIC.cpp
      )
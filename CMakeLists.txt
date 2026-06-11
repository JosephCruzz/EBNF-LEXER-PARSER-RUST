cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyCppProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable file from your source
add_executable(MyProject main.cpp
    Lexer.cpp)

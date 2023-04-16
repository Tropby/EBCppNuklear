cmake_minimum_required(VERSION 3.10)

project(EBCppExamples VERSION 0.1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Configure and Include EBCpp
set(EBCPP_USE_SSL Off)           # On/Off - Using openssl for ssl sockets and https
set(EBCPP_USE_SSL_STATIC Off)    # On/Off - Activate static linking of openssl into your application (see openssl license)
set(EBCPP_USE_SQLITE Off)        # On/Off - Using sqlite in your application (static linked)
set(EBCPP_STATIC On)             # On/Off - Static linking of libc, libc++ and winpthread

set(EBCPP_NUKLEAR_RENDERER GDI)

include(ebcpp_nuklear.cmake)

add_subdirectory(examples/basics)
include_directories(examples/basics)

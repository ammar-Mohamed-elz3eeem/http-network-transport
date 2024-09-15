# CMakeLists.txt for HTTPNetworkTransportTests
#
# © 2018 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This HTTPNetworkTransportTests)

set(Sources
    src/HTTPServerNetworkTransportTests.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

find_package(gtest REQUIRED)

target_include_directories(${This} PRIVATE ..)

target_link_libraries(${This} PUBLIC
    gtest_main
    gtest
    HTTPNetworkTransport
    HTTP
    SystemAbstractions
    StringExtensions
)

add_test(
    NAME ${This}
    COMMAND ${This}
)

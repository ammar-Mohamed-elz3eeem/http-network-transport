
# CMakeLists.txt for HTTPNetworkTransport
#
# © 2018 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This HTTPNetworkTransport)

set(Headers
    include/HTTPNetworkTransport/HTTPServerNetworkTransport.hpp
)

set(Sources
    src/HTTPServerNetworkTransport.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)

target_link_libraries(${This} PUBLIC
    HTTP
    SystemAbstractions
    StringExtensions
)

add_subdirectory(test)

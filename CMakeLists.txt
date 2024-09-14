
# CMakeLists.txt for HTTPNetworkTransport
#
# © 2018 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This HTTPNetworkTransport)

set(Headers
    include/HTTPNetworkTransport/HTTPNetworkTransport.hpp
)

set(Sources
    src/HTTPNetworkTransport.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)

target_link_libraries(${This} PUBLIC)

add_subdirectory(test)

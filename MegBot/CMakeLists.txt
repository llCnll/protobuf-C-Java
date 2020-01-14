cmake_minimum_required(VERSION 3.5)

PROJECT(MegBot)

SET(CMAKE_CXX_COMPILER /usr/local/bin/g++ CACHE PATH "" FORCE)
SET(CMAKE_CXX_FLAGS_DEBUG "-w -Wno-unused-variable -Wno-unused-but-set-variable -DPOSIX -g -O0 -fpermissive -fPIC -std=c++1z")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
##############A
find_package(CURL REQUIRED)
find_package(Protobuf REQUIRED)
FILE(GLOB protofiles "proto/*.proto")

PROTOBUF_GENERATE_CPP(CLIENT_SRC CLIENT_H ${protofiles})
set(CURL_LIBRARY "-lcurl")
add_executable(http_demo
        http_demo.cpp
        ${CLIENT_SRC}
        )
include_directories(${CURL_INCLUDE_DIR})
target_include_directories(http_demo PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(http_demo
        ${CURL_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        )


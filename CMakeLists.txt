cmake_minimum_required(VERSION 3.10)

project(http-server)

set(SOURCES
    src/main.c
    src/server/server.c
    src/http/request.c
    src/http/header.c
    sc/http/response.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
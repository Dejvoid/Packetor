cmake_minimum_required(VERSION 3.5)
project(Packetor VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/lib/header)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB SOURCES
${PROJECT_SOURCE_DIR}/include/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(Packetor src/main.cpp ${SOURCES})

set(CMAKE_CXX_FLAGS "-O2 -g -Wall")

target_link_libraries(${PROJECT_NAME} Pcap++ Packet++ Common++ pcap pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

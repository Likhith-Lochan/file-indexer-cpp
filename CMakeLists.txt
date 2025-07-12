cmake_minimum_required(VERSION 3.10)

project(FileSystemIndexer)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS filesystem system)

include_directories(${Boost_INCLUDE_DIRS} include)
file(GLOB SOURCES "src/*.cpp")

add_executable(indexer ${SOURCES})
target_link_libraries(indexer ${Boost_LIBRARIES})
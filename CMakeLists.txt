cmake_minimum_required(VERSION 3.10)

project(sync_io)
set(TOP_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(CheckCXXCompilerFlag)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include_directories(${TOP_ROOT_PATH}/include)

if( DEFINED ENV{BOOST_HOME})
    include_directories($ENV{BOOST_HOME}/include)
    link_directories($ENV{BOOST_HOME}/lib)
endif()

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    message("support CXX11")
    add_definitions(-std=c++11)
endif()

file(GLOB_RECURSE SRC_SOURCES src/*.cpp)

message("SRCS:${SRC_SOURCES}")


aux_source_directory(${TOP_ROOT_PATH}/src COMMON_CPP_FILES)
#add_executable(${PROJECT_NAME} ${SRC_SOURCES} main.cpp)

add_subdirectory(${TOP_ROOT_PATH}/server)
add_subdirectory(${TOP_ROOT_PATH}/client)

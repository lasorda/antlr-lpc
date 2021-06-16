# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)
project(lpc_parser)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DANTLR4CPP_STATIC)

set(ANTLR4_WITH_STATIC_CRT OFF)
include(ExternalAntlr4Cpp)
include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(mcpp)

set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/antlr-4.9.2-complete.jar)
find_package(ANTLR REQUIRED)
add_subdirectory(mcpp)

antlr_target(LPCParser LPC.g4 PACKAGE antlrcpptest LISTENER VISITOR)

include_directories(${ANTLR_LPCParser_OUTPUT_DIR})

add_executable(${PROJECT_NAME} main.cpp ${ANTLR_LPCParser_CXX_OUTPUTS})
target_link_libraries(${PROJECT_NAME} antlr4_static)
target_link_libraries(${PROJECT_NAME} mcpp)

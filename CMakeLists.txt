# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DANTLR4CPP_STATIC)

set(ANTLR4_WITH_STATIC_CRT OFF)
include(ExternalAntlr4Cpp)
include_directories(${ANTLR4_INCLUDE_DIRS})

set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/antlr-4.9.2-complete.jar)
find_package(ANTLR REQUIRED)

antlr_target(LPCParser LPC.g4 PACKAGE antlrcpptest LISTENER VISITOR)

include_directories(${ANTLR_LPCParser_OUTPUT_DIR})

add_executable(lpc_parser main.cpp ${ANTLR_LPCParser_CXX_OUTPUTS})
target_link_libraries(lpc_parser antlr4_static)

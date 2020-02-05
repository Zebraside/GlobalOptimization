project(GlobalOptimization)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # TODO: check this option

option(ENABLE_GUI "Enable Qt based UI" OFF)
message(STATUS "ENABLE_GUI option is ${ENABLE_GUI}")

add_subdirectory(Src)

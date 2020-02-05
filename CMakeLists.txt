project(GlobalOptimization)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # TODO: check this option

option(ENABLE_GUI "Enable Qt based UI" OFF)
message(STATUS "ENABLE_GUI option is ${ENABLE_GUI}")

message(STATUS ${CMAKE_PREFIX_PATH})

if (EXISTS "../Thirdparty/Qt" AND EXISTS ${CMAKE_PREFIX_PATH})
    message(STATUS "All thirdpary exists")
else()
    message(STATUS "Not all thirdpary exists")
endif()

add_subdirectory(Src)

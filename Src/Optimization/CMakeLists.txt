add_library(Optimization STATIC SolverFactory.cpp Function.cpp)
target_include_directories(Optimization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
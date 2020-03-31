add_library(Optimization STATIC
        SolverFactory.cpp
        PiyavskogoMethod.cpp
        StronginSolver.cpp
        UniformSearchMethod.cpp
        SolverMethod.cpp
        Test.cpp FunctionFactory.h FunctionFactory.cpp)

target_include_directories(Optimization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
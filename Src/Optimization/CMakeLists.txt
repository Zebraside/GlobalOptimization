add_library(Optimization STATIC
        SolverFactory.cpp
        Function.cpp
        PiyavskogoMethod.cpp
        StronginSolver.cpp
        UniformSearchMethod.cpp
        SolverMethod.cpp
        Test.cpp)

target_include_directories(Optimization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
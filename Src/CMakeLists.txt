add_executable(Main main.cpp main.cpp)

add_subdirectory(Optimization)

target_link_libraries(Main
        PUBLIC
            Optimization)

if (ENABLE_GUI)
    target_compile_definitions(Main PUBLIC ENABLE_GUI)

    add_subdirectory(Presenters)

    target_link_libraries(Main
        PUBLIC
            Presenters)
endif()
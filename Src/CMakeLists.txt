add_subdirectory(Optimization)

add_executable(Main main.cpp)
target_link_libraries(Main PUBLIC Optimization)
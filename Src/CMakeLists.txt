add_subdirectory(Optimization)
add_subdirectory(Presenters)

add_executable(Main main.cpp main.cpp)
target_link_libraries(Main
        PUBLIC
            Optimization
            Presenters
            Qt5::Widgets
            Qt5::Core
            Qt5::Gui
            Qt5::DataVisualization
            stdc++fs)

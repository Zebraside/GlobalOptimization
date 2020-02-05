add_library(Presenters STATIC surfacegraph.cpp main_window.cpp)

target_include_directories(Presenters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Presenters
        PUBLIC
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::DataVisualization
        Qt5::Quick
        stdc++fs)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#TODO: add Qt libs as thirdparty archive
find_package(Qt5 COMPONENTS Widgets Core DataVisualization Quick Charts REQUIRED)

add_library(Presenters
                STATIC
                    main_window.cpp
                    application.cpp chart.cpp chart.h)

target_include_directories(Presenters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Presenters
        PUBLIC
            Qt5::Widgets
            Qt5::Core
            Qt5::Gui
            Qt5::DataVisualization
            Qt5::Quick
            Qt5::Charts
            stdc++fs
            Optimization)
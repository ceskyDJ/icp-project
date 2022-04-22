cmake_minimum_required(VERSION 3.22)
project(icp_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/Qt/5.15.2/gcc_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(icp_project main.cpp)
target_link_libraries(icp_project
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )


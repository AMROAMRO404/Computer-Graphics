cmake_minimum_required(VERSION 3.16)

project(ComputerGraphics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Works with either Qt 6 or Qt 5, whichever is installed.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Window shared by both programs: hosts a canvas and adds the shortcuts.
add_library(viewer STATIC
   common/ViewerWindow.cpp
   common/ViewerWindow.h
)
target_include_directories(viewer PUBLIC common)
target_link_libraries(viewer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

enable_testing()

add_subdirectory(rasterizer)
add_subdirectory(opengl-shapes)

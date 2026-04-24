cmake_minimum_required(VERSION 3.16)
project(cutefish-qt-plugins)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 核心依赖从 Qt6 切换到 Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets DBus)

add_subdirectory(platformtheme)
add_subdirectory(widgetstyle)

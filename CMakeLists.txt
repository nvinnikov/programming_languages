cmake_minimum_required(VERSION 3.5)

project(nikita LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(gpsd IMPORTED_TARGET REQUIRED libgpsd)
pkg_check_modules(gps IMPORTED_TARGET REQUIRED libgps)

add_executable(nikita
  main.cpp
  widget.cpp
  widget.h
  widget.ui
  gps.cpp
  gps.h
)

target_link_libraries(nikita PRIVATE Qt5::Widgets Qt5::Multimedia PkgConfig::gps PkgConfig::gpsd)


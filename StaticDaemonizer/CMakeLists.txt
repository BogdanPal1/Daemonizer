cmake_minimum_required(VERSION 3.14)

project(StaticDaemonizer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./include)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(StaticDaemonizer STATIC
  ./src/daemonizer.cpp
  ./include/daemonizer.h
)

target_link_libraries(StaticDaemonizer PRIVATE Qt5::Core)

target_compile_definitions(StaticDaemonizer PRIVATE STATIC_DAEMONIZER_LIBRARY)

install (TARGETS StaticDaemonizer DESTINATION /usr/local/lib/Daemonizer)
install (FILES ./include/daemonizer.h DESTINATION /usr/local/include/Daemonizer)

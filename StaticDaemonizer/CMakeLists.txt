cmake_minimum_required(VERSION 3.13)

project(StaticDaemonizer VERSION 1.0.0 DESCRIPTION "Static library for daemonize Qt project" LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_PREFIX_PATH "/usr")

set(SOURCES src)
set(HEADERS include)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(StaticDaemonizer STATIC
  ${SOURCES}/daemonizer.cpp
  ${HEADERS}/daemonizer.h
)

set_target_properties(StaticDaemonizer PROPERTIES PUBLIC_HEADER ${HEADERS}/daemonizer.h)

target_include_directories(StaticDaemonizer PRIVATE ${HEADERS})
target_include_directories(StaticDaemonizer PRIVATE ${SOURCES})

target_link_libraries(StaticDaemonizer PRIVATE Qt5::Core)

target_compile_definitions(StaticDaemonizer PRIVATE STATIC_DAEMONIZER_LIBRARY)

install (TARGETS StaticDaemonizer
  ARCHIVE DESTINATION /usr/local/lib/daemonizer
  PUBLIC_HEADER DESTINATION /usr/local/include/daemonizer
)

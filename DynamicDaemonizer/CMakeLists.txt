cmake_minimum_required(VERSION 3.13)

project(DynamicDaemonizer VERSION 1.0.0 DESCRIPTION "Dynamic library for daemonize Qt project" LANGUAGES CXX)

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

add_library(DynamicDaemonizer SHARED
  ${SOURCES}/daemonizer.cpp
  ${HEADERS}/daemonizer.h
  ${HEADERS}/daemonizer_global.h
)

set_target_properties(DynamicDaemonizer PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(DynamicDaemonizer PROPERTIES PUBLIC_HEADER 
  "${HEADERS}/daemonizer.h;${HEADERS}/daemonizer_global.h")

target_include_directories(DynamicDaemonizer PRIVATE ${HEADERS})
target_include_directories(DynamicDaemonizer PRIVATE ${SOURCES})

target_link_libraries(DynamicDaemonizer PRIVATE Qt5::Core)

install(TARGETS DynamicDaemonizer
  LIBRARY DESTINATION /usr/local/lib/daemonizer
  PUBLIC_HEADER DESTINATION /usr/local/include/daemonizer
)


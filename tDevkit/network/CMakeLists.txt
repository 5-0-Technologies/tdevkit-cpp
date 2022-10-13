cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Network Widgets)

if(Qt5_FOUND)
    add_library(qtDevkit
        qt-network-client/qtNetworkClient.cpp
    )

    target_include_directories(qtDevkit PUBLIC qt-network-client/ base/)
    target_link_libraries(qtDevkit Qt5::Network Qt5::Core Qt5::Widgets)
endif()
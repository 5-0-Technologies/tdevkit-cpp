cmake_minimum_required(VERSION 3.15)

add_library(NetworkClient "")
target_sources(NetworkClient
    PUBLIC
        twinzo/network/network_client.hpp
)
target_include_directories(NetworkClient
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(NetworkClient PROPERTIES LINKER_LANGUAGE CXX)


add_library(MockNetworkClient "")
target_sources(MockNetworkClient
    PUBLIC
        twinzo/network/mock_client.hpp
)
target_include_directories(MockNetworkClient
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(MockNetworkClient PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(MockNetworkClient NetworkClient)


find_package(Qt5 REQUIRED COMPONENTS Core Network Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_library(QtNetworkClient "")
target_sources(QtNetworkClient
    PRIVATE
        twinzo/network/qt_client.cpp
    PUBLIC
        twinzo/network/qt_client.hpp
)
target_include_directories(QtNetworkClient
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(QtNetworkClient PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(QtNetworkClient Qt5::Network Qt5::Core Qt5::Widgets)
target_link_libraries(QtNetworkClient NetworkClient)
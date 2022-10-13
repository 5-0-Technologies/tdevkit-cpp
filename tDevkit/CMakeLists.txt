cmake_minimum_required(VERSION 3.15)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tDevkit/contracts)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/network)

add_library(tDevkit
  tDevkit/tDevkit.cpp
)

target_include_directories(tDevkit PUBLIC tDevkit/)
target_link_libraries(tDevkit contracts)

target_link_libraries(qtDevkit tDevkit)
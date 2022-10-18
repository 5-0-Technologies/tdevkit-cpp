cmake_minimum_required(VERSION 3.15)

add_subdirectory(twinzo/tdevkit/contracts)

add_library(tDevkit "")
target_sources(tDevkit
    PUBLIC
        twinzo/tdevkit/tdevkit.hpp
    PRIVATE
        twinzo/tdevkit/authorization.tpp
)
target_include_directories(tDevkit
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(tDevkit PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(tDevkit NetworkClient contracts)
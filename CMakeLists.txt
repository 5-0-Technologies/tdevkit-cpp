cmake_minimum_required(VERSION 3.15)
project(tDevkit VERSION 0.0.1 LANGUAGES CXX)


include(twinzo/network/CMakeLists.txt)
include(twinzo/tdevkit/CMakeLists.txt)

include(CTest)

option(TDEVKIT_BUILD_TESTING "Generate library with unit test support" ON)
if (TDEVKIT_BUILD_TESTING AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

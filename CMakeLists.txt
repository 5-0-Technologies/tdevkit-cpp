cmake_minimum_required(VERSION 3.15)
project(tDevkit VERSION 0.0.1 LANGUAGES CXX)

include(CTest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tDevkit)

add_executable(testQtGet
  tDevkit/tests/testQtGet.cpp
)

add_executable(testQtPost
  tDevkit/tests/testQtPost.cpp
)

add_executable(testQtPut
  tDevkit/tests/testQtPut.cpp
)

add_executable(testQtDelete
  tDevkit/tests/testQtDelete.cpp
)

add_executable(testQtPatch
  tDevkit/tests/testQtPatch.cpp
)

add_executable(testQtHeaders
  tDevkit/tests/testQtHeaders.cpp  
)

add_executable(testQtGetDelayed
  tDevkit/tests/testQtGetDelayed.cpp  
)

target_link_libraries(testQtGet qtDevkit)
target_link_libraries(testQtPost qtDevkit)
target_link_libraries(testQtPut qtDevkit)
target_link_libraries(testQtPatch qtDevkit)
target_link_libraries(testQtDelete qtDevkit)
target_link_libraries(testQtHeaders qtDevkit)
target_link_libraries(testQtGetDelayed qtDevkit)

add_test(NAME testQtGet COMMAND testQtGet)
add_test(NAME testQtPost COMMAND testQtPost)
add_test(NAME testQtPut COMMAND testQtPut)
add_test(NAME testQtPatch COMMAND testQtPatch)
add_test(NAME testQtDelete COMMAND testQtDelete)
add_test(NAME testQtHeaders COMMAND testQtHeaders)
add_test(NAME testQtGetDelayed COMMAND testQtGetDelayed)
add_test(NAME testQtGetTimeouted COMMAND testQtGetDelayed 1000)
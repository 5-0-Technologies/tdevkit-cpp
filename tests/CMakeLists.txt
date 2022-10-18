cmake_minimum_required(VERSION 3.15)

add_executable(testQtGet
  testQtGet.cpp
)
target_link_libraries(testQtGet QtNetworkClient)
add_test(NAME testQtGet COMMAND testQtGet)

add_executable(testQtPost
  testQtPost.cpp
)
target_link_libraries(testQtPost QtNetworkClient)
add_test(NAME testQtPost COMMAND testQtPost)

add_executable(testQtPut
  testQtPut.cpp
)
target_link_libraries(testQtPut QtNetworkClient)
add_test(NAME testQtPut COMMAND testQtPut)

add_executable(testQtDelete
  testQtDelete.cpp
)
target_link_libraries(testQtDelete QtNetworkClient)
add_test(NAME testQtDelete COMMAND testQtDelete)

add_executable(testQtPatch
  testQtPatch.cpp
)
target_link_libraries(testQtPatch QtNetworkClient)
add_test(NAME testQtPatch COMMAND testQtPatch)

add_executable(testQtHeaders
  testQtHeaders.cpp  
)
target_link_libraries(testQtHeaders QtNetworkClient)
add_test(NAME testQtHeaders COMMAND testQtHeaders)

add_executable(testQtGetDelayed
  testQtGetDelayed.cpp  
)
target_link_libraries(testQtGetDelayed QtNetworkClient)
add_test(NAME testQtGetDelayed COMMAND testQtGetDelayed)
add_test(NAME testQtGetTimeouted COMMAND testQtGetDelayed 1000)
set_tests_properties(testQtGetTimeouted PROPERTIES WILL_FAIL TRUE)

add_executable(testDevkitMock
  testDevkitMock.cpp
)
target_link_libraries(testDevkitMock tDevkit MockNetworkClient)
add_test(NAME testDevkitMock COMMAND testDevkitMock)

add_executable(testDevkit
  testDevkit.cpp
)
target_link_libraries(testDevkit tDevkit QtNetworkClient)
add_test(NAME testDevkit COMMAND testDevkit)

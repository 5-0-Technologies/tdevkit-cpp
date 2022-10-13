cmake_minimum_required(VERSION 3.15)

find_package(Protobuf REQUIRED)

# Get paths to contracts
file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} CONTRACT_PATH)
file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} CONTRACT_OUTPUT_PATH)
# Recursively find all contract protobuf files
file(GLOB_RECURSE CONTRACT_PROTOS "${CONTRACT_PATH}/*.proto")
# Iterate over the protobuf files & compile them using protoc
foreach(proto ${CONTRACT_PROTOS})
  file(TO_NATIVE_PATH ${proto} proto_native)
  execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --proto_path=${CONTRACT_PATH} --cpp_out=${CONTRACT_OUTPUT_PATH} ${proto_native})
endforeach(proto)
# Find all compiled protobuf files
file(GLOB_RECURSE PROTO_H "${CONTRACT_OUTPUT_PATH}/*.h")
file(GLOB_RECURSE PROTO_CC "${CONTRACT_OUTPUT_PATH}/*.cc")

# Create contract library & include headers/link protobuf libraries
add_library(contracts
  ${PROTO_CC}
)
target_include_directories(contracts PUBLIC ${CONTRACT_OUTPUT_PATH})
target_link_libraries(contracts ${PROTOBUF_LIBRARIES})
cmake_minimum_required(VERSION 3.15)

find_package(Protobuf REQUIRED)

# Recursively find all contract protobuf files
file(GLOB_RECURSE CONTRACT_PROTOS "${CMAKE_CURRENT_LIST_DIR}/*.proto")
# Iterate over the protobuf files & compile them using protoc
foreach(proto ${CONTRACT_PROTOS})
    file(TO_NATIVE_PATH ${proto} proto_native)
    execute_process(COMMAND
        ${PROTOBUF_PROTOC_EXECUTABLE}
            --proto_path=${CMAKE_CURRENT_LIST_DIR}
            --cpp_out=${CMAKE_CURRENT_LIST_DIR} ${proto_native}
    )
endforeach(proto)

# Find all compiled protobuf files
file(GLOB_RECURSE PROTO_H "${CMAKE_CURRENT_LIST_DIR}/*.h")
file(GLOB_RECURSE PROTO_CC "${CMAKE_CURRENT_LIST_DIR}/*.cc")

# Create contract library & include headers/link protobuf libraries
add_library(contracts
    ${PROTO_CC}
)
target_link_libraries(contracts ${PROTOBUF_LIBRARIES})
# Generate proto and grpc headers and source files
set(gc_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/grpcchat.pb.cc")
set(gc_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/grpcchat.pb.h")
set(gc_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/grpcchat.grpc.pb.cc")
set(gc_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/grpcchat.grpc.pb.h")
add_custom_command(
        OUTPUT "${gc_proto_srcs}" "${gc_proto_hdrs}" "${gc_grpc_srcs}" "${gc_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${gc_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${gc_proto}"
        DEPENDS "${gc_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Generate executables and link required libraries
foreach(_target client server)
    add_executable(${_target} "${_target}.cpp" ${gc_proto_srcs} ${gc_grpc_srcs})
    target_link_libraries(${_target} ${_GRPC_GRPCPP_UNSECURE} ${_PROTOBUF_LIBPROTOBUF})
endforeach()
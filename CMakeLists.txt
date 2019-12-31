cmake_minimum_required(VERSION 3.5.0)

project(GrpcChat C CXX)

set(CMAKE_CXX_STANDARD 11)

#find protobuf installation, looks for protobuf-config.cmake file
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

#find gRPC installation, looks for gRPCConfig.cmake file
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

#locate and set proto file and path
get_filename_component(gc_proto "proto/grpcchat.proto" ABSOLUTE)
get_filename_component(gc_proto_path "${gc_proto}" PATH)

add_subdirectory(src)
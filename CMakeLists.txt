cmake_minimum_required(VERSION 3.8)
project(MMP DESCRIPTION "Multi Media Plugin")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

set(MMP_System_Device)
include(ultis)

message("-- System Name : ${CMAKE_SYSTEM_NAME}")
message("-- System Device : ${MMP_System_Device}")


add_subdirectory(Sample)
cmake_minimum_required(VERSION 3.8)
project(MMP DESCRIPTION "Multi Media Plugin")

# GPU Window
option(USE_EGL ON)

set(MMP_PRO_TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

set(BUILD_SHARED_LIBS NO)
add_subdirectory(Extension/poco)
add_subdirectory(Common)
add_subdirectory(GPU)

set(MMP_System_Device)
include(ultis)

message("-- System Name : ${CMAKE_SYSTEM_NAME}")
message("-- System Device : ${MMP_System_Device}")


add_subdirectory(Sample)
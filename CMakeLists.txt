cmake_minimum_required(VERSION 3.8)
project(MMP DESCRIPTION "Multi Media Plugin")

# GPU Window
option(USE_EGL ON)
option(USE_OPENGL ON) 
option(USE_MEDIA_SERVER ON)
option(USE_SDL OFF) # 目前用于 x86 上创建调试窗口 (软件)

## media-server
option(USE_MEDIA_SERVER_MPEG ON)

set(MMP_PRO_TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

set(BUILD_SHARED_LIBS NO)
add_subdirectory(Extension/poco)
if (USE_OPENGL)
    add_subdirectory(Extension/glew-2.2.0)
endif()
if (USE_MEDIA_SERVER)
    add_subdirectory(CMake/MediaServer)
endif()
add_subdirectory(Common)
add_subdirectory(GPU)

set(MMP_System_Device)
include(utility)

message("-- System Name : ${CMAKE_SYSTEM_NAME}")
message("-- System Device : ${MMP_System_Device}")


add_subdirectory(Sample)
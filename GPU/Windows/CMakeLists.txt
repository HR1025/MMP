cmake_minimum_required(VERSION 3.8)
project(Windows)

set(Windows_SRCS)
set(Windows_INCS)
set(Windows_LIB_DIR)
set(Windows_LIBS)

list(APPEND Windows_INCS
    ${MMP_PRO_TOP_DIR}
)

if (USE_EGL)
    if (NOT OpenGL_FOUND) # 交叉编译时需外部设置
        find_package(OpenGL COMPONENTS EGL REQUIRED)
    endif()
    list(APPEND Windows_INCS ${OPENGL_INCLUDE_DIR})
    list(APPEND Windows_LIB_DIR ${OPENGL_LIBRARY})
    list(APPEND Windows_LIBS OpenGL::EGL)
endif()
 
if (USE_EGL)
    list(APPEND Windows_INCS
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

if (USE_EGL)
    list(APPEND Windows_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLWindowInterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLWindowDefault.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLCommon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLCommon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLWindowFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EGL/EGLWindowFactory.cpp
    )
endif()

add_library(Windows OBJECT ${Windows_SRCS})
add_library(Mmp::Windows ALIAS Windows)
target_include_directories(Windows PUBLIC ${Windows_INCS})
target_link_libraries(Windows PRIVATE ${Windows_LIBS} Poco::Foundation Mmp::Common) 
if (NOT Windows_LIB_DIR)
    target_link_directories(Windows ${Windows_LIB_DIR})
endif()
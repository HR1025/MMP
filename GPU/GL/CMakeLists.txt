cmake_minimum_required(VERSION 3.8)
project(GL)

set(GL_SRCS)
set(GL_INCS)
set(GL_LIB_DIR)
set(GL_LIBS)

list(APPEND GL_INCS
    ${MMP_PRO_TOP_DIR}
)

if (USE_OPENGL)
    # see also : https://cmake.org/cmake/help/latest/module/FindOpenGL.html
    if (NOT OPENGL_FOUND) # 交叉编译时需外部设置
        if (CMAKE_HOST_UNIX)
            set(OpenGL_GL_PREFERENCE GLVND)
        endif()
        find_package(OpenGL REQUIRED)
    endif()
    list(APPEND GL_INCS ${OPENGL_INCLUDE_DIR})
    list(APPEND GL_LIB_DIR ${OpenGL_LIBRARY_DIRS})
    list(APPEND GL_LIBS OpenGL::OpenGL)
    message("-- Found OPENGL")
    message("  -- OpenGL INCS : ${OPENGL_INCLUDE_DIR}")
    message("  -- OpenGL LIB DIR : ${OpenGL_LIBRARY_DIRS}")
    message("  -- OpenGL LIBS : ${OPENGL_LIBRARIES}")
endif()
 
if (USE_OPENGL)
    list(APPEND GL_INCS
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

if (USE_OPENGL)
    list(APPEND GL_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/OpenGL.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/OpenGL.cpp
    )
endif()

add_library(GL OBJECT ${GL_SRCS})
add_library(Mmp::GL ALIAS GL)
target_include_directories(GL PUBLIC ${GL_INCS})
target_link_libraries(GL PRIVATE ${GL_LIBS} Poco::Foundation Mmp::Common) 
list(LENGTH GL_LIB_DIR GL_LIB_DIR_LEN)
if (NOT(${GL_LIB_DIR_LEN} EQUAL 0))
    target_link_directories(GL ${GL_LIB_DIR})
endif()
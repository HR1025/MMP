cmake_minimum_required(VERSION 3.8)

project(Sample)

set(Smaple_SRCS)
set(Smaple_INCS)
set(Sample_LIBS)

list(APPEND Smaple_INCS
    ${MMP_PRO_TOP_DIR}
)
list(APPEND Smaple_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/TestSuit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/WindowsEGLTest.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/WindowsEGLTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/LogTest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/LogTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/DisplaySDLTest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/DisplaySDLTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/AnyTest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuit/AnyTest.cpp
)

add_subdirectory(Common)
add_subdirectory(Extension)

add_executable(Sample ${Smaple_SRCS})
target_include_directories(Sample PUBLIC ${Smaple_INCS})
target_link_libraries(Sample PRIVATE Poco::Foundation Mmp::Common Mmp::Windows Sample::Common Sample::Extension) 

if (USE_EGL)
    target_compile_definitions(Sample PRIVATE USE_EGL)
endif()
if (USE_OPENGL)
    target_compile_definitions(Sample PRIVATE USE_OPENGL)
endif()
if (USE_SDL)
    target_compile_definitions(Sample PRIVATE USE_SDL)
endif()

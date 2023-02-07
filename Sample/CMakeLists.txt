cmake_minimum_required(VERSION 3.8)

project(Sample)

set(Smaple_SRCS)
set(Smaple_INCS)

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
)

add_subdirectory(Common)

add_executable(Sample ${Smaple_SRCS})
target_include_directories(Sample PUBLIC ${Smaple_INCS})
target_link_libraries(Sample PRIVATE Poco::Foundation Mmp::Common Mmp::Windows Sample::Common) 
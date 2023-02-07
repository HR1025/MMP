cmake_minimum_required(VERSION 3.8)

project(Sample_Common)

set(Common_SRCS)
set(Common_INCS)

list(APPEND Common_INCS
    ${MMP_PRO_TOP_DIR}
)
list(APPEND Common_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp
)

add_library(Sample_Common OBJECT ${Common_SRCS})
add_library(Sample::Common ALIAS Sample_Common)
target_include_directories(Sample_Common PUBLIC ${Common_INCS})
target_link_libraries(Sample_Common PRIVATE Poco::Foundation Mmp::Common) 
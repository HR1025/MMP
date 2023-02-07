cmake_minimum_required(VERSION 3.8)

project(Common)

set(Common_SRCS)
set(Common_INCS)

list(APPEND Common_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}
)
list(APPEND Common_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/LoggerInterface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LoggerInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LogMessage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LogMessage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Instantiator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DynamicFactory.h
)

add_library(Common OBJECT ${Common_SRCS})
add_library(Mmp::Common ALIAS Common)
target_include_directories(Common PUBLIC ${Common_INCS})
target_link_libraries(Common PRIVATE Poco::Foundation) 
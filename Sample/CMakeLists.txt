cmake_minimum_required(VERSION 3.8)

project(Sample)

set(Smaple_SRCS)
set(Smaple_INCS)

list(APPEND Smaple_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${Smaple_SRCS})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Smaple_INCS})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Poco::Foundation) 
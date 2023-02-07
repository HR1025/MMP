cmake_minimum_required(VERSION 3.8)

project(Display)

if (USE_SDL)
add_subdirectory(SDL)
endif()
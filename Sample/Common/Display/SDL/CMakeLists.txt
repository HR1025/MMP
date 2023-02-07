cmake_minimum_required(VERSION 3.8)

project(Sample_SDL)

set(SDL_SRCS)
set(SDL_INCS)
set(SDL_LIB_DIR)
set(SDL_LIBS)

if (NOT SDL2_FOUND)
    pkg_check_modules(SDL2 REQUIRED sdl2)
endif()

message("-- Found SDL2")
message("  -- SDL INCS : ${SDL2_INCLUDE_DIRS}")
message("  -- SDL LIB DIR : ${SDL2_LIBRARY_DIRS}")
message("  -- SDL LIBS : ${SDL2_LIBRARIES}")
list(APPEND SDL_INCS ${SDL2_INCLUDE_DIRS})
list(APPEND SDL_LIB_DIR ${SDL2_LIBRARY_DIRS})
list(APPEND SDL_LIBS ${SDL2_LIBRARIES})

list(APPEND SDL_INCS
    ${MMP_PRO_TOP_DIR}
)
list(APPEND SDL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/DisplaySDL.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DisplaySDL.cpp
)

add_library(Sample_SDL OBJECT ${SDL_SRCS})
add_library(Sample::SDL ALIAS Sample_SDL)
target_include_directories(Sample_SDL PUBLIC ${SDL_INCS})
target_link_libraries(Sample_SDL PRIVATE Poco::Foundation Mmp::Common ${SDL_LIBS}) 
list(LENGTH SDL_LIB_DIR SDL_LIB_DIR_LEN)
if (NOT(${SDL_LIB_DIR_LEN} EQUAL 0))
    target_link_directories(Sample_SDL ${SDL_LIB_DIR})
endif()
cmake_minimum_required(VERSION 3.8)

project(Sample_Extension)

set(Extension_SRCS)
set(Extension_INCS)
set(Extension_LIBS)

list(APPEND Extension_LIBS Poco::Foundation Mmp::Common)
if (USE_MEDIA_SERVER)
    list(APPEND Extension_LIBS media_server)
endif()

list(APPEND Extension_INCS
    ${MMP_PRO_TOP_DIR}
)

if (USE_MEDIA_SERVER_MPEG)
list(APPEND Extension_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/media-server/ExMpegTest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/media-server/ExMpegTest.cpp
)
endif()

add_library(Sample_Extension STATIC ${Extension_SRCS})
add_library(Sample::Extension ALIAS Sample_Extension)
target_include_directories(Sample_Extension PUBLIC ${Extension_INCS})
target_link_libraries(Sample_Extension PRIVATE ${Extension_LIBS})
if (USE_MEDIA_SERVER_MPEG)
    target_compile_definitions(Sample_Extension PRIVATE USE_MEDIA_SERVER_MPEG)
endif()

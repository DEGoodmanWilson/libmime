#
#  mime
#  A library for transforming filenames into mime types
#
#  Copyright © 2018 D.E. Goodman-Wilson
#

cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME mime)
project(${PROJECT_NAME})

##### Use C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

##### External dependencies

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

#####

message(STATUS "${PROJECT_NAME} version: " ${CONAN_PACKAGE_VERSION})

# TODO This feels like a hack!
# add_definitions(-DMIMEDB_FILE=\"${CONAN_RES_DIRS_MIME-DB}/db.json\")

##### mime

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_MIME_SOURCE_FILES
        mime/mime.cpp
        mime/mime.h
        )

add_library(${PROJECT_NAME} ${LIB_MIME_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

##### tests
enable_testing()

add_subdirectory(tests)

add_test(ALL_TESTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_tests)
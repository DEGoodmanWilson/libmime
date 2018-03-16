#
#   .__  ._____.
#   |  | |__\_ |__
#   |  | |  || __ \
#   |  |_|  || \_\ \     .__
#   |____/__||___  /____ |__| _____   ____
#                \/     \|  |/     \_/ __ \
#                |  Y Y  \  |  Y Y  \  ___/
#                |__|_|  /__|__|_|  /\___  >
#                      \/         \/     \/
#
#   libmime
#   A C++ library for inferring MIME content-types from pathnames
#
#   Copyright © 2018 D.E. Goodman-Wilson
#

cmake_minimum_required(VERSION 3.2)

project(mime)

##### Use C++11. This is necessary to inform GCC 4.9 and other versions about language features we'll be using
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

##### External dependencies

include(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

#####

message(STATUS "${PROJECT_NAME} version: " ${CONAN_PACKAGE_VERSION})

##### mime

set(LIB_MIME_SOURCE_FILES
        mime/mime_impl.cpp
        mime/mime_impl.h
        mime/mime.h
        )

add_library(${PROJECT_NAME} ${LIB_MIME_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

##### tests
enable_testing()

include_directories(SYSTEM PRIVATE .)
add_subdirectory(tests)

add_test(ALL_TESTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_tests)
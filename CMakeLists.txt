project(Prelude-Engine)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build(Debug or Release)" FORCE)
endif()

set(BUILD_STATIC FALSE CACHE BOOL "true to build static libraries, false to build dynamic libraries (preferred)")
set(BUILD_SAMPLES FALSE CACHE BOOL "true to build the samples.")

if(BUILD_STATIC)
    add_definitions(-DPRELUDE_STATIC)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

if(BUILD_STATIC)
    set(BUILD_MODE STATIC)
else()
    set(BUILD_MODE SHARED)
endif()

include_directories(SYSTEM)

add_subdirectory(engine)

if (BUILD_SAMPLES)
add_subdirectory(sample)
endif()


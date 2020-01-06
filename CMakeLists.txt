cmake_minimum_required(VERSION 2.8.10)

set(ENABLE_EXPORTS)

project(Server1)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

file(GLOB_RECURSE source_files src/* )

add_subdirectory(PhysicModel)
add_subdirectory(WorldVisual)
add_subdirectory(NetworkHandling)

add_executable(

        Server1

        ${source_files}

)
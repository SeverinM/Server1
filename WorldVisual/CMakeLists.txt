cmake_minimum_required(VERSION 2.8.10)

project(WorldVisual)

file(GLOB_RECURSE source_files src/* )

include_directories(include)
include_directories(../src)
include_directories(../PhysicModel/src)
include_directories(../PhysicModel/include)

link_directories(lib)

set(EXECUTABLE_OUTPUT_PATH "bin")

add_library(
        WorldVisual
	STATIC
        ${source_files}
)

target_link_libraries(
	WorldVisual
	glfw3dll
	PhysicModel
	reactphysics3d.lib
)
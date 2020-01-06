cmake_minimum_required(VERSION 2.8.10)
project(NetworkHandling)

file(GLOB_RECURSE source_files src/* )

include_directories(include)
include_directories(../PhysicModel/src)
include_directories(../WorldVisual/src)

link_directories(lib)

set(EXECUTABLE_OUTPUT_PATH "bin")

add_executable(

        NetworkHandling

        ${source_files}

)

target_link_libraries(
	NetworkHandling
	WorldVisual
	reactphysics3d
	PhysicModel
	sfml-network-d
	sfml-system-d
	glfw3dll
)
cmake_minimum_required(VERSION 2.8.10)

project(PhysicModel)

file(GLOB_RECURSE source_files src/* )

include_directories(include)
link_directories(lib)

set(EXECUTABLE_OUTPUT_PATH "bin")

add_library(
        PhysicModel
	STATIC
        ${source_files}

)

target_link_libraries(
	PhysicModel
	reactphysics3D
)
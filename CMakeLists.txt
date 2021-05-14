cmake_minimum_required(VERSION 3.8)

project(
	3DReconstructionProject
	VERSION 0.1
	DESCRIPTION " 3D reconstruction project with Cmake and based on AliceVision"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


find_package(AliceVision CONFIG REQUIRED)
message(STATUS "Found AliceVision : ${AliceVision_FOUND}")
message(STATUS "Found AliceVision version: ${AliceVision_VERSION}")
find_package(IlmBase REQUIRED)
message(STATUS "Found IlmBase : ${IlmBase_FOUND}")
message(STATUS "Found IlmBase version: ${IlmBase_VERSION}")


add_subdirectory(src)

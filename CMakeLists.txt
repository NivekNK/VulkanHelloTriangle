cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/Windows)
endif()

project("VulkanHelloTriangle")

add_subdirectory("VulkanHelloTriangle")

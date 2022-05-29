set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(Vulkan REQUIRED)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)

add_executable(VulkanHelloTriangle   "src/HelloTriangleApplication.h" "src/HelloTriangleApplication.cpp" "src/EntryPoint.cpp")

target_link_libraries(VulkanHelloTriangle
PUBLIC
	${Vulkan_LIBRARIES}
	glfw
	glm::glm
)

target_include_directories(VulkanHelloTriangle
PUBLIC
	src
PRIVATE
	${Vulkan_INCLUDE_DIRS}
	vendor/GLFW/include
	vendor/glm
)

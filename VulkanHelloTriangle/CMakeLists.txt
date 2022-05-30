set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_compile_definitions(
    $<$<CONFIG:Debug>:NK_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:NK_RELEASE>
    $<$<CONFIG:Release>:NK_DIST>
)

find_package(Vulkan REQUIRED)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/vk-bootstrap)

add_executable(VulkanHelloTriangle   "src/HelloTriangleApplication.h" "src/HelloTriangleApplication.cpp" "src/EntryPoint.cpp" "src/Window.h" "src/Window.cpp")

target_link_libraries(VulkanHelloTriangle
PUBLIC
	${Vulkan_LIBRARIES}
	glfw
	glm::glm
	vk-bootstrap::vk-bootstrap
)

target_include_directories(VulkanHelloTriangle
PUBLIC
	src
PRIVATE
	${Vulkan_INCLUDE_DIRS}
	vendor/GLFW/include
	vendor/glm
	vendor/vk-bootstrap/src
)

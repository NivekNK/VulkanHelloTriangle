#include "HelloTriangleApplication.h"

#define GLFW_INCLUDE_NONE
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace nk
{
	void HelloTriangleApplication::Run()
	{
		InitWindow();
		InitVulkan();
		MainLoop();
		Cleanup();
	}

	void HelloTriangleApplication::InitWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, "VulkanTriangleApplication", nullptr, nullptr);
	}

	void HelloTriangleApplication::InitVulkan()
	{
	}

	void HelloTriangleApplication::MainLoop()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
		}
	}

	void HelloTriangleApplication::Cleanup()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}

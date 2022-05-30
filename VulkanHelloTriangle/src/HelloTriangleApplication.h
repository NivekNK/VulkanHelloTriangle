#pragma once

#include <memory>

#include "Window.h"
#include <vulkan/vulkan.hpp>

namespace nk
{
	class HelloTriangleApplication
	{
	public:
		void Run();

	private:
		void InitVulkan();
		void Update();
		void Cleanup();

		void CreateInstance();

		vk::UniqueInstance m_Instance;
		std::unique_ptr<Window> m_Window;
	};
}

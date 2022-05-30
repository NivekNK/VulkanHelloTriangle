#pragma once

#include <memory>
#include <optional>

#include "Window.h"

#include <VkBootstrap.h>
#include <vulkan/vulkan.hpp>

namespace nk
{
	class HelloTriangleApplication
	{
	public:
		void Run();

	private:
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> GraphicsFamily;
		};

		void InitVulkan();
		void Update();
		void Cleanup();

		void CreateInstance();
		void SelectPhysicalDevice();

		vkb::Instance m_Instance;
		vkb::PhysicalDevice m_PhysicalDevice;
		std::unique_ptr<Window> m_Window;
	};
}

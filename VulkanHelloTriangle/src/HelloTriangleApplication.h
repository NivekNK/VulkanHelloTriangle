#pragma once

#include <memory>
#include <vector>
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
		void CreateSurface();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSwapChain();

		vkb::Instance m_Instance;
		vk::SurfaceKHR m_Surface;

		vkb::PhysicalDevice m_PhysicalDevice;
		vkb::Device m_Device;

		vkb::Swapchain m_Swapchain;
		std::vector<VkImage> m_SwapchainImages;
		std::vector<VkImageView> m_SwapchainImageViews;

		vk::Queue m_GraphicsQueue;
		vk::Queue m_PresentQueue;

		std::unique_ptr<Window> m_Window;
	};
}

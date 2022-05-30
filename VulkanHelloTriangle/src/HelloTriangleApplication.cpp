#include "HelloTriangleApplication.h"

#include <iostream>

namespace nk
{
	void HelloTriangleApplication::Run()
	{
		m_Window = std::make_unique<Window>();

		InitVulkan();
		Update();
		Cleanup();
	}
	
	void HelloTriangleApplication::InitVulkan()
	{
		CreateInstance();
		CreateSurface();
		SelectPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain();
	}

	void HelloTriangleApplication::Update()
	{
		while (!m_Window->ShouldClose())
		{
			m_Window->Update();
		}
	}

	void HelloTriangleApplication::Cleanup()
	{
		vkb::destroy_swapchain(m_Swapchain);
		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkb::destroy_device(m_Device);
		vkb::destroy_instance(m_Instance);
	}

	void HelloTriangleApplication::CreateInstance()
	{
		vkb::InstanceBuilder instanceBuilder;
		auto instanceBuilderRet = instanceBuilder
			.set_app_name("Hello Triangle")
			.set_engine_name("No Engine")
			.require_api_version(VK_API_VERSION_1_0)
#if NK_DEBUG
			.request_validation_layers()
			.set_debug_callback(
			  [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
					 VkDebugUtilsMessageTypeFlagsEXT messageType,
					 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
					 void* pUserData) -> VkBool32 
				{
					auto severity = vkb::to_string_message_severity(messageSeverity);
					auto type = vkb::to_string_message_type(messageType);
					printf("[%s: %s] %s\n", severity, type, pCallbackData->pMessage);
					return VK_FALSE;
				}
			)
#endif
			.build();
		if (!instanceBuilderRet)
		{
			std::cerr << "Failed to create Vulkan instance. Error: " << instanceBuilderRet.error().message() << std::endl;
			return;
		}

		m_Instance = instanceBuilderRet.value();

		auto systemInfoRet = vkb::SystemInfo::get_system_info();
		if (!systemInfoRet)
		{
			std::cerr << "Failed to get system info. Error: " << systemInfoRet.error().message() << std::endl;
			return;
		}

		std::cout << "Available extensions:" << std::endl;
		for (const auto& extension : systemInfoRet.value().available_extensions)
		{
			std::cout << "\t" << extension.extensionName << std::endl;
		}
	}

	void HelloTriangleApplication::CreateSurface()
	{
		m_Surface = m_Window->GetSurface(m_Instance.instance);
	}

	void HelloTriangleApplication::SelectPhysicalDevice()
	{
		vkb::PhysicalDeviceSelector selector(m_Instance);
		auto selectorRet = selector
			.set_surface(m_Surface)
			.add_required_extension(VK_KHR_SWAPCHAIN_EXTENSION_NAME)
			.select();

		if (!selectorRet)
		{
			std::cerr << "Failed to select physical device. Error: " << selectorRet.error().message() << std::endl;
			return;
		}

		m_PhysicalDevice = selectorRet.value();
	}

	void HelloTriangleApplication::CreateLogicalDevice()
	{
		vkb::DeviceBuilder deviceBuilder(m_PhysicalDevice);
		auto deviceBuilderRet = deviceBuilder.build();
		if (!deviceBuilderRet)
		{
			std::cerr << "Failed to create logical device. Error: " << deviceBuilderRet.error().message() << std::endl;
			return;
		}

		m_Device = deviceBuilderRet.value();

		auto graphicsQueue = m_Device.get_queue(vkb::QueueType::graphics);
		if (!graphicsQueue)
		{
			std::cerr << "Failed to get graphics queue. Error: " << graphicsQueue.error().message() << std::endl;
		}
		else
		{
			m_GraphicsQueue = graphicsQueue.value();
		}

		auto presentQueue = m_Device.get_queue(vkb::QueueType::present);
		if (!presentQueue)
		{
			std::cerr << "Failed to get present queue. Error: " << presentQueue.error().message() << std::endl;
		}
		else
		{
			m_PresentQueue = presentQueue.value();
		}
	}

	void HelloTriangleApplication::CreateSwapChain()
	{
		vkb::SwapchainBuilder swapchainBuilder(m_Device);
		auto swapRet = swapchainBuilder.build();
		if (!swapRet)
		{
			std::cerr << "Failed to create swapchain. Error: " << swapRet.error().message() << std::endl;
			return;
		}

		m_Swapchain = swapRet.value();
	}
}

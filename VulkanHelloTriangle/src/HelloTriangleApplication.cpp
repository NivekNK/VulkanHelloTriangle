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
		SelectPhysicalDevice();
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
		vkb::destroy_instance(m_Instance);
		vkb::destroy_device(m_Device);
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

	void HelloTriangleApplication::SelectPhysicalDevice()
	{
		vkb::PhysicalDeviceSelector selector(m_Instance);
		auto selectorRet = selector
			.defer_surface_initialization()
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

		auto queueRet = m_Device.get_queue(vkb::QueueType::graphics);
		if (!queueRet)
		{
			std::cerr << "Failed to get graphics queue. Error: " << queueRet.error().message() << std::endl;
			return;
		}
		m_GraphicsQueue = queueRet.value();
	}
}

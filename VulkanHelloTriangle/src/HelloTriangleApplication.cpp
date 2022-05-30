#include "HelloTriangleApplication.h"

#include <iostream>
#include <VkBootstrap.h>

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
	}

	void HelloTriangleApplication::CreateInstance()
	{
		vkb::InstanceBuilder instanceBuilder;
		auto instanceBuilderRet = instanceBuilder
			.set_app_name("Hello Triangle")
			.set_engine_name("No Engine")
			.require_api_version(VK_API_VERSION_1_0)
			.build();
		if (!instanceBuilderRet)
		{
			std::cerr << "Failed to create Vulkan instance. Error: " << instanceBuilderRet.error().message() << std::endl;
			return;
		}

		const vkb::Instance vkbInstance = instanceBuilderRet.value();
		m_Instance = vk::UniqueInstance(vkbInstance.instance);

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
}

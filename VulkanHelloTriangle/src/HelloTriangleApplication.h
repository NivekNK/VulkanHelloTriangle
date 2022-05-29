#pragma once

struct GLFWwindow;

namespace nk
{
	class HelloTriangleApplication
	{
	public:
		HelloTriangleApplication(const unsigned int width = 800, const unsigned int height = 600)
			: m_Width(width), m_Height(height) {}

		void Run();

	private:
		void InitWindow();
		void InitVulkan();
		void MainLoop();
		void Cleanup();

		unsigned int m_Width;
		unsigned int m_Height;
		GLFWwindow* m_Window;
	};
}

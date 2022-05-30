#pragma once

struct GLFWwindow;

namespace nk
{
	class Window
	{
	public:
		explicit Window(unsigned int width = 800, unsigned int height = 600);
		~Window();

		void Update();
		bool ShouldClose() const;
	private:
		unsigned int m_Width;
		unsigned int m_Height;
		GLFWwindow* m_Window;
	};
}

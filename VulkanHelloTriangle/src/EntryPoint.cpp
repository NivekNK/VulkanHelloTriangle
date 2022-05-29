#include "HelloTriangleApplication.h"

#include <iostream>

int main()
{
	nk::HelloTriangleApplication app{};

	try
	{
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#include <iostream>

#include "Raytracer.h"

int main(void)
{
	try
	{
		Raytracer raytracer;

		raytracer.Initialize();
		raytracer.Run();
		raytracer.Export();
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	return 0;
}
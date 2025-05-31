#include "Raytracer.h"

int main(void)
{
	Raytracer raytracer;

	raytracer.Initialize();
	raytracer.Run();
	raytracer.Export();

	return 0;
}
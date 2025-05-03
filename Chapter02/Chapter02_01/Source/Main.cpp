#include <iostream>

int main(void)
{
	int imageWidth = 256;
	int imageHeight = 256;

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for (int row = 0; row < imageHeight; ++row)
	{
		for (int col = 0; col < imageWidth; ++col)
		{
			double r = static_cast<double>(col) / static_cast<double>(imageWidth - 1);
			double g = static_cast<double>(row) / static_cast<double>(imageHeight - 1);
			double b = 0.0;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	return 0;
}
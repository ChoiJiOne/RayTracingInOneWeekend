#include <chrono>
#include <iostream>

#include <stb_image_write.h>

#include "ConfigUtils.h"
#include "Raytracer.h"

void Raytracer::Initialize()
{
	std::string configPath = "Config/Config.json"; // [2025.05.31/최지원] 임시로 강제 위치 지정.
	Json::Value root = LoadConfigFile(configPath);

	int32_t width;
	int32_t height;
	GetConfigValue(root, "width", width);
	GetConfigValue(root, "height", height);
	GetConfigValue(root, "outputFileName", _outputFileName);

	_image = std::make_unique<Image>(width, height);
}

void Raytracer::Run()
{
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

	for (int y = 0; y < _image->GetHeight(); ++y)
	{
		for (int x = 0; x < _image->GetWidth(); ++x)
		{
			float r = static_cast<double>(x) / static_cast<double>(_image->GetWidth() - 1);
			float g = static_cast<double>(y) / static_cast<double>(_image->GetHeight() - 1);
			float b = 0.0f;
			float a = 1.0f;

			glm::vec4 pixelColor(r, g, b, a);
			_image->SetPixel(x, y, pixelColor);
		}
	}

	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "RAYTRACER ELAPSED TIME: " << duration.count() << " ms" << std::endl;
}

void Raytracer::Export()
{
	_image->Export(_outputFileName);
}
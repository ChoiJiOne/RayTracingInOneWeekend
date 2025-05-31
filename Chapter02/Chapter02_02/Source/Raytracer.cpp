#include <iostream>

#include <stb_image_write.h>

#include "ConfigUtils.h"
#include "Raytracer.h"

void Raytracer::Initialize()
{
	LoadConfig();
}

void Raytracer::Run()
{
	_imageBuffer = std::vector<uint8_t>(_imageWidth * _imageHeight * _imageChannel);

	for (int y = 0; y < _imageHeight; ++y)
	{
		for (int x = 0; x < _imageWidth; ++x)
		{
			int offset = (y * _imageWidth + x) * _imageChannel;

			float r = static_cast<double>(x) / static_cast<double>(_imageWidth - 1);
			float g = static_cast<double>(y) / static_cast<double>(_imageHeight - 1);
			float b = 0.0f;
			float a = 1.0f;

			_imageBuffer[offset + 0] = static_cast<uint8_t>(r * 255.0f);
			_imageBuffer[offset + 1] = static_cast<uint8_t>(g * 255.0f);
			_imageBuffer[offset + 2] = static_cast<uint8_t>(b * 255.0f);
			_imageBuffer[offset + 3] = static_cast<uint8_t>(a * 255.0f);
		}
	}
}

void Raytracer::Export()
{
	int32_t byteStride = _imageWidth * _imageChannel;
	std::string outputPath = _outputFileName + _outputFileExtension;
	if (!stbi_write_png(outputPath.c_str(), _imageWidth, _imageHeight, _imageChannel, _imageBuffer.data(), byteStride))
	{
		std::ostringstream oss;
		oss << "FAILED_TO_WRITE_IMAGE_FILE(path: " << outputPath << ")";
	}
	else
	{
		std::cout << "SUCCESS CREATE RAYTRACING IMAGE: " << outputPath << std::endl;
	}
}

void Raytracer::LoadConfig()
{
	std::string configPath = "Config/Config.json"; // [2025.05.31/최지원] 임시로 강제 위치 지정.
	Json::Value root = LoadConfigFile(configPath);
	GetConfigValue(root, "width", _imageWidth);
	GetConfigValue(root, "height", _imageHeight);
	GetConfigValue(root, "outputFileName", _outputFileName);

	_imageWidth = std::max(1, _imageWidth);
	_imageHeight = std::max(1, _imageHeight);
	_imageChannel = 4; // [2025.05.31/최지원] 강제로 RGBA로 고정.
	_outputFileExtension = ".png"; // [2025.05.31/최지원] 강제로 PNG로 고정.
}
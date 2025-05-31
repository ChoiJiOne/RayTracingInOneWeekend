#include <iostream>

#include <stb_image_write.h>

#include "ConfigUtils.h"
#include "Image.h"

Image::Image(int32_t width, int32_t height)
	: _width(width)
	, _height(height)
{
	_width = std::max(1, _width);
	_height = std::max(1, _height);
	_channel = 4; // [2025.05.31/최지원] 강제로 RGBA로 고정
	_outputFileExtension = ".png"; // [2025.05.31/최지원] 강제로 PNG로 고정.
	_colorBuffer = std::vector<uint8_t>(_width * _height * _channel);
}

Image::~Image()
{
}

void Image::SetPixel(int32_t x, int32_t y, const glm::vec4& color)
{
	int32_t offset = (y * _width + x) * _channel;

	_colorBuffer[offset + 0] = static_cast<uint8_t>(color.x * 255.0f);
	_colorBuffer[offset + 1] = static_cast<uint8_t>(color.y * 255.0f);
	_colorBuffer[offset + 2] = static_cast<uint8_t>(color.z * 255.0f);
	_colorBuffer[offset + 3] = static_cast<uint8_t>(color.w * 255.0f);
}

void Image::Export(const std::string& outputFileName)
{
	int32_t byteStride = _width * _channel;
	std::string outputPath = outputFileName + _outputFileExtension;
	if (!stbi_write_png(outputPath.c_str(), _width, _height, _channel, _colorBuffer.data(), byteStride))
	{
		std::ostringstream oss;
		oss << "FAILED_TO_WRITE_IMAGE_FILE(path: " << outputPath << ")";
	}
	else
	{
		std::cout << "SUCCESS CREATE RAYTRACING IMAGE: " << outputPath << std::endl;
	}
}
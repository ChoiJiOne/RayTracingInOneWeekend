#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Macro.h"

class Image
{
public:
	Image(int32_t width, int32_t height);
	virtual ~Image();

	void SetPixel(int32_t x, int32_t y, const glm::vec4& color);
	void Export(const std::string& outputFileName);

	int32_t GetWidth() const { return _width; }
	int32_t GetHeight() const { return _height; }
	int32_t GetChannel() const { return _channel; }

private:
	int32_t _width = 0;
	int32_t _height = 0;
	int32_t _channel = 0;
	std::vector<uint8_t> _colorBuffer;
	std::string _outputFileExtension;
};
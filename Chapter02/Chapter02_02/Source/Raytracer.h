#pragma once

#include <string>
#include <vector>

#include <json/json.h>

#include "Macro.h"

class Raytracer
{
public:
	Raytracer() = default;
	virtual ~Raytracer() {}

	// [2025.05.31/������] Raytracer Ŭ������ ���� ������ �� ���� ������ ��������� ����!
	DISALLOW_COPY_AND_ASSIGN(Raytracer);
	
	void Initialize();
	void Run();
	void Export();

private:
	void LoadConfig();

private:
	int32_t _imageWidth = 0;
	int32_t _imageHeight = 0;
	int32_t _imageChannel = 0;
	std::vector<uint8_t> _imageBuffer;
	std::string _outputFileName;
	std::string _outputFileExtension;
};

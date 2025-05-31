#pragma once

#include <string>

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
	std::string _configPath;
	int _imageWidth;
	int _imageHeight;
};

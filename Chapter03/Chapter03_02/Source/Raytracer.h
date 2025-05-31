#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Image.h"
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
	std::string _outputFileName;
	std::unique_ptr<Image> _image;
};

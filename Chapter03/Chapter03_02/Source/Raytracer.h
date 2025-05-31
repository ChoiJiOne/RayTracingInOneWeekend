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

	// [2025.05.31/최지원] Raytracer 클래스의 복사 생성자 및 대입 연산자 명시적으로 삭제!
	DISALLOW_COPY_AND_ASSIGN(Raytracer);
	
	void Initialize();
	void Run();
	void Export();

private:
	std::string _outputFileName;
	std::unique_ptr<Image> _image;
};

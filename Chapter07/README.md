# Chapter07. Moving Camera Code Into Its Own Class

## 카메라 클래스 분리
- 카메라 설정 및 렌더링 코드를 `camera` 클래스로 분리
- 이 클래스는 다음의 두 가지 역할 수행:
    - 광선을 생성하여 월드에 발사  
    - 해당 광선의 결과를 바탕으로 이미지를 구성

## `camera` 클래스 구조

```cpp
#pragma once

#include "color.h"
#include "hittable.h"

class camera
{
public:
	camera()
	{
		initialize();
	}

	void render(const hittable& world);

private:
	void initialize();
	color ray_color(const ray& r, const hittable& world) const;

private:
	double _aspect_ratio = 1.0;
	int _image_width = 100;
	int _image_height = 0;
	point3 _center;
	point3 _pixel00_loc;
	vec3 _pixel_delta_u;
	vec3 _pixel_delta_v;
};
```
- `public` 메서드:
	- 렌더링 함수: `render()`
		- 메인 루프 및 픽셀별 Ray 생성
- `private` 메서드:
	- 초기화 함수: `initialize()`
		- 화면 사이즈 및 뷰포트 계산
	- 색상 계산: `ray_color()`
		- 히트 확인 후 색상 결정


## `main()` 함수
- `main()` 함수는 간결하게 유지
- world 객체만 구성
- camera 인스턴스를 생성 및 `render` 호출로 이미지 생성

```CPP
int main(void)
{
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5));
	world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0));

	camera cam;
	cam.render(world);

	return 0;
}
```
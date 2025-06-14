# Chapter04. Rays, Camera, and Background

## 핵심 개념 요약
- 광선(ray) 정의: 𝑃(𝑡) = 𝐴 + 𝑡 ⋅ 𝑏
	- 𝐴: ray origin
	- 𝑏: ray direction
	- 𝑡: scalar parameter (거리)
- 핵심 목표:
	= scene에 광선을 쏘고(ray tracing)
	- 어떤 색깔을 볼지 계산

## `ray` 클래스 정의

```CPP
class ray 
{
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction) {}

    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t) const 
	{
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};
```
- `at(t)`: 광선 상의 t 위치 계산
- 모든 ray tracing 시스템의 핵심 구성 요소

## 카메라 및 이미지 설정
- 해상도 & 비율 설정
	```CPP
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;
	```
- viewport 정의
	```CPP
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width)/image_height);
	auto focal_length = 1.0;

	auto camera_center = point3(0, 0, 0);
	```
- 뷰포트 벡터 계산
	```CPP
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	auto viewport_upper_left =
		camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;

	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	```
- 주의사항:
	- 이미지 좌표계는 y축이 반대임 (위에서 아래로 증가)

## 메인 루프

```CPP
for (int j = 0; j < image_height; j++) 
{
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) 
	{
        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto ray_direction = pixel_center - camera_center;
        ray r(camera_center, ray_direction);

        color pixel_color = ray_color(r);
        write_color(std::cout, pixel_color);
    }
}
```

## 배경 그라데이션 렌더링
- lerp (선형 보간): blended = (1 − 𝑎) ⋅ start + 𝑎 ⋅ end
- `ray_color()` 구현
	```CPP
	color ray_color(const ray& r) 
	{
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
	```
- 결과:
	- 위 → 흰색
	- 아래 → 파란색
	- 하늘 그라데이션 구현
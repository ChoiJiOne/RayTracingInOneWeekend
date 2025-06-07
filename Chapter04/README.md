# Chapter04. Rays, Camera, and Background
- 이 프로젝트는 레이 트레이싱(ray tracing) 기반으로, 픽셀마다 레이를 발사하고 해당 방향의 색상을 계산하여 이미지를 생성

## `Ray` class
- `ray`: 원점(origin)과 방향(direction)을 기반으로 정의
- `at(t) 함수`: 주어진 t 값에서의 위치를 반환

```CPP
class ray
{
public:
	ray() {}
	ray(const point3& origin, const vec3& direction)
		: _origin(origin), _direction(direction) {}

	const point3& origin() const { return _origin; }
	const vec3& direction() const { return _direction; }

	point3 at(double t) const
	{
		return _origin + (t * _direction);
	}

private:
	point3 _origin;
	vec3 _direction;
};
```

## 카메라 설정
- Aspect Ratio: 16:9 기준 (image_width / image_height)
- Viewport: 2.0 높이를 기준으로 계산된 가상 직사각형
- 초점 거리(focal_length): 1.0
- 카메라 위치(camera_center): (0,0,0)
- 픽셀 간격: pixel_delta_u, pixel_delta_v 계산
- 픽셀 시작 위치: pixel00_loc 기준으로 이미지 전 픽셀 위치 계산

## 배경 색상 그라디언트
- 레이의 방향 벡터를 정규화한 후 Y축 값을 기준으로 하늘색(파란색)과 흰색을 선형 보간(LERP)
- ray_color() 함수 구현 예:

```CPP
color ray_color(const ray& r) 
{
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
```

## 출력 결과
- 파란색(하늘색)에서 흰색으로 이어지는 수직 + 수평 그라디언트 배경이 출력됨
- 이미지 출력은 PPM 포맷으로, `> image.ppm` 형식으로 저장
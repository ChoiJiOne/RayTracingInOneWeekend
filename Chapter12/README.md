# Chapter12. Positionable Camera

## 기존 카메라의 한계
- 지금까지 카메라는 항상 (0,0,0)에서 (0,0,-1) 방향만 봄
- 필요한 개선사항
    - 시점 위치 조정
    - 시점 방향 조정
    - 시야각 조정 (Field of View)

## 수직 시야각 (Vertical Field of View)
- 수직 FOV를 기반으로 Viewport 크기 계산
    $$
    h = \tan\left(\frac{\theta}{2}\right)
    $$

    $$
    \text{viewportHeight} = 2 \cdot h \cdot \text{focalLength}
    $$

    $$
    \text{viewportWidth} = \text{viewportHeight} \cdot \frac{\text{imageWidth}}{\text{imageHeight}}
    $$
- focal length는 기본값 1.0 사용 가능

## 카메라 파라미터 추가

```CPP
double vfov = 90;            // Vertical Field of View (in degrees)
point3 lookfrom = (0,0,0);   // 카메라 위치
point3 lookat = (0,0,-1);    // 바라보는 지점
vec3 vup = (0,1,0);          // 월드 업 벡터
```

## 카메라 좌표계 생성 (Orthonormal Basis)
- 카메라 기준 좌표축 (u, v, w)
    $$
    w = \frac{lookfrom - lookat}{\|lookfrom - lookat\|}
    $$

    $$
    u = \frac{vup \times w}{\|vup \times w\|}
    $$

    $$
    v = w \times u
    $$
    - w: 바라보는 방향 반대
    - u: 카메라 오른쪽
    - v: 카메라 위쪽

## Viewport 위치 계산

```CPP
vec3 viewport_u = viewport_width * u;
vec3 viewport_v = viewport_height * -v;
pixel_delta_u = viewport_u / image_width;
pixel_delta_v = viewport_v / image_height;

auto viewport_upper_left = center - focal_length * w - viewport_u/2 - viewport_v/2;
pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
```

## 새로운 카메라 클래스 구조

```CPP
class camera 
{
public:
    double vfov = 90;
    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);
    ...
private:
    vec3 u, v, w;
    void initialize() { ... }
};
```

## 새로운 카메라 위치로 테스트
- 시점 이동:

```CPP
cam.lookfrom = point3(-2, 2, 1);
cam.lookat = point3(0, 0, -1);
cam.vup = vec3(0, 1, 0);
cam.vfov = 90;
```

## Zoom (FOV 변경)
- 시야각 축소 (줌 인):
    - FOV가 좁아질수록 더 줌인된 느낌
```cpp
cam.vfov = 20;
```
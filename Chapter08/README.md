# Chapter08. Antialiasing

## 계단 현상 (Aliasing) 개념 도입
- 렌더링 이미지 가장자리에서 "계단 현상(stair-stepping)" 발생
- 이 현상은 aliasing 또는 jaggies 라고 부름
- 현실 세계 이미지는 연속적 (infinite resolution)
- 현실에서는 한 픽셀 안에도 여러 색이 섞여 보임 (혼합광)
    - 이를 근사하기 위해 다중 샘플링(Antialiasing) 적용

## Point Sampling의 한계
- 기존: 픽셀 중심에서 단일 광선만 발사 → point sampling
- 문제: 멀리 있는 체스판 렌더링 시 흑/백 타일이 무작위로 과장됨
- 인간 눈은 이러한 경우 회색처럼 인지 (실제는 평균화된 빛)

## Supersampling 개념 도입
- 동일 픽셀 내 여러 지점에서 샘플링
- 모든 샘플의 결과 색을 평균화 → 부드러운 경계 생성
- 각 샘플은 픽셀 중심에서 무작위 오프셋 적용

## 랜덤 유틸리티 추가

```CPP
inline double random_double() 
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) 
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}
```
- `random_double()`로 `[0,1)` 난수 생성
- `random_double(min, max)`로 범위 난수 생성

## 무작위 샘플링 위치 계산
- 픽셀 내 정사각형 영역 안에서 오프셋 샘플

```CPP
vec3 sample_square() const 
{
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}
```

## 카메라의 다중 샘플 `get_ray()`
- 각 픽셀 내에서 약간 다른 위치에 광선 발사

```CPP
ray get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                       + ((i + offset.x()) * pixel_delta_u)
                       + ((j + offset.y()) * pixel_delta_v);

    return ray(center, pixel_sample - center);
}
```

## 색상 샘플 평균화
- 각 픽셀의 누적 색상 평균 적용

```CPP
pixel_color += ray_color(r, world);
final_color = pixel_color / samples_per_pixel;
```

## `write_color()`에서 범위 클램프 적용
- 최종 출력 RGB가 [0,1] 범위를 넘지 않도록 보정

```CPP
double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
```

## 최종 적용 파라미터

```CPP
camera cam;
cam.aspect_ratio = 16.0 / 9.0;
cam.image_width = 400;
cam.samples_per_pixel = 100;
cam.render(world);
```
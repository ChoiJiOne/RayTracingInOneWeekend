# Chapter13. Defocus Blur (Depth of Field)

## 개념 정리
- 실제 카메라는 핀홀이 아닌 렌즈를 사용 → Defocus Blur (Depth of Field) 발생
- 특정 거리(focus distance)에서는 선명, 그 외 거리는 흐릿
- aperture (조리개 크기) → defocus blur 크기 결정

## 우리 모델: Thin Lens Approximation
- 얇은 렌즈 모델 사용 → 단순화
- Focus Plane: lookfrom에서 focus distance 떨어진 평면
- Defocus Disk: 렌즈 위치에서 임의의 원판 위에서 광선 발사

## 파라미터 추가
- `defocus_angle == 0` → 기존 핀홀 카메라와 동일

```CPP
double focus_dist = 10;     // focus plane 까지 거리
double defocus_angle = 0;   // 렌즈 cone angle (조리개 역할)
```

## 렌즈 샘플링: 원판 안의 무작위 점 생성
- 원판 내 난수 생성
    ```CPP
    vec3 random_in_unit_disk() 
    {
        while (true) 
        {
            auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
            if (p.length_squared() < 1)
                return p;
        }
    }
    ```
- 최종 샘플링 위치 계산
    ```CPP
    point3 defocus_disk_sample() const 
    {
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
    ```

## defocus_disk basis 벡터 계산
- 렌즈 원판의 가로/세로 반경
```CPP
auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
defocus_disk_u = u * defocus_radius;
defocus_disk_v = v * defocus_radius;
```

## 카메라의 `get_ray()` 변경
- 기존 center 출발 → 렌즈 원판 출발로 변경
```CPP
ray get_ray(int i, int j) const
{
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}
```

## 최종 테스트 설정
- `defocus_angle` 클수록 흐림 증가

```CPP
cam.vfov     = 20;
cam.lookfrom = point3(-2,2,1);
cam.lookat   = point3(0,0,-1);
cam.vup      = vec3(0,1,0);

cam.defocus_angle = 10.0;
cam.focus_dist    = 3.4;
```
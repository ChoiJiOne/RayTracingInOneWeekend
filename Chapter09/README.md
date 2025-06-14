# Chapter09. Diffuse Materials

## 재질 시스템 분리 개념 도입
- 재질(Material)과 기하(Geometry)를 분리
- 재질 시스템 설계 → 여러 오브젝트에서 재질 재사용 가능

## 난반사(Diffuse, Matte) 개념
- 입사광이 표면에서 여러 방향으로 퍼짐 (산란)
- 현실 세계에서 대부분의 재질은 디퓨즈 성질 가짐
- 이상적 난반사는 모든 반사 방향이 균등 확률

## 반사 벡터 샘플링을 위한 랜덤 벡터 생성
- 단위 구 내부의 랜덤 벡터 필요

```CPP
vec3 random_unit_vector() 
{
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}
```

## Hemisphere 샘플링
- 생성된 랜덤 벡터가 노멀과 같은 반구 위에 있도록 보정
    - 이를 통해 디퓨즈 난반사 시뮬레이션 가능

```CPP
vec3 random_on_hemisphere(const vec3& normal) 
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

```

## ray_color 함수 수정
- 산란 반사 구현 (0.5 reflectance)
    - 이 함수는 재귀 호출 → 무한반사 방지 필요

```CPP
if (world.hit(r, interval(0.001, infinity), rec)) 
{
    vec3 direction = random_on_hemisphere(rec.normal);
    return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
}

```

## 최대 재귀 깊이 도입

```CPP
if (depth <= 0)
    return color(0, 0, 0);
```

- `max_depth` 파라미터를 카메라에 추가

```CPP
cam.max_depth = 50;
```

## Shadow Acne 방지 (Self-Intersection 문제 해결)
- 매우 작은 epsilon offset 사용 → 교차점 무시

```CPP
if (world.hit(r, interval(0.001, infinity), rec)) { ... }
```

## Lambertian 난반사 도입
- 좀 더 현실적인 $\cos(\phi)$ 기반 분포 적용
- 단순히 normal + random_unit_vector()로 구현

```CPP
vec3 direction = rec.normal + random_unit_vector();
return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
```

## 밝기 문제 → 감마 보정 도입
- 렌더링된 색상이 실제 반사율보다 어둡게 보이는 현상은 감마 보정이 없기 때문
- 대부분의 이미지 뷰어는 감마 보정된(gamma space) 이미지를 기대하지만, 렌더러는 선형 공간(linear space)으로 출력
- 이를 보정하기 위해 출력 전에 각 색상 성분에 루트 연산(√x)을 적용
- 감마 2.0 보정 → $\sqrt{linearComponent}$ 적용
    - `write_color` 함수에서 적용

```CPP
inline double linear_to_gamma(double linear_component) 
{
    return (linear_component > 0) ? sqrt(linear_component) : 0;
}
```
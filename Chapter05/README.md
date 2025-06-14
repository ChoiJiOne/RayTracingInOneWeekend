# Chapter05. Adding a Sphere

## 핵심 목표
- 첫 번째 오브젝트 추가: Sphere
- Ray-Sphere 교차 판정 구현
- 교차 여부에 따라 색상 결정

## 수학적 배경
- 구(Sphere) 방정식
  - `(x - Cx)² + (y - Cy)² + (z - Cz)² = r²`
- 벡터 형태
  - `(P - C) · (P - C) = r²`
- Ray 방정식
  - `P(t) = Q + t·d`
- 대입
  - `(P(t) - C) · (P(t) - C) = r²`
  - `((Q + t·d) - C) · ((Q + t·d) - C) = r²`
- 전개 및 정리 → 이차방정식 형태
  - `t²(d·d) - 2t(d·(Q - C)) + (Q - C)·(Q - C) - r² = 0`
- 이차방정식 계수:  
  `a·t² + b·t + c = 0`  
  - `a = d · d`  
  - `b = -2(d · (C - Q))`  
  - `c = (C - Q) · (C - Q) - r²`
- 판별식(Discriminant):  
  - `Δ = b² - 4ac`  
    - `Δ > 0`: 두 교차점  
    - `Δ = 0`: 접점  
    - `Δ < 0`: 교차 없음

## 교차 판정 함수

```CPP
bool hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
```

## `ray_color()` 수정
- 구에 교차 시 빨간색 출력
- 아니면 기존 배경 그라데이션

```CPP
color ray_color(const ray& r) 
{
    if (hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0); // 빨간색

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
```
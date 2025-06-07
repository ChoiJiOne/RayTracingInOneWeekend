# Chapter05. Adding a Sphere
- 레이 트레이서에 처음으로 하나의 물체(구)를 추가
- 구는 수학적으로 광선과의 교차 계산이 간단하여 자주 사용

## 구의 방정식
- 중심이 원점일 경우: `x² + y² + z² = r²`
- 중심이 C일 경우: `(P - C) · (P - C) = r²`

## 교차 조건 유도
- 반지름이 `r`, 중심이 원점인 구의 방정식:  
  `x² + y² + z² = r²`
- 중심이 임의의 위치 `C = (Cx, Cy, Cz)`일 경우, 벡터 형태로 표현:  
  `(P - C) · (P - C) = r²`
- 광선(ray)의 방정식:  
  `P(t) = Q + t·d`
- 구의 표면을 광선이 통과할 조건:  
  `(P(t) - C) · (P(t) - C) = r²`
- 위 식을 정리:  
  `((Q + t·d) - C) · ((Q + t·d) - C) = r²`
- 벡터 대수 전개:  
  `t²(d·d) - 2t(d·(Q - C)) + (Q - C)·(Q - C) - r² = 0`
- 이차방정식 형태로 표현:  
  `a·t² + b·t + c = 0`  
  - `a = d · d`  
  - `b = -2(d · (C - Q))`  
  - `c = (C - Q) · (C - Q) - r²`
- 판별식(Discriminant)으로 교차 여부 확인:  
  `Δ = b² - 4ac`  
  - `Δ > 0`: 두 교차점  
  - `Δ = 0`: 접점  
  - `Δ < 0`: 교차 없음

## 첫 번째 Raytraced 이미지
- Z축 `-1` 위치에 중심을 둔 반지름 0.5의 구 생성
- 해당 구와 교차하는 픽셀은 빨간색으로 출력
    - 출력 결과는 화면 중앙에 빨간 구가 표시되고, 나머지 영역은 하늘색-흰색 그라디언트로 채워짐
    - 현재 구현은 t < 0인 경우도 통과시키므로, 카메라 뒤쪽에 있는 구도 렌더링됨 → 이후 수정 예정
```cpp
bool hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color ray_color(const ray& r) 
{
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
        return color(1, 0, 0); // 빨간색으로 렌더링

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); // 배경 그라디언트
}
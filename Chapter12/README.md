# Chapter12. Positionable Camera
- 카메라는 시야각(Field of View)과 위치, 방향 등을 조정할 수 있는 객체
- 디버깅이 어렵기 때문에 점진적으로 구현하며, 수직 시야각(vertical FOV)을 기준으로 설정

## 시야각(Field of View, FOV) 설정
- vfov: 수직 시야각 (단위: 도 → 내부적으로 라디안으로 변환)
- 시야각에 따라 화면 확대/축소 효과가 발생
- 카메라에서 뷰포트로의 거리에 따라 뷰포트 크기(viewport_height, viewport_width)가 결정

```CPP
auto theta = degrees_to_radians(vfov);
auto h = std::tan(theta / 2);
auto viewport_height = 2 * h * focal_length;
```
## 카메라 방향 설정
- 카메라 위치: `lookfrom`
- 카메라가 바라보는 지점: `lookat`
- 카메라 기준 위쪽 방향: `vup` (보통 (0,1,0) 사용)
- 이 세 벡터를 통해 카메라 기준 직교 좌표계(u, v, w)를 정의:
    - `w`: 시선 반대 방향 단위 벡터
    - `u`: 오른쪽 방향 단위 벡터
    - `v`: 위쪽 방향 단위 벡터

```CPP
w = unit_vector(lookfrom - lookat);
u = unit_vector(cross(vup, w));
v = cross(w, u);
```
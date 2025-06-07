# Chapter03. The `vec3` class
- 이 프로젝트는 벡터 연산과 색상 표현을 위해 간단한 `vec3` 클래스를 사용

## `vec3.h`
- vec3는 3차원 벡터를 나타내며 위치, 색상, 방향 등에 재사용
- point3, color는 vec3의 타입 별칭(alias)으로 가독성 향상
- 주요 기능:
    - 벡터 연산자 오버로딩 (+, -, *, /)
    - 길이, 정규화 함수 (`length()`, `unit_vector()`)
    - 내적 `dot()`, 외적 `cross()`

## `color.h`
- color는 vec3의 별칭으로 색상 출력을 담당
- `write_color()` 함수는 RGB 값을 [0.0, 1.0] 범위에서 [0, 255] 정수로 변환 후 PPM 형식으로 출력
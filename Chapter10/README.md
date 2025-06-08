# Chapter10. Metal
- material은 추상 클래스이며 scatter()로 산란 여부와 감쇠값 결정
- hit_record는 교차 지점, 법선, 재질 포인터 등 포함

## Lambertian (확산 재질)
- 항상 산란하며 색상은 `albedo`로 감쇠
- 산란 벡터가 0에 가까운 경우 대비해 `near_zero()` 사용

## Metal (금속 재질)
- 반사 벡터: `reflect(v, n) = v - 2(v·n)n`
- 광선은 반사 방향으로 산란, `albedo`로 감쇠

## Fuzz (흐림 효과)
- 반사 벡터에 `fuzz * random_unit_vector()` 추가
    - `fuzz = 0`: 완전 거울 
    - `fuzz > 0`: 흐릿한 금속 반사
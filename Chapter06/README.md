# Chapter06. Surface Normals and Multiple Objects
- 구체와의 교차점을 통해 법선 벡터(surface normal) 를 계산하고 시각화
- 단위 벡터를 RGB 색상에 매핑하여 표면 방향을 시각적으로 표현
- 표면 법선 계산
    ```CPP
    vec3 N = unit_vector(hit_point - center);
    return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
    ```

## Abstraction: `hittable` Interface
- `hittable`: 레이와 교차할 수 있는 모든 객체의 추상 인터페이스
- `hit()` 함수는 교차 여부와 법선, 위치, t값 등을 반환
- `hit_record`: 교차 정보 저장
- `set_face_normal()`: 법선 방향 결정 (앞면/뒷면)

## `Sphere` Implementation
- `sphere`: hittable을 상속하여 교차 판정 구현
- `hit()`: 교차 지점을 계산하고 법선을 설정
- 내부/외부 판별을 통해 렌더링 로직에 활용

## Managing Multiple Objects: `hittable_list`
- 여러 객체를 저장하고 순차적으로 hit() 검사
- 가장 가까운 객체만 반환하여 중복 렌더링 방지
- `std::vector<shared_ptr<hittable>>` 사용

##  Precision with Intervals: `interval`
- 실수 범위(t값 등)를 명확하게 표현하는 interval 클래스 도입
- `contains(x)` / `surrounds(x)` 메서드로 범위 유효성 체크
- `hittable`, `hittable_list`, `sphere`, `main` 모두 interval 기반으로 t-range 처리

## Rendering Logic
- `ray_color()`: hittable 객체와의 교차 여부에 따라 색상 결정
    ```CPP
    if (world.hit(r, interval(0, infinity), rec)) 
    {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    ```
- 다수의 구와 지면 포함된 world 생성
    ```CPP
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    ```
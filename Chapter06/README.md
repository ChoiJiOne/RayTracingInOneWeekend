# Chapter06. Surface Normals and Multiple Objects

## 핵심 목표
- 표면 노멀(Surface Normals) 계산 → 간단한 shading 구현
- 다중 오브젝트 지원 → hittable 추상 클래스 도입
- 코드 구조화 → 추상화 및 클래스 분리

## 노멀 벡터
- 교차 지점에서의 법선 벡터 (표면에 수직인 단위 벡터)
- Sphere의 경우:
    $$
    Normal = \frac{P - C}{r}
    $$
- `unit_vector` 로 항상 정규화 수행 (단위벡터 유지)

## 노멀을 이용한 색상 시각화
- `(x, y, z)` 값이 `[-1, 1]` 범위 → 색상으로 매핑하기 위해 `0.5 * (N + 1)` 사용

```CPP
color ray_color(const ray& r) 
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) 
    {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
    }
    ...
}
```

## `hit_sphere()` 개선

- 기존 이차방정식 형태를 단순화

```CPP
double hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) return -1.0;
    return (h - sqrt(discriminant)) / a;
}
```

## 추상화: hittable 시스템 설계
- hittable 인터페이스 도입 (가상 클래스)
- `hittable`: 레이와 교차할 수 있는 모든 객체의 추상 인터페이스
- `hit()` 함수는 교차 여부와 법선, 위치, t값 등을 반환
- `hit_record`: 교차 정보 저장
- `set_face_normal()`: 법선 방향 결정 (앞면/뒷면)
- front-face 계산을 여기서 수행하여 후속 shading 계산 단순화

```CPP
class hit_record 
{
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable 
{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

```

## sphere 클래스 구현
- `sphere`: hittable을 상속하여 교차 판정 구현
- `hit()`: 교차 지점을 계산하고 법선을 설정
- 내부/외부 판별을 통해 렌더링 로직에 활용

```CPP
class sphere : public hittable 
{
public:
    sphere(const point3& center, double radius)
        : center(center), radius(fmax(0, radius)) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
    {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;

        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);
        auto root = (h - sqrtd) / a;
        if (root < t_min || root > t_max) {
            root = (h + sqrtd) / a;
            if (root < t_min || root > t_max)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};
```

## hittable_list (다중 오브젝트 지원)
- 여러 객체를 저장하고 순차적으로 hit() 검사
- 가장 가까운 객체만 반환하여 중복 렌더링 방지
- `std::vector<shared_ptr<hittable>>` 사용

```CPP
class hittable_list : public hittable 
{
public:
    vector<shared_ptr<hittable>> objects;

    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object : objects) 
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec)) 
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};
```

## interval 클래스 도입
- 실수 범위(t값 등)를 명확하게 표현하는 interval 클래스 도입
- `contains(x)` / `surrounds(x)` 메서드로 범위 유효성 체크
- `hittable`, `hittable_list`, `sphere`, `main` 모두 interval 기반으로 t-range 처리

```CPP
class interval 
{
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}

    bool surrounds(double x) const 
    {
        return min < x && x < max;
    }
};
```

## 최종 `ray_color()`

```CPP
color ray_color(const ray& r, const hittable& world) 
{
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec))
        return 0.5 * (rec.normal + color(1,1,1));

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
```

## 렌더링 로직

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
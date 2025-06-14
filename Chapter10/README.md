# Chapter10. Metal

## 재질 시스템 설계 결정
- 다양한 재질을 지원하기 위해 추상 클래스 material 도입
- 모든 재질은 `scatter()` 함수를 통해 산란 결과를 계산
- `scatter()` 역할:
    - 산란 여부 결정 (bool 반환)
    - 산란 광선(scattered) 반환
    - 감쇠값(attenuation, 색상) 반환

```CPP
class material {
public:
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};
```

## hit_record에 재질 추가
- 각 교차 지점에 재질 정보를 포함해야 함
- `shared_ptr<material>` 로 재질 저장

```CPP
class hit_record 
{
public:
    point3 p;
    vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face;
};
```

- Sphere 충돌 시 `rec.mat` 세팅

```CPP
rec.mat = mat;
```

## Lambertian (디퓨즈 재질) 재구현
- `scatter()` 함수 오버라이드
- 항상 난반사 → Lambertian 분포 적용
- albedo: 반사율

```CPP
class lambertian : public material 
{
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
    {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};
```

- 보호 코드: `near_zero()` → 산란 방향이 거의 0일 경우 보정

```CPP
bool near_zero() const 
{
    auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}
```

## Metal 재질 기본 반사 구현
- 반사 광선은 스펙큘러 반사:
    - 반사 공식 사용
    $$
    \mathbf{R} = \mathbf{V} - 2(\mathbf{V} \cdot \mathbf{N}) \mathbf{N}
    $$
- 반사 함수
    ```CPP
    vec3 reflect(const vec3& v, const vec3& n)
    {
        return v - 2 * dot(v, n) * n;
    }
    ```
- Metal 클래스 구현
    ```CPP
    class metal : public material 
    {
    public:
        metal(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
        {
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }
    private:
        color albedo;
    };
    ```

## `ray_color()` 재질 시스템 적용
- 재질에 따라 산란 방식 결정

```CPP
if (world.hit(r, interval(0.001, infinity), rec)) 
{
    ray scattered;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered))
        return attenuation * ray_color(scattered, depth - 1, world);
    return color(0, 0, 0);
}
```

## Sphere 생성자에서 재질 주입

```CPP
sphere(const point3& center, double radius, shared_ptr<material> mat)
    : center(center), radius(std::fmax(0, radius)), mat(mat) {}
```

## Metal + Lambertian 혼합 장면 구성

```CPP
world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
```

## Metal Fuzziness 도입 (거친 금속 표현)
- fuzz 값 추가 → 반사 광선에 랜덤 노이즈 추가
    - fuzz가 클수록 흐릿한 금속 효과 → 디퓨즈와 스펙큘러 사이를 조절 가능
```CPP
class metal : public material {
public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
    {
        vec3 reflected = unit_vector(reflect(r_in.direction(), rec.normal));
        reflected += fuzz * random_unit_vector();
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    color albedo;
    double fuzz;
};
```
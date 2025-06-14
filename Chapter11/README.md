# Chapter11. Dielectrics

## 유전체 (Dielectrics) 개념 도입
- 투명한 재질: 물, 유리, 다이아몬드 등
- 입사광이 반사(reflection) 와 굴절(refraction) 로 나뉨
- 굴절량은 굴절률(refractive index, $\eta$)에 의해 결정됨
- 상대 굴절률 사용: $\eta_{rel} = \frac{\eta_{inside}}{\eta_{outside}}$

| Material | Index (\$\eta\$) |
| -------- | ---------------- |
| Air      | 1.0003           |
| Water    | 1.333            |
| Glass    | 1.5\~1.7         |
| Diamond  | 2.4              |

## Snell's Law (스넬의 법칙)

- 입사각과 굴절각의 관계
- 단위벡터 사용 시 dot product로 $\cos \theta$ 계산 가능

$$\eta \cdot \sin \theta = \eta' \cdot \sin \theta'$$

$$\cos \theta = \mathbf{a} \cdot \mathbf{b}$$


## 굴절 벡터 계산 (벡터 수식)
- 굴절 벡터:
    $$\mathbf{r_\perp} = \frac{\eta}{\eta'} (\mathbf{v} + \cos\theta \cdot \mathbf{n})$$
    $$\mathbf{r_\parallel} = -\sqrt{1 - |\mathbf{r_\perp}|^2} \cdot \mathbf{n}$$
    $$\mathbf{refracted} = \mathbf{r_\perp} + \mathbf{r_\parallel}$$
- C++ 함수 구현:
    ```CPP
    vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) 
    {
        auto cos_theta = std::fmin(dot(-uv, n), 1.0);
        vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
        vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }
    ```

## 유전체 재질 클래스 (굴절만 수행)
- 항상 굴절시키는 단순 버전
```CPP
class dielectric : public material 
{
public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
    {
        attenuation = color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction = unit_vector(r_in.direction());
        vec3 refracted = refract(unit_direction, rec.normal, ri);

        scattered = ray(rec.p, refracted);
        return true;
    }

private:
    double refraction_index;
};
```

## 전반사 (Total Internal Reflection) 처리
- 임계각 초과시 굴절 불가 → 반드시 반사
    ```CPP
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    bool cannot_refract = ri * sin_theta > 1.0;
    ```
- 조건문 추가:
    ```CPP
    if (cannot_refract)
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);
    ```

## Schlick 근사 (반사율 근사)
- 각도에 따라 반사 확률 변동 → 반사율 근사 적용
    $$R(\theta) = R_0 + (1 - R_0)(1 - \cos\theta)^5$$
    $$R_0 = \left( \frac{1 - \eta}{1 + \eta} \right)^2$$
- C++ 구현:
    ```CPP
    static double reflectance(double cosine, double refraction_index) 
    {
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
    ```
- 최종 `scatter()` 수정:
    ```CPP
    if (cannot_refract || reflectance(cos_theta, ri) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);
    ```

## 유전체 씬 예제: 공기 방울과 중공구 구현

- 외부 → 내부 재질 간 상대굴절률 사용
    ```CPP
    auto material_left   = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    ```
- 내부구 (bubble sphere) 추가
    ```CPP
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    ```
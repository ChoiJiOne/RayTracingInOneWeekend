# Chapter03. The `vec3` class

## 목적
- 벡터와 색상 표현 클래스 작성
- vec3 클래스 → 위치, 방향, 색상 등 모든 3D 값 표현
- 타입 명확성을 위해 type alias 사용:
    - point3 → 위치
    - color → 색상

## `vec3` 클래스 정의

```CPP
class vec3 
{
public:
    double e[3];

    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v);
    vec3& operator*=(double t);
    vec3& operator/=(double t);

    double length() const;
    double length_squared() const;
};
```
- 연산자 오버로딩을 활용하여 직관적 벡터 연산 지원
- 길이 및 길이제곱 함수 포함

## 연산자 구현

```CPP
vec3& vec3::operator+=(const vec3& v) 
{
    e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(double t) 
{
    e[0] *= t; e[1] *= t; e[2] *= t;
    return *this;
}

vec3& vec3::operator/=(double t) 
{
    return *this *= 1/t;
}

double vec3::length() const 
{
    return std::sqrt(length_squared());
}

double vec3::length_squared() const 
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}
```

## 유틸리티 함수 정의

- 벡터 출력
    ```cpp
    inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }
    ```
- 벡터 연산
    ```cpp
    inline vec3 operator+(const vec3& u, const vec3& v);
    inline vec3 operator-(const vec3& u, const vec3& v);
    inline vec3 operator*(const vec3& u, const vec3& v);
    inline vec3 operator*(double t, const vec3& v);
    inline vec3 operator/(const vec3& v, double t);
    ```
- 내적 (dot product)
    ```cpp
    inline double dot(const vec3& u, const vec3& v) 
    {
        return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
    }
    ```
- 외적 (cross product)
    ```cpp
    inline vec3 cross(const vec3& u, const vec3& v) 
    {
        return vec3(
            u.e[1]*v.e[2] - u.e[2]*v.e[1],
            u.e[2]*v.e[0] - u.e[0]*v.e[2],
            u.e[0]*v.e[1] - u.e[1]*v.e[0]
        );
    }
    ```
- 단위 벡터 (normalize)
    ```CPP
    inline vec3 unit_vector(const vec3& v) 
    {
        return v / v.length();
    }
    ```

## 타입 alias
- 읽기 편의성 ↑
- 타입 체크는 하지 않음

```CPP
using point3 = vec3;  // 위치 좌표용
using color = vec3;   // 색상용
```

## 색상 출력 유틸리티 함수
- [0,1] → [0,255] 스케일 변환

```CPP
void write_color(std::ostream& out, const color& pixel_color) 
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
```

## 최종 main() 갱신
- 기존과 출력 결과 동일 (우하단 노란색 그라데이션)

```CPP
int main() 
{
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) 
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) 
        {
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
```
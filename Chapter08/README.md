# Chapter08. Antialiasing
- 계단 현상(Aliasing): 픽셀 중심에서만 샘플링 시 발생하는 경계선의 계단형 왜곡
- 안티앨리어싱(Antialiasing): 픽셀 내 여러 지점 샘플 → 평균화 → 부드러운 경계
- 실제 세계는 연속적임 → 다수 샘플로 근사 필요
- Point Sampling: 픽셀 중심 1점만 샘플 → 노이즈 발생
- Supersampling: 픽셀 영역 내 랜덤 다중 샘플링 → 결과 평균 → 노이즈 감소

## 샘플링 전략
- 각 픽셀을 주변 사각형 영역에서 다중 샘플링
- 샘플 위치는 픽셀 내에서 무작위 오프셋 사용
- 샘플 개수: `samples_per_pixel`

## 수식 요약

$$
\text{final\_color} = \frac{1}{N} \sum_{i=1}^{N} \text{ray\_color}(r_i)
$$

$$
\text{offset} = (\text{random()} - 0.5, \text{random()} - 0.5)
$$


## 핵심 코드

- 랜덤 유틸리티
    ```CPP
    inline double random_double() 
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }
    ```
- 샘플링 오프셋
    ```CPP
    vec3 sample_square() 
    {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    ```
- 광선 생성 (다중 샘플 적용)
    ```CPP
    ray get_ray(int i, int j) 
    {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
            + ((i + offset.x()) * pixel_delta_u)
            + ((j + offset.y()) * pixel_delta_v);

        return ray(center, pixel_sample - center);
    }
    ```
- 색상 출력 (클램프)
    ```CPP
    double clamp(double x, double min, double max) 
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
    ```
- 평균 적용
    ```CPP
    pixel_color += ray_color(r, world);
    final_color = pixel_color / samples_per_pixel;
    ```


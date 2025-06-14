# Chapter14. Where Next?

## 최종 장면: 모든 기능 종합 테스트

### 랜덤 구 생성
- 랜덤하게 많은 작은 구 생성
- 서로 겹치지 않도록 충돌 검사

```CPP
for (int a = -11; a < 11; a++) 
{
    for (int b = -11; b < 11; b++) 
    {
        auto choose_mat = random_double();
        point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

        if ((center - point3(4, 0.2, 0)).length() > 0.9) 
        {
            shared_ptr<material> sphere_material;

            if (choose_mat < 0.8) 
            {
                auto albedo = color::random() * color::random();
                sphere_material = make_shared<lambertian>(albedo);
            } 
            else if (choose_mat < 0.95) 
            {
                auto albedo = color::random(0.5, 1);
                auto fuzz = random_double(0, 0.5);
                sphere_material = make_shared<metal>(albedo, fuzz);
            } 
            else 
            {
                sphere_material = make_shared<dielectric>(1.5);
            }

            world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
    }
}
```


### 3개의 큰 구 생성 (대표 구)

```CPP
world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));
world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, make_shared<lambertian>(color(0.4, 0.2, 0.1))));
world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)));
```

### 바닥 구 (거대한 plane 역할)

```CPP
world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(color(0.5, 0.5, 0.5))));
```

## 최종 카메라 설정
- 모든 카메라 기능 (FOV, 위치, DoF) 종합 적용
```CPP
cam.aspect_ratio      = 16.0 / 9.0;
cam.image_width       = 1200;
cam.samples_per_pixel = 500;
cam.max_depth         = 50;

cam.vfov     = 20;
cam.lookfrom = point3(13, 2, 3);
cam.lookat   = point3(0, 0, 0);
cam.vup      = vec3(0, 1, 0);

cam.defocus_angle = 0.6;
cam.focus_dist    = 10.0;
```

## 출력 특징
- Glass sphere → 사실상 그림자 없음 → 현실에서도 비슷한 현상
- Random scene → 다양한 재질 + 산란 조합 시뮬레이션
- 최종 결과 → 이 책의 표지 이미지 완성


## 다음 단계 (이후 책 소개)

### Book 2: Ray Tracing The Next Week
- Motion Blur (움직임 흐림)
- Bounding Volume Hierarchies (가속 구조)
- Texture Mapping (텍스처 맵핑)
- Perlin Noise (펄린린 노이즈)
- Quadrilaterals, Disks, Triangles (다양한 도형)
- Light Source (조명 시스템)
- Transforms (이동, 회전, 스케일)
- Volumetric Rendering (볼륨 렌더링)

### Book 3: Ray Tracing The Rest of Your Life
- 고급 최적화 및 렌더링 기술
- Subsurface Scattering
- Nested Dielectrics
- 프로페셔널급 렌더러 기반 구축

## 추가 확장 방향
- Triangles (일반 모델 지원)
- Parallelism (병렬 처리 확장)
- Shadow Rays (정확한 그림자 처리)
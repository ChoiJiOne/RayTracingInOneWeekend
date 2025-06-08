# Chapter14. Where Next?

## Final Render: 랜덤한 수많은 구체 장면
- 지면 구체 + 수백 개의 작은 구체를 무작위 재질로 배치 (Diffuse, Metal, Dielectric).
- 중심부에는 세 가지 큰 구체(유리, 금속, 램버시안)를 배치.
- 카메라 설정:
    - samples_per_pixel = 500 (고품질)
    - defocus_angle = 0.6, focus_dist = 10.0
- Glass 재질 특성상 그림자가 옅거나 없어 보이는 효과 발생.

## 다음 단계 (Next Steps)

### Book 2: Ray Tracing: The Next Week
- Motion Blur: 움직이는 물체의 현실적 표현
- BVH (Bounding Volume Hierarchies): 렌더링 성능 향상
- Texture Mapping: 이미지 기반 표면 표현
- Perlin Noise: 노이즈 기반 텍스처, 절차적 생성
- 사각형(Quad): 다양한 2D 기하 형태의 기반
- Light Sources: 명시적인 광원 추가
- Transform: 위치, 회전 등 변환 지원
- Volumetric Rendering: 연기, 구름 등 부피 기반 효과

### Book 3: Ray Tracing: The Rest of Your Life
- 이미지 품질 및 렌더러 성능 개선
- 고급 효과 (예: 서브서피스 스캐터링, 중첩 유전체 등) 구현 기반 제공

### 기타 확장 방향
- 삼각형 기반 모델 로딩: 실질적인 모델 렌더링
- 병렬 처리: 멀티코어/멀티스레드 렌더링 최적화
- Shadow Rays: 정확한 그림자 계산 (부드러운 그림자 구현 가능)
# Chapter02. Output an Image

## 목적
- 렌더링 결과 출력 준비
- 가장 단순한 이미지 포맷인 PPM (Portable Pixmap) 활용

## PPM 파일 포맷
- 아스키 텍스트 기반 (읽고 쓰기 쉬움)
- 파일 포맷 구조:
  ```
  P3
  <image_width> <image_height>
  255
  R G B
  R G B
  ...
  ```
- 각 픽셀: 0~255 범위의 정수 (R G B 순서)

## 첫 번째 이미지 생성 코드

```CPP
#include <iostream>

int main() 
{
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) 
    {
        for (int i = 0; i < image_width; i++) 
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
```
- 좌상단 → (0,0), 좌하단 → (0, image_height-1)
- 빨간색: 좌 → 우로 증가
- 초록색: 상 → 하로 증가
- 오른쪽 아래 모서리는 노란색 (r=1, g=1, b=0)

## 진행 중 렌더링 상태 표시 (Progress Indicator)
- std::clog 사용 → 진행상황 표시
  - 향후 오래 걸리는 렌더링 작업에서 유용
  
```CPP
for (int j = 0; j < image_height; ++j) 
{
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) 
    {
        auto r = double(i) / (image_width-1);
        auto g = double(j) / (image_height-1);
        auto b = 0.0;

        int ir = int(255.999 * r);
        int ig = int(255.999 * g);
        int ib = int(255.999 * b);

        std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
}
std::clog << "\rDone.                 \n";
```
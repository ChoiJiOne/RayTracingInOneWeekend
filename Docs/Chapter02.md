# 2. Output an Image

## 2.1 The PPM Image Format

렌더러를 시작할 때마다 이미지를 확인할 수 있는 방법이 필요합니다. 가장 직관적인 방법은 이미지를 파일로 저장하는 것입니다. 다만, 파일 형식이 매우 다양하다는 점이 문제입니다. 그중 많은 형식은 복잡합니다. 저는 항상 가장 단순한 텍스트 형식인 PPM 파일부터 시작합니다. 다음은 위키백과에 나온 좋은 설명입니다:

![fig-1.01-ppm.jpg](./Image/fig-1.01-ppm.jpg)

그럼 이제 그런 파일을 출력하는 C++ 코드를 작성해 보겠습니다:

```CPP
#include <iostream>

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
```

이 코드에서 주의할 점은 다음과 같습니다:

1. 픽셀은 행 단위로 출력됩니다.

2. 각 행의 픽셀은 왼쪽에서 오른쪽 방향으로 출력됩니다.

3. 이러한 행들은 위쪽에서 아래쪽 방향으로 출력됩니다.

4. 일반적으로 빨강/초록/파랑(RGB) 각각의 성분은 내부적으로 0.0에서 1.0 사이의 실수형 변수로 표현됩니다. 이를 출력하기 전에 반드시 0부터 255 사이의 정수 값으로 스케일링해야 합니다.

5. 빨간색은 왼쪽에서 오른쪽으로 갈수록 점점 밝아지며(검정에서 밝은 빨강으로), 초록색은 위에서 아래로 갈수록 점점 밝아집니다(검정에서 밝은 초록으로). 빨강과 초록이 합쳐지면 노란색이 되므로, 화면의 오른쪽 아래 모서리는 노란색이 될 것으로 예상할 수 있습니다.

## 2.2 Creating an Image File

파일이 표준 출력 스트림으로 기록되기 때문에, 이를 이미지 파일로 저장하려면 리디렉션을 사용하셔야 합니다. 일반적으로는 명령줄에서 > 리디렉션 연산자를 사용합니다.

Windows에서는 CMake를 통해 디버그 빌드를 수행한 뒤 다음 명령어로 실행하실 수 있습니다:

```PowerShell
cmake -B build
cmake --build build
```

그런 다음, 새로 빌드한 프로그램을 다음과 같이 실행합니다:

```PowerShell
build\Debug\inOneWeekend.exe > image.ppm
```

나중에는 속도를 위해 최적화된 빌드를 사용하는 것이 더 좋습니다. 이 경우 다음과 같이 빌드합니다:

```PowerShell
cmake --build build --config release
```

그리고 최적화된 프로그램은 다음과 같이 실행합니다:

```PowerShell
build\Release\inOneWeekend.exe > image.ppm
```

위 예제는 CMake로 빌드하는 경우를 가정하며, 제공된 소스의 `CMakeLists.txt` 파일과 같은 방식을 사용합니다. 자신이 가장 익숙한 빌드 환경(및 언어)을 사용하셔도 괜찮습니다.

Mac이나 Linux에서 릴리즈 빌드된 프로그램은 다음과 같이 실행합니다:

```PowerShell
build/inOneWeekend > image.ppm
```

[프로젝트 README 파일](https://raytracing.github.io/README.md)에 전체 빌드 및 실행 방법이 안내되어 있습니다.

출력된 파일을 열어보면 (저는 Mac에서 ToyViewer로 열었지만, 선호하는 이미지 뷰어를 사용하시거나, 지원되지 않는 경우 “ppm viewer”를 검색해 보세요) 다음과 같은 결과를 확인할 수 있습니다:

![img-1.01-first-ppm-image.png](./Image/img-1.01-first-ppm-image.png)

만세! 이것이 그래픽스 세계의 “Hello World”입니다. 만약 이미지가 예상과 다르게 보인다면, 출력된 파일을 텍스트 편집기로 열어보시고 내용을 확인해 보세요. 파일은 다음과 비슷한 형태로 시작해야 합니다:

```PowerShell
P3
256 256
255
0 0 0
1 0 0
2 0 0
3 0 0
4 0 0
5 0 0
6 0 0
7 0 0
8 0 0
9 0 0
10 0 0
11 0 0
12 0 0
...
```

PPM 파일이 이런 형태가 아니라면, 출력 형식 관련 코드를 다시 한번 꼼꼼히 확인해 보셔야 합니다. 만약 형식은 맞지만 이미지가 제대로 표시되지 않는다면, 줄바꿈 방식의 차이 같은 문제가 이미지 뷰어를 혼란스럽게 만들고 있을 수 있습니다. 이를 디버깅하는 데 도움이 되도록, GitHub 프로젝트의 images 디렉터리에 test.ppm이라는 파일이 포함되어 있습니다. 이 파일을 통해 뷰어가 PPM 포맷을 올바르게 처리할 수 있는지 확인하고, 생성된 PPM 파일과 비교해볼 수 있습니다.

일부 사용자는 Windows 환경에서 생성된 PPM 파일이 열리지 않는 문제를 보고하기도 했습니다. 이 경우, 문제는 종종 PowerShell에서 출력된 파일이 UTF-16 인코딩으로 저장되었기 때문입니다. 이러한 문제가 발생한 경우, Discussion 1114 항목을 참고하시면 도움이 됩니다.

모든 것이 정상적으로 표시된다면, 시스템 및 IDE 관련 문제는 거의 해결된 것입니다. 이후 시리즈에서 다루는 모든 렌더링 이미지는 이와 동일한 간단한 방식으로 생성됩니다.

다른 이미지 포맷을 생성하고 싶으시다면, 저는 stb_image.h 라이브러리를 추천드립니다. 이 라이브러리는 GitHub에서 제공되는 헤더 전용 이미지 라이브러리이며, 주소는 다음과 같습니다: https://github.com/nothings/stb
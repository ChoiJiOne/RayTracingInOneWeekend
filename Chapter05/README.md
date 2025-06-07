# Chapter05. Adding a Sphere
- 구의 방정식
  - 중심이 원점일 경우: `x² + y² + z² = r²`
  - 중심이 C일 경우: `(P - C) · (P - C) = r²`
- 레이 `P(t) = Q + t·d`를 구에 대입하여 t에 대한 이차방정식 유도:
    ```CPP
    a = dot(d, d)
    b = -2 * dot(d, C - Q)
    c = dot(C - Q, C - Q) - r²
    ```
- 판별식(discriminant)이 0 이상이면 교차:
    ```CPP
    discriminant = b² - 4ac
    ```
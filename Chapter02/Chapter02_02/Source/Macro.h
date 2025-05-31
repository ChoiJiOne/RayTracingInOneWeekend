#pragma once

// [2025.05.31/최지원] NOTE: 복사 생성자 및 대입 연산자를 정의하지 않는 클래스는 반드시 이 매크로를 사용해야 함!
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)    \
TypeName(TypeName&&) = delete;                \
TypeName(const TypeName&) = delete;           \
TypeName& operator=(TypeName&&) = delete;     \
TypeName& operator=(const TypeName) = delete;
#endif
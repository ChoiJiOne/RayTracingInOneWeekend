#pragma once

// [2025.05.31/������] NOTE: ���� ������ �� ���� �����ڸ� �������� �ʴ� Ŭ������ �ݵ�� �� ��ũ�θ� ����ؾ� ��!
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)    \
TypeName(TypeName&&) = delete;                \
TypeName(const TypeName&) = delete;           \
TypeName& operator=(TypeName&&) = delete;     \
TypeName& operator=(const TypeName) = delete;
#endif

// C#�� nameof �����ڿ� ������ ����� �����ϴ� ��ũ��
#define NAMEOF(x) #x
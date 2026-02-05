#pragma once

#include "Math/Vector2.h"
#include <Windows.h>

namespace Wanted
{
	// ���� ���۸��� ����� Console output �ڵ��� �����ϴ� Ŭ����.
	class ScreenBuffer
	{
	public:
		ScreenBuffer(const Vector2& screenSize);
		~ScreenBuffer();

		// �ܼ� ���۸� ����� �Լ�.
		void Clear();

		// �ֿܼ� 2���� ���� �迭�� �׸� �� ����ϴ� �Լ�.
		void Draw(CHAR_INFO* charInfo);

		// ���� ��ȯ Getter.
		inline HANDLE GetBuffer() const { return buffer; }

	private:
		// �ܼ� ��� �ڵ�.
		HANDLE buffer = nullptr;

		// ȭ�� ũ��.
		Vector2 screenSize;


	};
}



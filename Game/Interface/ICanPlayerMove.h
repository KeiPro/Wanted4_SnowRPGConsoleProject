#pragma once

#include "Math/Vector2.h"

// �÷��̾ �̵��� ��ġ�� �Ǵ����ִ� �������̽�.
// C++ �������̽� = ���� �����Լ��� ������ Ŭ����.
class ICanPlayerMove
{
public:
	// �÷��̾ �̵��������� ������ �� ����� �Լ�.
	virtual bool CanMove(
		const Wanted::Vector2& playerPosition,
		const Wanted::Vector2& nextPosition
	) = 0;
};

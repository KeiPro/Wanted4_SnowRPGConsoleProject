#pragma once
#include "Actor/Actor.h"

using namespace Wanted;

class En_Wall : public Actor
{
	RTTI_DECLARATIONS(En_Wall, Actor)

public:
	// ��ġ ������ �����ϵ��� ������ ����.
	En_Wall(const Vector2& position);
};


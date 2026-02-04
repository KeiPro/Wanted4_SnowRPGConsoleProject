#pragma once
#include "Actor/Actor.h"

using namespace Wanted;

class En_Wall : public Actor
{
	RTTI_DECLARATIONS(En_Wall, Actor)

public:
	// 위치 지정이 가능하도록 생성자 선언.
	En_Wall(const Vector2& position);
};


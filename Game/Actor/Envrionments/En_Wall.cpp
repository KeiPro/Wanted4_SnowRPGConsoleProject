#include "En_Wall.h"

#include "Component/Collider/BoxCollider.h"
#include "Physics/CollisionSystem.h"

using namespace Wanted;

En_Wall::En_Wall(const Vector2& position)
	: super("#", position, Color::White)
{
	sortingOrder = 0;

	int left = position.x;
	int top = position.y;
	int right = left + GetWidth();
	int bottom = top + GetHeight();

	boxCollider = new BoxCollider(left, top, right, bottom);
	AddNewComponent(boxCollider);
	CollisionSystem::Get().Register(boxCollider);
}



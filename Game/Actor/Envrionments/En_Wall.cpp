#include "En_Wall.h"

En_Wall::En_Wall(const Vector2& position)
	: super("#", position, Color::White)
{
	// �׸��� �켱���� ����.
	sortingOrder = 0;
}

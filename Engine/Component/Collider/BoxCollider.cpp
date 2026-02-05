#include "BoxCollider.h"
#include "Actor/Actor.h"

using namespace Wanted;

BoxCollider::BoxCollider(int left, int top, int right, int bottom)
	: left(left), top(top), right(right), bottom(bottom)
{
	size = { right - left, bottom - top };
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Component::BeginPlay();
}

void BoxCollider::Tick(float deltaTime)
{
	SetPosition(GetOwner()->GetPosition().x, GetOwner()->GetPosition().y);
}

void BoxCollider::SetPosition(int left, int top)
{
	this->left = left;
	this->top = top;
	this->right = this->left + size.x;
	this->bottom = this->bottom + size.y;
}

void BoxCollider::NotifyCollision(const BoxCollider* const other)
{

}

bool BoxCollider::AABBCollision(const BoxCollider* const other)
{
	// AABB (Axis Aligned Bounding Box).
	int xMin = left; int xMax = right;
	int yMin = top; int yMax = bottom;

	int otherXMin = other->left; int otherXMax = other->right; 
	int otherYMin = other->top;  int otherYMax = other->bottom;

	if (otherXMin > xMax || otherXMax < xMin)
		return false;
	
	if (otherYMin > yMax || otherYMax < yMin)
		return false;

	return true;
}
#include "BoxCollider.h"
#include "Actor/Actor.h"
#include "Render/Renderer.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

BoxCollider::BoxCollider(int left, int top, int right, int bottom, int offsetX, int offsetY)
	: left(left), top(top), right(right), bottom(bottom)
{
	SetOffset(offsetX, offsetY);
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
	super::Tick(deltaTime);
}

void BoxCollider::Draw()
{
	if (debugMode)
	{
		for (int i = left; i < right; i++)
		{
			for (int j = top; j < bottom; j++)
			{
				Renderer::Get().Submit("C", Vector2(i, j), debugColor, 9999);
			}
		}
	}
}

void BoxCollider::SyncToOwner()
{
	this->left = (int)GetOwner()->GetPosition().x + offsetX;
	this->top = (int)GetOwner()->GetPosition().y + offsetY;
	this->right = this->left + size.x;
	this->bottom = this->top + size.y;
}

void BoxCollider::SetOffset(int offsetX, int offsetY)
{
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

bool BoxCollider::AABBCollision(const BoxCollider* const other)
{
	// AABB (Axis Aligned Bounding Box).
	int xMin = left; int xMax = right;
	int yMin = top; int yMax = bottom;

	int otherXMin = other->left; int otherXMax = other->right; 
	int otherYMin = other->top;  int otherYMax = other->bottom;

	if (otherXMin >= xMax || otherXMax <= xMin)
		return false;
	
	if (otherYMin >= yMax || otherYMax <= yMin)
		return false;

	return true;
}
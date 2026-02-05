#include "BoxCollider.h"
#include "Actor/Actor.h"

using namespace Wanted;

BoxCollider::BoxCollider(int left, int top, int size)
	: left(left), top(top), size(size)
{

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
	// 충돌 처리 진행.

	// 내가 지금 충돌하고 있다면, 누구와 충돌하고 있는가?
	
	// 내가 바닥에 대한 충돌 Collider라면, Owner에게 SetOnGround를 호출.
}

void BoxCollider::SetPosition(int left, int right)
{

}

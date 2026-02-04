#include "Actor.h"
#include "Render/Renderer.h"
#include "Util/Util.h"
#include "Engine/Engine.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Actor::Actor(const char* image, const Vector2& position, Color color)
		: position(position), color(color)
	{
		// 문자열 복사.
		size_t length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image, length, image);
	}

	Actor::~Actor()
	{
		SafeDeleteArray(this->image);
	}

	void Actor::BeginPlay()
	{
		// 이벤트를 받은 후에는 플래그 설정.
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{

	}

	void Actor::Draw()
	{
		//Renderer::Draw(position, color, image);

		// 렌더러에 데이터 제출.
		Renderer::Get().Submit(image, position, color, sortingOrder);
	}

	void Actor::Destroy()
	{
		destroyRequested = true;

		OnDestroy();
	}

	void Actor::OnDestroy()
	{

	}

	void Actor::QuitGame()
	{
		Engine::Get().QuitEngine();
	}

	bool Actor::TestIntersect(const Actor* const other)
	{
		// AABB(Axis Aligned Bounding Box).
		// x 좌표만 고려하면 됨. y는 크기가 1이기 때문.

		// 자기자신의 x좌표 정보.
		int xMin = position.x;
		int xMax = position.x + width - 1;

		// 충돌을 비교할 다른 액터의 x좌표 정보.
		int otherXMin = other->GetPosition().x;
		int otherXMax = other->GetPosition().x + other->GetWidth() - 1;

		// 안겹치는 조건 확인.
		if (otherXMin > xMax)
			return false;

		if (otherXMax < xMin)
			return false;

		// y는 크기가 1이기 때문에 좌표가 같은지 여부만 확인.
		return position.y == other->position.y;
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// renderer에 빈칸 그리기 요청.
		// Renderer::Draw(position, ' ');

		// 변경하려는 위치가 현재 위치와 가으면 건너뜀.
		if (position == newPosition)
			return;

		// 새로운 위치 설정.
		position = newPosition;
	}
}
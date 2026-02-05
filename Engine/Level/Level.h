#pragma once

#include "Common/RTTI.h"

// STL (Standard Template Library - C++���� �⺻ ����).
// ũ�Ⱑ �����ϴ� �迭.
#include <vector>

namespace Wanted
{
	// ���� ����
	class Actor;
	class CollisionSystem;
	// ��� �ӹ� : ������ �ִ� ��� ����(��ü) ����.
	class WANTED_API Level : public RTTI
	{
		RTTI_DECLARATIONS(Level, RTTI)

	public:
		Level();
		virtual ~Level();

		// ���� �÷��� �̺�Ʈ.
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// ���� �߰� �Լ�.
		void AddNewActor(Actor* newActor);

		// ���� �߰�/���� ó�� �Լ�.
		void ProcessAddAndDestroyActors();

	protected:
		// ���� �迭.
		std::vector<Actor*> actors;

		// ���� �߿� �߰� ��û�� ������ �迭.
		std::vector<Actor*> addRequestedActors;

	private:
		CollisionSystem* collisionSystem = nullptr;
	};
}

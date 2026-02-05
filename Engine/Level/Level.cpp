#include "Level.h"
#include "Actor/Actor.h"
#include "Physics/CollisionSystem.h"

namespace Wanted
{
	Level::Level()
	{
		collisionSystem = new CollisionSystem();
	}

	Level::~Level()
	{
		// �޸� ����.
		for (Actor* actor : actors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		// �迭 �ʱ�ȭ.
		actors.clear();

		delete collisionSystem;
		collisionSystem = nullptr;
	}

	void Level::BeginPlay()
	{
		// ���Ϳ� �̺�Ʈ �긮��.
		for (Actor* actor : actors)
		{
			if (actor->HasBeganPlay())
				continue;

			actor->BeginPlay();
		}

		collisionSystem->BeginPlay();
	}

	void Level::Tick(float deltaTime)
	{
		// ���Ϳ� �̺�Ʈ �긮��.
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}

		collisionSystem->Tick(deltaTime);
	}

	void Level::Draw()
	{
		// ���� ��ȸ�ϸ鼭 Draw�Լ� ȣ��.
		for (Actor* const actor : actors)
		{
			if (!actor->IsActive())
				continue;

			actor->Draw();
		}
	}

	void Level::AddNewActor(Actor* newActor)
	{
		// ���߿� �߰��� ���� �ӽ� �迭�� ����.
		addRequestedActors.emplace_back(newActor);

		// ���ʽ� ����.
		newActor->SetOwner(this);
	}

	void Level::ProcessAddAndDestroyActors()
	{
		collisionSystem->ProcessAddAndDestroyColliders();

		// ���� �迭���� ��Ÿ���߿� �ε����� ��ȭ�� �Ͼ ���ɼ��� �ִٸ�, �Ű����� ��.
		// ���� ó��
		for (int ix = 0; ix < static_cast<int>(actors.size()); )
		{
			// ���� ��û�� ���Ͱ� �ִ��� Ȯ��.
			if (actors[ix]->DestroyRequested())
			{
				// ���� ó��
				delete actors[ix];
				actors.erase(actors.begin() + ix); // actors.begin() + ix : ix�� ���ͷ����� : ix��° ������.
				continue;
			}

			++ix;
		}

		// �߰� ó��.
		if (addRequestedActors.size() == 0)
			return;

		for (Actor* const actor : addRequestedActors)
		{
			actors.emplace_back(actor);
		}

		addRequestedActors.clear();
	}
}
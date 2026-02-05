#pragma once

#include "Component/Component.h"

using namespace Wanted;

class BoxCollider : public Component
{
	RTTI_DECLARATIONS(BoxCollider ,Component)

public:

	BoxCollider(int left, int top, int size);
	~BoxCollider();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	void SetPosition(int left, int right);

private:

	int left;
	int top;
	int size = 1;
};


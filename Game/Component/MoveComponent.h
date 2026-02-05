#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"

using namespace Wanted;

class MoveComponent : public Component
{
	RTTI_DECLARATIONS(MoveComponent, Component)

public:

	MoveComponent();
	~MoveComponent();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:

	float moveSpeed = 30.0f;

	float jumpPower = 30.0f;
	Vector2 velocity = {0, 0};
	bool onGrounded = true;

	float physY = 0.0f;
};


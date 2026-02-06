#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"
#include "Common/RTTI.h"

namespace Wanted { class BoxCollider; }

using namespace Wanted;
class MoveComponent : public Component
{
	RTTI_DECLARATIONS(MoveComponent, Component)

public:

	MoveComponent();
	~MoveComponent();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	inline bool IsOnGrounded() const { return onGrounded; }
	void RequestOnGrounded(int floorY);
	inline void SetOnGrounded(bool grounded) { onGrounded = grounded; }

private:

	float moveSpeed = 30.0f;
	float jumpPower = 30.0f;
	Vector2 velocity = {0, 0};
	bool onGrounded = false;
	float physY = 0.0f;

	float elapsedTime = 0.0f;
	float lastGroundedTime = 0.0f;

	BoxCollider* floorBox = nullptr;
};
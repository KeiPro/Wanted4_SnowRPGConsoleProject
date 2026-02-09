#pragma once
class IDamageable
{
public:
	virtual void OnDamaged(int damage) = 0;
	virtual ~IDamageable() = default;
};
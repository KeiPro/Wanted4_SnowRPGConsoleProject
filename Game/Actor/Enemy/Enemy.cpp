#include "Enemy.h"
#include "Component/EnemyAI.h"
#include "Level/Level.h"

using namespace Wanted;

Enemy::Enemy(const char* image, const Vector2& position, Color color)
	: super(image, position, color)
{
	sortingOrder = 10;

	AddNewComponent(new EnemyAI());
}

Enemy::~Enemy()
{
}

void Enemy::BeginPlay()
{
	Actor::BeginPlay();
}

void Enemy::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	if (isDead)
		return;

	switch (state)
	{
	case Enemy::EnemyState::Idle:
		UpdateIdle(deltaTime);
		break;
	case Enemy::EnemyState::Chase:
		UpdateChase(deltaTime);
		break;
	case Enemy::EnemyState::Attack:
		UpdateAttack(deltaTime);
		break;
	case Enemy::EnemyState::Dead:
		Dead();
		break;
	default:
		break;
	}
}

void Enemy::Draw()
{
	if (state == EnemyState::Freeze)
		return;

	Actor::Draw();
}

void Enemy::UpdateIdle(float deltaTime)
{
	
}

void Enemy::UpdateChase(float deltaTime)
{

}

void Enemy::UpdateAttack(float deltaTime)
{

}

void Enemy::Dead()
{
	isDead = true;
	Destroy();
}

void Enemy::OnSnowballReleased(const Vector2& position)
{
	SetPosition(position);
	state = EnemyState::Idle;
}

void Enemy::OnDamaged(int damageType)
{
	if (damageType != (int)EDamageType::Dead)
	{
		state = EnemyState::Freeze;
		return;
	}

	state = EnemyState::Dead;
	Dead();
}



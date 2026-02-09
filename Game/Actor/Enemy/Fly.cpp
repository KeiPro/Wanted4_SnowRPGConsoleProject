#include "Fly.h"
#include "Util/Util.h"

using namespace Wanted;

Fly::Fly(const Vector2 position)
	: super("F", position, Color::Red)
{
}

Fly::~Fly()
{
}

void Fly::BeginPlay()
{
	Enemy::BeginPlay();
}

void Fly::Tick(float deltaTime)
{
	Enemy::Tick(deltaTime);
}

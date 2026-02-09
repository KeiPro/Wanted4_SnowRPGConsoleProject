#include "Snow.h"
#include "Actor/Enemy/Enemy.h"

using namespace Wanted;

static const Snow::FreezeEffect sequence[] =
{
	Snow::FreezeEffect(".", 1.0f, 2, Color::Blue),
	Snow::FreezeEffect(".", 1.0f, 2, Color::Blue),
	Snow::FreezeEffect("ㅇ", 1.0f, 3, Color::Blue),
	Snow::FreezeEffect("◎", 1.0f, 4, Color::Blue),
	Snow::FreezeEffect("㉧", 2.0f, 99999, Color::Blue),
};

Snow::Snow(const Vector2& position, Enemy* changedEnemy)
	: super(sequence[0].frame, position, Color::Blue), changedEnemy(changedEnemy)
{
	sortingOrder = 10;
	int effectFrameImageLength = 6;

	freezeEffectSequenceCount = sizeof(sequence) / sizeof(sequence[0]);
	timer.SetTargetTime(sequence[0].meltTime);
	hp = sequence[0].hp;
	color = sequence[0].color;
}

Snow::~Snow()
{
}

void Snow::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
		return;

	timer.Reset();
	
	--currentSequenceIndex;
	if (currentSequenceIndex < 0)
	{
		Destroy();
		changedEnemy->OnSnowballReleased(position);
		return;
	}

	timer.SetTargetTime(sequence[currentSequenceIndex].meltTime);
	ChangeImage(sequence[currentSequenceIndex].frame);
	hp = sequence[currentSequenceIndex].hp;
	color = sequence[currentSequenceIndex].color;
}

void Snow::OnDamaged(int damage)
{
	timer.Reset();

	hp -= damage;
	if (hp < 0)
		hp = 0;

	++currentSequenceIndex;
	if (currentSequenceIndex >= freezeEffectSequenceCount)
	{
		currentSequenceIndex = freezeEffectSequenceCount - 1;
		return;
	}

	timer.SetTargetTime(sequence[currentSequenceIndex].meltTime);
	ChangeImage(sequence[currentSequenceIndex].frame);
	hp = sequence[currentSequenceIndex].hp;
	color = sequence[currentSequenceIndex].color;
}

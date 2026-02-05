#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SnowRPGLevel : public Wanted::Level
{
	RTTI_DECLARATIONS(SnowRPGLevel, Level)

public:
	SnowRPGLevel();

	// �̺�Ʈ �Լ� �������̵�.
	virtual void Draw() override;

private:
	// ���ӿ��� ����� ���� �ε��ϴ� �Լ�.
	void LoadMap(const char* filename);

	// ���� Ŭ���� Ȯ�� �Լ�.
	bool CheckGameClear();

private:
	// ȹ���ؾ� �ϴ� ��ǥ ����.
	int targetScore = 0;

	// ���� Ŭ���� ���θ� �˷��ִ� ����.
	bool isGameClear = false;
};
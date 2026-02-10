#pragma once
class Timer
{
public:
	
	// Ÿ�̸� ���� �ð� �� ����.
	Timer(float targetTime = 1.0f);

	// Ÿ�̸� ������Ʈ �Լ�.
	void Tick(float dletaTime);

	// ����ð� ���� �Լ�.
	void Reset();

	// ������ �ð���ŭ �귶���� Ȯ���ϴ� �Լ�.
	bool IsTimeOut() const;

	// ��ǥ �ð� ���� �Լ�.
	void SetTargetTime(float newTargetTime);

private:
	// ����ð� Ȯ�ο� ����.
	float elapsedTime = 0.0f;

	// Ÿ�̸� ��ǥ �ð�.
	float targetTime = 0.0f;
};


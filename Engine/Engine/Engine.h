#pragma once

#include "Common/Common.h"

namespace Wanted
{
	// ���� ����.
	class Input;
	class Renderer;

	// Main game engine class.
	class WANTED_API Engine
	{
		// ���� ���� ����ü.
		struct EngineSetting
		{
			// ������ �ӵ�.
			float frameRate = 0.0f;

			// ȭ�� �ʺ�
			int width = 0;

			// ȭ�� ����
			int height = 0;
		};

	public:
		Engine();
		virtual ~Engine();

		// ���� ����(���� ����).
		void Run();

		// ���� �����Լ�.
		void QuitEngine();

		// �� ������ �߰�(����)�ϴ� �Լ�. 
		void SetNewLevel(class Level* newLevel);

		static Engine& Get();

	protected:

		// �����Լ�.
		void Shutdown();

		// ���� ���� �ε� �Լ�.
		void LoadSetting();

		// ���� �÷��� ���� �Լ�.
		// Unity�� ��� : Start / Awake.
		void BeginPlay();

		// ������Ʈ �Լ�.
		void Tick(float deltaTime);

		// �׸��� �Լ�(Draw / Render).
		void Draw();

	protected:
		// ���� ���� �÷���.
		bool isQuit = false;

		// ���� ���� ��.
		EngineSetting setting;

		// �Է� ������
		Input* input = nullptr;
		
		// ������ ��ü.
		Renderer* renderer = nullptr;

		// ���� ����
		class Level* mainLevel = nullptr;

		// ���� ����
		static Engine* instance;
	};
}


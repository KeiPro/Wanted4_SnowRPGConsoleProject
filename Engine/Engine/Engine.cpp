#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		instance = this;

		// �Է� ������ ����.
		input = new Input();

		// ���� ���� �ε�
		LoadSetting();

		// ������ ��ü ����.
		renderer = new Renderer(Vector2(setting.width, setting.height));

		Util::TurnOffCursor();
	}

	Engine::~Engine()
	{
		// ���� ���� ����.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		// �Է� ������ ����.
		if (input)
		{
			delete input;
			input = nullptr;
		}

		// ������ ��ü ����.
		SafeDelete(renderer);
	}

	void Engine::Run()
	{
		// �ð��� ���е� // 1�ʿ� �� �� ������ �� �ִ���.
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		// ������ ���� ����.
		//int64_t : stdint���� Ÿ�� ������ �� ��. �� �� �Ȱ���.
		//__int64 : ms�����Ϸ�. 
		int64_t currentTime = 0;
		int64_t previousTime = 0;

		// �ϵ���� Ÿ�̸ӷ� �ð� ���ϱ�.
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		// ���� ���� �������� �� �ð� ���� ���� ����.
		currentTime = time.QuadPart;
		previousTime = currentTime;

		// ���� ������(���� : ��)
		//float targetFrameRate = 120;
		setting.frameRate = setting.frameRate == 0.0f ? 60.0f : setting.frameRate;
		float oneFrameTime = 1.0f / setting.frameRate;

		// ���� ����(���� ����).
		while (!isQuit)
		{
			//timeGetTime() : 1000ms�ۿ� �������� ���ؼ� QueryPerformanceCounter�� ��ü.

			// ����ð� ���ϱ�. // �ϵ���� Ŭ��
			// intel x86 instruction set architecture pdf�� �ִ� �ϵ���� Ŭ�� Ȯ��.
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;

			// ������ �ð� ���.
			float deltaTime = static_cast<float>(currentTime - previousTime);

			// �ʴ��� ��ȯ
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			// ���� ������ ���.
			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();

				// ������ ó��.
				BeginPlay();
				Tick(deltaTime);
				Draw();

				// ���� �ð� �� ����.
				previousTime = currentTime;

				input->SavePreviousInputStates();

				// ������ ��û�� �߰�/���� ó��.
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
				}
			}
		}

		Shutdown();
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		// ���� ������ �ִ��� Ȯ��.
		// ������ ���� ���� ����
		// TODO : �ӽ� �ڵ�. ���� ��ȭ�� ���� �ٷ� �����ϸ� �ȵ�.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		// ���� ����
		mainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		// ����ó��
		if (!instance)
		{
			std::cout << "Error : Engine::Get(). instance is null\n";
			__debugbreak();
		}

		return *instance;
	}

	void Engine::Shutdown()
	{
		// ���� �۾�.
		std::cout << "Engine has been shutdown...\n";

		Util::TurnOnCursor();
	}

	void Engine::LoadSetting()
	{
		// ���� ���� ���� ����.
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt"); // read text
		if (file == nullptr)
		{
			std::cout << "Failed to open engine setting file.\n";
			__debugbreak();
			return;
		}

		char buffer[2048] = {};

		// ���Ͽ��� �б�.
		size_t readSize = fread(buffer, sizeof(char), 2048, file);

		// ���ڿ� �ڸ���(�Ľ�).
		// ù ��° ���ڿ� �и��� ���� ù �Ķ���� ����.
		char* context = nullptr;
		char* token = nullptr;
		token = strtok_s(buffer, "\n", &context);

		// �ݺ��ؼ� �ڸ���.
		while (token)
		{
			// ���� �ؽ�Ʈ���� �Ķ���� �̸��� �б�.
			char header[10] = {};


			// ���ڿ� �б� �Լ� Ȱ��.
			// �̶� "%s"�� ������ "�����̽��� ������ �ű���� ����."
			sscanf_s(token, "%s", header, 10);

			// ���ڿ� �� �� �� �б�.
			if (strcmp(header, "framerate") == 0)
			{
				sscanf_s(token, "framerate = %f", &setting.frameRate);
			}
			else if (strcmp(header, "width") == 0)
			{
				sscanf_s(token, "width = %d", &setting.width);
			}
			else if (strcmp(header, "height") == 0)
			{
				sscanf_s(token, "height = %d", &setting.height);
			}

			// ���� ���ڷ� ���ڿ� �и�.
			token = strtok_s(nullptr, "\n", &context);
		}

		fclose(file);
	}

	void Engine::BeginPlay()
	{
		// ������ ������ �̺�Ʈ ����.
		if (mainLevel == nullptr)
		{
			// Silent is violent
			// ħ���� �����̴�.
			// -> �α� �޽����� ���ܶ�.
			std::cout << "mainLevel is empty.\n";
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		//std::cout 
		//	<< "DeltaTime : " << deltaTime
		//	<< ", FPS : " << (1.0f / deltaTime) << "\n";

		// ������ �̺�Ʈ �ø���.
		// ����ó��
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Tick(). mainLevel is empty. \n";
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Draw(). mainLevel is empty. \n";
			return;
		}

		// ������ ��� ���Ͱ� ���� �����͸� ����.
		mainLevel->Draw();

		// �������� �׸��� ��� ����.
		renderer->Draw();
	}

}

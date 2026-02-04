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

		// 입력 관리자 생성.
		input = new Input();

		// 설정 파일 로드
		LoadSetting();

		// 렌더러 객체 생성.
		renderer = new Renderer(Vector2(setting.width, setting.height));

		Util::TurnOffCursor();
	}

	Engine::~Engine()
	{
		// 메인 레벨 제거.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		// 입력 관리자 제거.
		if (input)
		{
			delete input;
			input = nullptr;
		}

		// 렌더러 객체 제거.
		SafeDelete(renderer);
	}

	void Engine::Run()
	{
		// 시계의 정밀도 // 1초에 몇 번 진동할 수 있는지.
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		// 프레임 계산용 변수.
		//int64_t : stdint에서 타입 재정의 된 것. 둘 다 똑같다.
		//__int64 : ms컴파일러. 
		int64_t currentTime = 0;
		int64_t previousTime = 0;

		// 하드웨어 타이머로 시간 구하기.
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		// 엔진 시작 직전에는 두 시간 값을 같게 맞춤.
		currentTime = time.QuadPart;
		previousTime = currentTime;

		// 기준 프레임(단위 : 초)
		//float targetFrameRate = 120;
		setting.frameRate = setting.frameRate == 0.0f ? 60.0f : setting.frameRate;
		float oneFrameTime = 1.0f / setting.frameRate;

		// 엔진 루프(게임 루프).
		while (!isQuit)
		{
			//timeGetTime() : 1000ms밖에 측정하지 못해서 QueryPerformanceCounter로 대체.

			// 현재시간 구하기. // 하드웨어 클락
			// intel x86 instruction set architecture pdf에 있는 하드웨어 클락 확인.
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;

			// 프레임 시간 계산.
			float deltaTime = static_cast<float>(currentTime - previousTime);

			// 초단위 변환
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			// 고정 프레임 기법.
			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();

				// 프레임 처리.
				BeginPlay();
				Tick(deltaTime);
				Draw();

				// 이전 시간 값 갱신.
				previousTime = currentTime;

				input->SavePreviousInputStates();

				// 레벨에 요청된 추가/제거 처리.
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
		// 기존 레벨에 있는지 확인.
		// 있으면 기존 레벨 제거
		// TODO : 임시 코드. 레벨 전화할 때는 바로 제거하면 안됨.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		// 레벨 설정
		mainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		// 예외처리
		if (!instance)
		{
			std::cout << "Error : Engine::Get(). instance is null\n";
			__debugbreak();
		}

		return *instance;
	}

	void Engine::Shutdown()
	{
		// 정리 작업.
		std::cout << "Engine has been shutdown...\n";

		Util::TurnOnCursor();
	}

	void Engine::LoadSetting()
	{
		// 엔진 설정 파일 열기.
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt"); // read text
		if (file == nullptr)
		{
			std::cout << "Failed to open engine setting file.\n";
			__debugbreak();
			return;
		}

		char buffer[2048] = {};

		// 파일에서 읽기.
		size_t readSize = fread(buffer, sizeof(char), 2048, file);

		// 문자열 자르기(파싱).
		// 첫 번째 문자열 분리할 때는 첫 파라미터 전달.
		char* context = nullptr;
		char* token = nullptr;
		token = strtok_s(buffer, "\n", &context);

		// 반복해서 자르기.
		while (token)
		{
			// 설정 텍스트에서 파라미터 이름만 읽기.
			char header[10] = {};


			// 문자열 읽기 함수 활용.
			// 이때 "%s"로 읽으면 "스페이스가 있으면 거기까지 읽음."
			sscanf_s(token, "%s", header, 10);

			// 문자열 비교 및 값 읽기.
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

			// 개행 문자로 문자열 분리.
			token = strtok_s(nullptr, "\n", &context);
		}

		fclose(file);
	}

	void Engine::BeginPlay()
	{
		// 레벨이 있으면 이벤트 전달.
		if (mainLevel == nullptr)
		{
			// Silent is violent
			// 침묵은 폭력이다.
			// -> 로그 메시지는 남겨라.
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

		// 레벨에 이벤트 플리기.
		// 예외처리
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

		// 레벨의 모든 액터가 렌더 데이터를 제출.
		mainLevel->Draw();

		// 렌더러에 그리기 명령 전달.
		renderer->Draw();
	}

}

#include "Input.h"
#include <Windows.h>
#include <iostream>

// Ctrl + HomeŰ�� ���� ���� ���� ����.
namespace Wanted
{
	// ���� ���� �ʱ�ȭ.
	// ������ ������ �ö�.
	Input* Input::instance = nullptr;

	Input::Input()
	{
		// ��ü�� �ʱ�ȭ�Ǹ� �ڱ� �ڽ��� �ּҸ� ����.
		instance = this;
	}

	Input::~Input()
	{
	}

	bool Input::GetKeyDown(int keyCode)
	{
		return keyStates[keyCode].isKeyDown &&
			!keyStates[keyCode].wasKeyDown;
	}

	bool Input::GetKeyUp(int keyCode)
	{
		return keyStates[keyCode].wasKeyDown &&
			!keyStates[keyCode].isKeyDown;
	}

	bool Input::GetKey(int keyCode)
	{
		return keyStates[keyCode].isKeyDown;
	}

	Input& Input::Get()
	{
		// �̱���(Singleton)
		// �� �Լ��� ������ ������Ʈ���� ������.
		// ���� ������ �̹� �ʱ�ȭ �Ϸ� ����.
		if (!instance)
		{
			std::cout << "Error: Input::Get(). instance is null\n";

			// ����� ��忡���� ������.
			// �ڵ����� �ߴ��� �ɸ�.
			__debugbreak();
		}

		// Lazy-pattern.
		// ������ �̸� ���ϰ� ȣ���ϴ� ������ ����.
		// ����Ƽ�� C++�� ����.
		//static Input instance;
		return *instance;
	}

	void Input::ProcessInput()
	{
		// Ű ������ �Է� �б�.
		// !!! �ü���� �����ϴ� ����� ����� �� �ۿ� ����.
		for (int key = 0; key < 255; key++)
		{
			keyStates[key].isKeyDown = (GetAsyncKeyState(key) & 0x8000) > 0 ? true : false;
		}
	}

	void Input::SavePreviousInputStates()
	{
		// ���� �Է� ���� ���� �Է� ������ ����.
		for (int key = 0; key < 255; key++)
		{
			keyStates[key].wasKeyDown = keyStates[key].isKeyDown;
		}
	}
}

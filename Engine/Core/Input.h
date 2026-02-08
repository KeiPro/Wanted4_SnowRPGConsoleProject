#pragma once

#include "Common/Common.h"

namespace Wanted
{
	class WANTED_API Input
	{
		friend class Engine;

		// ������
		// Down/Up/Key
		struct KeyState
		{
			// ���� Ű�� ���ȴ���.
			bool isKeyDown = false;

			//  ������ Ű�� ���ȴ���.
			bool wasKeyDown = false;
		};

	private:
		Input();
		~Input();

	public:
		// �Է� Ȯ�� �Լ�.
		// ������ �Է¾� �ȵƴµ�, ���� �Է��� ������ 1�� ȣ��.
		bool GetKeyDown(int keyCode);

		// ������ �Է��� �ƴµ�, ���� �Է��� ��ҵ����� 1�� ȣ��.
		bool GetKeyUp(int keyCode);

		// ���� ���������� �ݺ� ȣ��.
		bool GetKey(int keyCode);

		// ���������� �����ϴ� �Լ�.
		static Input& Get();


	private:

		// �Է� ó�� �Լ�.
		void ProcessInput();

		// ���� �Է� ���� �Լ�.
		void SavePreviousInputStates();

	private:
		// Ű ���� ����� �迭.
		KeyState keyStates[255] = { };

		// ���������� �����ϵ��� ����� ���� ���� ����.
		static Input* instance;
	};

}


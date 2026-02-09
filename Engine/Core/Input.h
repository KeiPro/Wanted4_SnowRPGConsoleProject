#pragma once

#include "Common/Common.h"

namespace Wanted
{
	class WANTED_API Input
	{
		friend class Engine;

		// Down/Up/Key
		struct KeyState
		{
			bool isKeyDown = false;

			bool wasKeyDown = false;
		};

	private:
		Input();
		~Input();

	public:
		bool GetKeyDown(int keyCode);

		bool GetKeyUp(int keyCode);

		bool GetKey(int keyCode);

		static Input& Get();


	private:

		void ProcessInput();

		void SavePreviousInputStates();

	private:
		KeyState keyStates[255] = { };

		static Input* instance;
	};

}


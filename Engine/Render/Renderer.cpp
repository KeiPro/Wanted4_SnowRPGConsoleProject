#include "Util/Util.h"
#include "Renderer.h"
#include "ScreenBuffer.h"

namespace Wanted
{
	Renderer::Frame::Frame(int bufferCount)
	{
		charInfoArray = new CHAR_INFO[bufferCount];
		memset(charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);

		sortingOrderArray = new int[bufferCount];
		memset(sortingOrderArray, 0, sizeof(int) * bufferCount);
	}

	Renderer::Frame::~Frame()
	{
		SafeDeleteArray(charInfoArray);
		SafeDeleteArray(sortingOrderArray);
	}

	void Renderer::Frame::Clear(const Vector2 screenSize)
	{
		const int width = static_cast<int>(screenSize.x);
		const int height = static_cast<int>(screenSize.y);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				const int index = (y * width) + x;

				CHAR_INFO& info = charInfoArray[index];
				info.Char.AsciiChar = ' ';
				info.Attributes = 0;

				sortingOrderArray[index] = -1;
			}
		}
	}

	// -------------------------Frame------------------------------//

	Renderer* Renderer::instance = nullptr;


	ScreenBuffer* Renderer::GetCurrentBuffer()
	{
		return screenBuffers[currentBufferIndex];
	}

	Renderer::Renderer(const Vector2& screenSize)
		: screenSize(screenSize)
	{
		instance = this;

		const int bufferCount = static_cast<int>(screenSize.x * screenSize.y);
		frame = new Frame(bufferCount);

		frame->Clear(screenSize);

		screenBuffers[0] = new ScreenBuffer(screenSize);
		screenBuffers[0]->Clear();

		screenBuffers[1] = new ScreenBuffer(screenSize);
		screenBuffers[1]->Clear();

		Present();
	}

	Renderer::~Renderer()
	{
		SafeDelete(frame);
		for (ScreenBuffer*& buffer : screenBuffers)
		{
			SafeDelete(buffer);
		}
	}

	Renderer& Renderer::Get()
	{
		if (!instance)
		{
			MessageBoxA(nullptr, "Renderer::Get() - instance is null", "Error", MB_OK);
			__debugbreak();
		}

		return *instance;
	}

	void Renderer::Draw()
	{
		Clear();

		for (const RenderCommand& command : renderQueue)
		{
			if (!command.text)
				continue;

			if (command.position.y < 0 || command.position.y >= screenSize.y)
				continue;

			const int length = static_cast<int>(strlen(command.text));

			if (length <= 0)
			{
				continue;
			}

			const int startX = static_cast<int>(command.position.x);
			const int endX = static_cast<int>(command.position.x) + length - 1;

			if (endX < 0 || startX >= static_cast<int>(screenSize.x))
			{
				continue;
			}

			const int visibleStart = startX < 0 ? 0 : startX;
			const int visibleEnd = endX >= static_cast<int>(screenSize.x) ? static_cast<int>(screenSize.x) - 1 : endX;

			for (int x = visibleStart; x <= visibleEnd; x++)
			{
				const int sourceIndex = x - startX;

				const int index = (command.position.y * screenSize.x) + x;

				if (frame->sortingOrderArray[index] > command.sortingOrder)
					continue;

				frame->charInfoArray[index].Char.AsciiChar = command.text[sourceIndex];
				frame->charInfoArray[index].Attributes = (WORD)command.color;

				frame->sortingOrderArray[index] = command.sortingOrder;
			}
		}

		GetCurrentBuffer()->Draw(frame->charInfoArray);

		Present();

		renderQueue.clear();
	}

	void Renderer::Clear()
	{
		frame->Clear(screenSize);

		GetCurrentBuffer()->Clear();
	}

	void Renderer::Present()
	{
		SetConsoleActiveScreenBuffer(GetCurrentBuffer()->GetBuffer());

		currentBufferIndex = 1 - currentBufferIndex;
	}


	void Renderer::Submit(const char* text, const Vector2& position, Color color, int sortingOrder)
	{
		RenderCommand command = {};
		command.text = text;
		command.position = position;
		command.color = color;
		command.sortingOrder = sortingOrder;

		renderQueue.emplace_back(std::move(command));
	}
}
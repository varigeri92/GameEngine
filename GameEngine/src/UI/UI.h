#pragma once
#include "Window.h"
namespace core::ui
{
	class UI 
	{
	public:
		void InitGUI(Window* window);
		void OnFrameStart();
		void DrawGUI();
		void CleanUpGui();

	private:
		Window* window;

		bool someBoolean;
		float speed;
	};
}
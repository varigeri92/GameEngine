#pragma once
#include <SDL.h>

class Window
{
public:
	Window(int _width, int _height);
	~Window();

	int InitWindow();
	int CreateContext();

	SDL_Window* GetWindow() { return m_window; };
	SDL_GLContext& GetContext() { return glContext; };

	void WindowEvent(const SDL_Event* event);
	int width, height;
private:

	SDL_Window* m_window;
	SDL_GLContext glContext;
};


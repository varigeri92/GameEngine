#include "Window.h"
#include <SDL.h>
#include "Log.h"

Window::Window(int _width, int _height) : width{ _width }, height{ _height }{}

int Window::InitWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	m_window = SDL_CreateWindow(
		"Game Engine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		window_flags
	);

	if (m_window == NULL) return 1;
	return 0;
}

int Window::CreateContext()
{
	glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr) {
		LOG_ERROR("SDL_GL context could not be created!");
	}
	return 0;
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
}

void Window::WindowEvent(const SDL_Event* event)
{
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            break;
        case SDL_WINDOWEVENT_MOVED:
            break;
        case SDL_WINDOWEVENT_RESIZED:
            width = event->window.data1;
            height = event->window.data2;
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            width = event->window.data1;
            height = event->window.data2;
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            break;
        case SDL_WINDOWEVENT_RESTORED:
            break;
        case SDL_WINDOWEVENT_ENTER:
            break;
        case SDL_WINDOWEVENT_LEAVE:
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            break;
        case SDL_WINDOWEVENT_CLOSE:
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            break;
#endif
        default:

            break;
        }
    }
}
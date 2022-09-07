#pragma once

#ifdef BUILD_DLL
#define _API __declspec(dllexport)
#else
#define _API __declspec(dllimport)
#endif

class Engine
{
public:
	_API Engine(int _width, int _height);
	_API void LogMessage(const char* msg);
	_API int InitEngine();
	_API int Run();

private:
	int width, height;
};

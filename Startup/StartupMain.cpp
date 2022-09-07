#include <iostream>
#include "../GameEngine/API/Engine.h"
#include "../GameEngine/API/Log.h"

#include <filesystem>

int main(int argc, char* argv[])
{
	int error = 0;
	Engine* engine = new Engine(1920, 1080);
	engine -> LogMessage("Hello from the engine dll! abc-dfg");
	error = engine->InitEngine();
	if (error != 0) return error;
	return engine->Run();
}
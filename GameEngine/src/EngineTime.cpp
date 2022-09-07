#include "EngineTime.h"

void core::Time::StartFrameTimer()
{
	m_startTime = std::chrono::high_resolution_clock::now();
}

void core::Time::EndFrameTimer()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	m_deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - m_startTime).count();
}

#pragma once
#include "Engine.h"
#include <chrono>

namespace core
{
	class Time
	{
	public:
		static float GetDelta() { return m_deltaTime; };

	private:

		static void StartFrameTimer();
		static void EndFrameTimer();
	
		inline static std::chrono::steady_clock::time_point m_startTime;
		inline static float m_deltaTime;
		inline static float m_timeScale1;
	
		friend class Engine;
	};

}


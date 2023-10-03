#pragma once
#include <chrono>

namespace nc
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() : 
			m_startTime{ clock::now() },
			m_frameTime{ clock::now() }
		{}

		void Tick();
		void Reset() { m_startTime = clock::now(); }

		clock::rep GetElapsedNanoseconds();
		clock::rep GetElapsedMicroseconds();
		clock::rep GetElapsedMilliseconds();
		float GetElapsedSeconds();

		float GetTime() const { return m_time; }
		float GetDeltaTime() const { return m_deltaTime * m_timeScale; }
		float GetUnscaledDeltaTime() const { return m_deltaTime; }

		float GetTimeScale() const { return m_timeScale; }
		void SetTimeScale(float timeScale) { m_timeScale = timeScale; }

	private:
		float m_time = 0;
		float m_deltaTime = 0;
		float m_timeScale = 1;

		clock::time_point m_startTime;
		clock::time_point m_frameTime;
	};
}
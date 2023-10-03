#include "Time.h"
#include "Math/MathUtils.h"

namespace nc
{
	void Time::Tick()
	{
		clock::duration duration = clock::now() - m_startTime;
		m_time = duration.count() / static_cast<float>(clock::duration::period::den);

		duration = clock::now() - m_frameTime;
		m_deltaTime = duration.count() / static_cast<float>(clock::duration::period::den);
		m_deltaTime = Min(m_deltaTime, 0.25f);

		m_frameTime = clock::now();
	}

	Time::clock::rep Time::GetElapsedNanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_startTime).count();
	}

	Time::clock::rep Time::GetElapsedMicroseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_startTime).count();
	}

	Time::clock::rep Time::GetElapsedMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_startTime).count();
	}

	float Time::GetElapsedSeconds()
	{
		return (clock::now() - m_startTime).count() / static_cast<float>(clock::duration::period::den);
	}
}


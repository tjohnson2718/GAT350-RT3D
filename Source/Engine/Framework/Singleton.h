#pragma once

namespace nc
{
	// Design pattern to ensure there is only one instance of an object and accessed through static method Instance().
	// https://en.wikipedia.org/wiki/Singleton_pattern
	template <typename T>
	class Singleton
	{
	public:
		Singleton(const Singleton& other) = delete;
		Singleton& operator = (const Singleton& other) = delete;

		static T& Instance()
		{
			static T instance;
			return instance;
		}

	protected:
		Singleton() = default;
	};
}
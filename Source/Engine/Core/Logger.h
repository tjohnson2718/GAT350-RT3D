#pragma once
#include "Framework/Singleton.h"
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
// if Debug Configuration, log messages
#define INFO_LOG(message)		{ if (nc::Logger::Instance().Log(nc::LogLevel::Info, __FILE__, __LINE__))		{ nc::Logger::Instance() << message << "\n"; } }
#define WARNING_LOG(message)	{ if (nc::Logger::Instance().Log(nc::LogLevel::Warning, __FILE__, __LINE__))	{ nc::Logger::Instance() << message << "\n"; } }
#define ERROR_LOG(message)		{ if (nc::Logger::Instance().Log(nc::LogLevel::Error, __FILE__, __LINE__))		{ nc::Logger::Instance() << message << "\n"; } }
#define ASSERT_LOG(condition, message) { if (!condition && nc::Logger::Instance().Log(nc::LogLevel::Assert, __FILE__, __LINE__)) { nc::Logger::Instance() << message << "\n"; } assert(condition); }
#else
// if not Debug Configuration, don't log messages
#define INFO_LOG(message)		{}
#define WARNING_LOG(message)	{}
#define ERROR_LOG(message)		{}
#define ASSERT_LOG(condition, message)		{}
#endif // _DEBUG

namespace nc
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	// Logs streams of data into the console and/or file
	class Logger : public Singleton<Logger>
	{
	public:
		Logger(LogLevel logLevel = LogLevel::Info, std::ostream* ostream = &std::cout, const std::string& filename = "log.txt") :
			m_logLevel{ logLevel },
			m_ostream{ ostream } 
		{
			if (!filename.empty()) m_fstream.open(filename);
		}

		bool Log(LogLevel logLevel, const std::string& filename, int line);

		// Stream operator overload to stream data into logger.
		template<typename T>
		Logger& operator << (T value);

	private:
		LogLevel m_logLevel; // Log(logLevel) needs to be higher than current m_logLevel to log
		std::ostream* m_ostream = nullptr; // console stream
		std::ofstream m_fstream; // file stream
	};

	template<typename T>
	inline Logger& Logger::operator << (T value)
	{
		// stream to console
		if (m_ostream) *m_ostream << value;
		// stream to file
		if (m_fstream.is_open())
		{
			m_fstream << value;
			m_fstream.flush();
		}

		return *this;
	}
}
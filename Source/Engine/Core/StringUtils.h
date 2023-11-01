#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		static std::string ToUpperCase(const std::string& str);
		static std::string ToLowerCase(const std::string& str);
		static bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);
		static std::string CreateUnique(const std::string& str);
		static std::string Reverse(const std::string& str, int index = 0);
		
	private:
		static unsigned int uniqueCounter;
	};
}
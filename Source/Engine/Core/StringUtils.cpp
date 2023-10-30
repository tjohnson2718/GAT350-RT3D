#include "StringUtils.h"
#include <cctype>

namespace nc
{
	unsigned int StringUtils::uniqueCounter = 0;

	std::string StringUtils::ToUpperCase(const std::string& str)
	{
		std::string result = str;
		for (char& c : result)
		{
			c = std::toupper(c);
		}
		return result;
	}

	std::string StringUtils::ToLowerCase(const std::string& str)
	{
		std::string result = str;
		for (char& c : result)
		{
			c = std::tolower(c);
		}
		return result;
	}

	bool StringUtils::IsEqualIgnoreUpperCase(const std::string& str1, const std::string& str2)
	{
		return ToLowerCase(str1) == ToLowerCase(str2);
	}

	std::string StringUtils::CreateUnique(const std::string& str)
	{
		std::string uniqueString = str + std::to_string(uniqueCounter);
		uniqueCounter++;

		return uniqueString;
	}

	std::string StringUtils::Reverse(const std::string& str, int index)
	{
		if (index == str.length())
		{
			return "";
		}
		else
		{
			return Reverse(str, index + 1) + str[index];
		}
	}
}
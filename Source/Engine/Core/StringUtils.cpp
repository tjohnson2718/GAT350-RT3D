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

	bool StringUtils::IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
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

	int StringUtils::GetTrailingNumber(const std::string& str)
	{
		// if the string is empty return -1
		if (str.empty()) return -1;

		// check from the end of the string for characters that are digits, add digit to strNumber
		// if character is not digit, then exit
		std::string strNumber;
		for (size_t i = str.size() - 1; i >= 0; i--)
		{
			if (std::isdigit(str[i])) strNumber = str[i] + strNumber;
			else break;
		}

		// convert strNumber to a number if not empty
		return (!strNumber.empty()) ? std::stoi(strNumber) : -1;
	}

	std::string StringUtils::RemoveTrailingNumber(const std::string& str)
	{
		if (str.empty()) return "";

		// set result string to str parameter
		// start at the end of the string and remove any characters that are digits
		// if character is not a digit, then exit
		std::string result = str;
		for (size_t i = str.size() - 1; i >= 0; i--)
		{
			if (std::isdigit(str[i])) result.pop_back();
			else break;
		}

		// return string without trailing number
		return result;
	}
}
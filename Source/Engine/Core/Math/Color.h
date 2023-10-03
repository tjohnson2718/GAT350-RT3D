#pragma once
#include "MathUtils.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace nc
{
	class Color
	{
	public:
		float r, g, b, a;

	public:
		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {}
		Color(float r, float g, float b, float a = 1) : r{ r }, g{ g }, b{ b }, a{ a } {}

		float  operator [] (size_t index) const { return (&r)[index]; }
		float& operator [] (size_t index) { return (&r)[index]; }

		static uint8_t ToInt(float c) { return static_cast<uint8_t>(Clamp(c, 0.0f, 1.0f) * 255); }
	};

	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		// line = { ##, ##, ## }
		// red
		std::string str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		color.r = std::stof(str);

		line = line.substr(line.find(",") + 1);

		// green
		str = line.substr(0, line.find(","));
		color.g = std::stof(str);

		// blue
		str = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
		color.b = std::stof(str);

		// alpha
		color.a = 1;

		return stream;
	}
}
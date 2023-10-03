#pragma once

namespace nc
{
	class Rect
	{
	public:
		int x, y, w, h;

	public:
		Rect() : x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 } {}
		Rect(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}

		int  operator [] (size_t index) const { return (&x)[index]; }
		int& operator [] (size_t index) { return (&x)[index]; }
	};
}

#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace nc
{
	class Matrix33
	{
	public:
		vec3 rows[3];
		// [row][column]
		// rows[0] = vec3{ 0, 0, 0 }
		// rows[1] = vec3{ 0, 0, 0 }
		// rows[2] = vec3{ 0, 0, 0 }

		Matrix33() = default;
		Matrix33(const vec3& row1, const vec3& row2, const vec3& row3)
		{
			rows[0] = row1;
			rows[1] = row2;
			rows[2] = row3;
		}

		vec3  operator [] (size_t index) const { return rows[index]; }
		vec3& operator [] (size_t index) { return rows[index]; }

		vec2 operator * (const vec2& v);
		Matrix33 operator * (const Matrix33& mx);

		static Matrix33 CreateTranslation(const vec2& translate);
		static Matrix33 CreateScale(const vec2& scale);
		static Matrix33 CreateScale(float scale);
		static Matrix33 CreateRotation(float radians);
		static Matrix33 CreateIdentity();

		vec2  GetTranslation() const;
		float GetRotation() const;
		vec2  GetScale() const;

	};

	inline vec2 Matrix33::operator*(const vec2& v)
	{
		// | 00 01 02 |   | x |
		// | 10 11 12 | * | y |
		// | 20 21 22 |   | 1 |

		vec2 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y + rows[0][2];
		result.y = rows[1][0] * v.x + rows[1][1] * v.y + rows[1][2];

		return result;
	}

	inline Matrix33 Matrix33::operator*(const Matrix33& mx)
	{
		// | 00 01 02 |   | 00 01 02 |
		// | 10 11 12 | * | 10 11 12 |
		// | 20 21 22 |   | 20 21 22 |

		Matrix33 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0] + rows[0][2] * mx[2][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1] + rows[0][2] * mx[2][1];
		result[0][2] = rows[0][0] * mx[0][2] + rows[0][1] * mx[1][2] + rows[0][2] * mx[2][2];

		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0] + rows[1][2] * mx[2][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1] + rows[1][2] * mx[2][1];
		result[1][2] = rows[1][0] * mx[0][2] + rows[1][1] * mx[1][2] + rows[1][2] * mx[2][2];

		result[2][0] = rows[2][0] * mx[0][0] + rows[2][1] * mx[1][0] + rows[2][2] * mx[2][0];
		result[2][1] = rows[2][0] * mx[0][1] + rows[2][1] * mx[1][1] + rows[2][2] * mx[2][1];
		result[2][2] = rows[2][0] * mx[0][2] + rows[2][1] * mx[1][2] + rows[2][2] * mx[2][2];

		return result;
	}

	inline Matrix33 Matrix33::CreateIdentity()
	{
		return
		{
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
		};
	}

	inline Matrix33 Matrix33::CreateScale(const vec2& scale)
	{
		// | sx 0 0 |
		// | 0 sy 0 |
		// | 0  0 1 |
		Matrix33 mx = CreateIdentity();
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix33 Matrix33::CreateScale(float scale)
	{
		// | s 0 0 |
		// | 0 s 0 |
		// | 0 0 1 |
		Matrix33 mx = CreateIdentity();
		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix33 Matrix33::CreateRotation(float radians)
	{
		// | c -s 0 |
		// | s  c 0 |
		// | 0  0 1 |
		Matrix33 mx = CreateIdentity();
		float c = cos(radians);
		float s = sin(radians);

		mx[0][0] = c; mx[0][1] = -s;
		mx[1][0] = s; mx[1][1] =  c;

		return mx;
	}

	inline Matrix33 Matrix33::CreateTranslation(const vec2& translate)
	{
		// | 1 0 x |
		// | 0 1 y |
		// | 0 0 1 |
		Matrix33 mx = CreateIdentity();
		mx[0][2] = translate.x;
		mx[1][2] = translate.y;

		return mx;
	}

	inline vec2 Matrix33::GetTranslation() const
	{
		// 1 0 x
		// 0 1 y
		// 0 0 1

		return { rows[0][2], rows[1][2] };
	}

	inline float Matrix33::GetRotation() const
	{
		// cos -sin 0
		// sin  cos 0
		//  0    0  1

		// y = sin(angle) = rows[1][0]
		// x = cos(angle) = rows[0][0]

		return std::atan2(rows[1][0], rows[0][0]);
	}

	inline vec2  Matrix33::GetScale() const
	{
		// vx = cos + -sin
		// vy = sin +  cos
		// x  = vx length
		// y  = vy length

		vec2 x = { rows[0][0], rows[0][1] };
		vec2 y = { rows[1][0], rows[1][1] };

		return { x.Length(), y.Length() };
	}

	using mat3 = Matrix33;
}
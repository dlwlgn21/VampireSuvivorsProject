#pragma once
#include <math.h>

#define PI (3.141592)

namespace ya
{	

	struct Vector2
	{
		float x;
		float y;

		static Vector2 ZERO;
		static Vector2 ONE;
		static Vector2 RIGHT;
		static Vector2 LEFT;
		static Vector2 UP;
		static Vector2 DOWN;
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2() = default;
		~Vector2() = default;
		Vector2(const Vector2& other) = default;

		Vector2 operator/(const float val)
		{
			Vector2 temp;
			temp.x = x / val;
			temp.y = y / val;
			return temp;
		}

		Vector2 operator+(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}
		Vector2 operator-(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}
		Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		float GetLength()
		{
			return sqrt((x * x) + (y * y));
		}

		Vector2& Normalize()
		{
			float lenth = GetLength();
			x /= lenth;
			y /= lenth;
			return *this;
		}
	};

	namespace yamath
	{
		__forceinline float DegreeToRad(float degree)
		{
			return static_cast<float>(degree * PI / 180.0f);
		}

		__forceinline float RadToDegree(float rad)
		{
			return static_cast<float>(rad * 180.0f / PI);
		}

		inline Vector2 Rotate(const Vector2 input, float degree)
		{
			Vector2 ret = Vector2::ZERO;
			float rad = DegreeToRad(degree);
			ret.x = input.x * cosf(rad) - input.y * sinf(rad);
			ret.y = input.x * sinf(rad) + input.y * cosf(rad);
			return ret;
		}
	}

}
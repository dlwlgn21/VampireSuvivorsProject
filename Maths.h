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
		void Clear()
		{
			x = 0.0f;
			y = 0.0f;
		}
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

		Vector2 operator*(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x * other.x;
			temp.y = y * other.y;
			return temp;
		}

		Vector2 operator*(const float val)
		{
			Vector2 temp;
			temp.x = x * val;
			temp.y = y * val;
			return temp;
		}

		Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Vector2& operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vector2& operator*=(const Vector2& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		Vector2& operator*=(const float val)
		{
			x *= val;
			y *= val;
			return *this;
		}

		bool operator==(const Vector2& other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vector2& other)
		{
			return x != other.x && y != other.y;
		}

		Vector2 operator-()
		{
			return Vector2(-x, -y);
		}

		float GetLength()
		{
			return static_cast<float>(sqrt((x * x) + (y * y)));
		}

		Vector2& Normalize()
		{
			float lenth = GetLength();
			x /= lenth;
			y /= lenth;
			return *this;
		}

		float Dot(const Vector2& other)
		{
			return (x * other.x) + (y * other.y);
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

		__forceinline float Dot(const Vector2& v1, const Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
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
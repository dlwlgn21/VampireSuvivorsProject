#pragma once
#include <math.h>

#define PI (3.141592f)

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
		Vector2(float paramX, float paramY)
			: x(paramX)
			, y(paramY)
		{
		}

		Vector2() = default;
		~Vector2() = default;
		Vector2(const Vector2& other) = default;

		__forceinline void Clear()
		{
			x = 0.0f;
			y = 0.0f;
		}
		
		__forceinline Vector2 operator/(const float val) const
		{
			return Vector2(x / val, y / val);
		}

		__forceinline Vector2 operator+(const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}
		__forceinline Vector2 operator-(const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		__forceinline Vector2 operator*(const Vector2& other) const
		{
			return Vector2(x * other.x, y * other.y);
		}

		__forceinline Vector2 operator*(const float scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		
		__forceinline Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		__forceinline Vector2& operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		__forceinline Vector2& operator*=(const Vector2& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		__forceinline Vector2& operator*=(const float val)
		{
			x *= val;
			y *= val;
			return *this;
		}

		__forceinline bool operator==(const Vector2& other) const
		{
			return x == other.x && y == other.y;
		}

		__forceinline bool operator!=(const Vector2& other) const
		{
			return x != other.x && y != other.y;
		}

		__forceinline Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}

		__forceinline float GetLength()
		{
			return static_cast<float>((std::sqrt((x * x) + (y * y))));
		}

		__forceinline Vector2& Normalize()
		{
			float lenth = GetLength();
			x /= lenth;
			y /= lenth;
			return *this;
		}

		__forceinline float Dot(const Vector2& other) const
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

		__forceinline void GetSinCosValueAtDegree(float& out_sin, float& out_cos, float degree)
		{
			out_sin = sinf(DegreeToRad(degree));
			out_cos = cosf(DegreeToRad(degree));
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
#pragma once

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
		void operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

	};

}
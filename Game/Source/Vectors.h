#pragma once

#include <math.h>

struct Vec2
{
	Vec2() : x(0.0f), y(0.0f) {}

	Vec2(float _x, float _y) : x(_x), y(_y) {}

	void SetZero() { x = 0.0f; y = 0.0f; }

	void Set(float _x, float _y) { x = _x; y = _y; }

	void operator +=(const Vec2& v2)
	{
		x += v2.x;
		y += v2.y;
	}

	void operator -=(const Vec2& v2)
	{
		x -= v2.x;
		y -= v2.y;
	}

	void operator *=(float num)
	{
		x *= num;
		y *= num;
	}

	void operator +(const Vec2& v2)
	{
		x += v2.x;
		y += v2.y;
	}

	void operator -(const Vec2& v2)
	{
		x -= v2.x;
		y -= v2.y;
	}
	
	void operator *(float num) 
	{
		x *= num;
		y *= num;
	}

	float LengthSquared() const
	{
		return sqrtf(x * x + y * y);
	}

	float Length() const
	{
		return x * x + y * y;
	}

	void Normalize()
	{
		float length = Length();

		x = x / length;
		y = y / length;
	}

	float x, y;
};
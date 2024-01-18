#pragma once
#include <cmath>
#include <windows.h>

using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int65		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

struct State
{
	int32 hp = 0;
	int maxHp = 0;
	float speed = 0;
};

struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) :x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}
	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}

	float LengthSqured()
	{
		//루트 씌우는 비용이 비싸서 이렇게 씌우지 않는경우를 지원할 때가 많음
		//최단거리에있는 친구를 찾는다거나 한다면 굳이 루트를 씌우거나 할 필요가 없음
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSqured());
	}

	void Normalize()
	{
		float length = Length();
		if (length < 0.000000f)
			return;

		x /= length;
		y /= length;
	}

	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}
	
	float Cross(Vector other)
	{
		return x * other.y - y * other.x;
	}
	
	float x = 0;
	float y = 0;
};

using Pos = Vector;

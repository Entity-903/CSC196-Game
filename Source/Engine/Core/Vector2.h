#pragma once

namespace kiko
{
	class Vector2
	{
	public:
		float x, y;

	public:
		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {}

		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		float lengthSqr() { return (x * x) + (y * y); }
		float length() { return std::sqrt(lengthSqr()); }

		Vector2 Normalized() { return *this / length(); }
		void Normalize() { *this /= length(); }
	};

	using vec2 = Vector2;
}
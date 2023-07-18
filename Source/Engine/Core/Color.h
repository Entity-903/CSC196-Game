#pragma once
#include "MathUtils.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace kiko
{
	class Color
	{
	public:
		float r, g, b, a;

	public:
		Color() : r(0), g(0), b(0), a(0) {}
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		static uint8_t ToInt(float c) { return static_cast<uint8_t>(Clamp(c, 0.0f, 1.0f) * 255); }
	};

	inline std::istream& operator >> (std::istream& stream, Color& v)
	{
		std::string line;
		std::getline(stream, line);

		return stream;
	}
}
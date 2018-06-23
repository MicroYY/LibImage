#pragma once
#include <stdint.h>

namespace image
{
	struct Color
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		Color() :red(0), green(0), blue(0) {}
		Color(uint8_t _red, uint8_t _green, uint8_t _blue) :
			red(_red), green(_green), blue(_blue) {}
		Color(Color const& src) :red(src.red), green(src.green), blue(src.blue) {}
	};




}
#pragma once


namespace math
{


	template<typename T>
	inline T
		interpolate(T const& v1, T const& v2, float w1, float w2)
	{
		return v1 * w1 + v2 * w2;
	}

	template<>
	inline unsigned char
		interpolate(unsigned char const& v1, unsigned char const& v2,
			float w1, float w2)
	{
		return (unsigned char)((float)v1 * w1 + (float)v2 * w2 + 0.5f);
	}

	template<typename T>
	inline T
		interpolate(T const& v1, T const& v2, T const& v3,
			float w1, float w2, float w3)
	{
		return v1 * w1 + v2 * w2 + v3 * w3;
	}

	template<>
	inline unsigned char
		interpolate(unsigned char const& v1, unsigned char const& v2, unsigned char const& v3,
			float w1, float w2, float w3)
	{
		return (unsigned char)((float)v1 * w1 + (float)v2 * w2 + (float)v3 * w3 + 0.5f);
	}

}
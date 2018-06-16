#pragma once


namespace shape
{

	/*
		二维点
	*/
	template<typename T>
	struct Point2_
	{
		T x;
		T y;

		Point2_() :x(T(0)), y(T(0)) {}
		Point2_(T _x, T _y) :x(_x), y(_y) {}
		Point2_(Point2_ const& src) :x(src.x), y(src.y) {}

	};

	typedef Point2_<int> Point2i;
	typedef Point2_<float> Point2f;
	typedef Point2_<double> Point2d;
	typedef Point2i Point;


	/*
		三维点
	*/
	template<typename T>
	struct Point3_
	{
		T x;
		T y;
		T z;

		Point3_() :x(T(0)), y(T(0)), z(T(0)) {}
		Point3_(T _x, T _y, T _z) :x(_x), y(_y), z(_z) {}
		Point3_(Point3_ const& src) :x(src.x), y(src.y) {}
	};

	typedef Point3_<int> Point3i;
	typedef Point3_<float> Point3f;
	typedef Point3_<double> Point3d;


	/*
		线段
	*/
	struct Line
	{
		Point pt1;
		Point pt2;
	};


	/*
		矩形
	*/
	template<typename T>
	struct Rect_
	{
		T x, y;
		T width, height;

		Rect_() {}
		Rect_(T _x, T _y, T _width, T _height) :x(_x), y(_y), width(_width), height(_height)
		{
			if (_width <= 0 || _height <= 0 || _x < 0 || _y < 0)
				throw std::invalid_argument("Invaild parameter");
		};

		Rect_(Rect_ const& src) :x(src.x), y(src.y), width(src.width), height(src.height) {};


	};

	typedef Rect_<int> Rect2i;
	typedef Rect_<float> Rect2f;
	typedef Rect_<double> Rect2d;
	typedef Rect2i Rect;

	struct Circle
	{

	};
}
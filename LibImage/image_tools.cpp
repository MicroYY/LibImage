﻿
#include <math.h>
#include <iostream>
#include "image_tools.h"


namespace image
{

	void
		fill(ByteImage::Ptr src, Color const & color)
	{
		if (src == nullptr)
			throw std::invalid_argument("No image given");
		int const c = src->channels();
		if (c != 3)
			throw std::invalid_argument("Channels must be 3");
		for (int i = 0; i < src->GetPixelAmount(); i++)
		{
			src->at(i, 0) = color.red;
			src->at(i, 1) = color.green;
			src->at(i, 2) = color.blue;
		}
	}

	void 
		fillRect(ByteImage::Ptr src, Color const & color, shape::Rect roi)
	{
		if (src == nullptr)
			throw std::invalid_argument("No image given");
		int const c = src->channels();
		if (c != 3)
			throw std::invalid_argument("Channels must be 3");
		if (roi.x >= src->width() || roi.y >= src->height())
			throw std::invalid_argument("Rect out of range");
		int const img_height = src->height();
		int const img_width = src->width();
		int const xx = roi.x;
		int const yy = roi.y;

		for (size_t i = 0; i < roi.width; i++)
		{
			int x = xx + i;
			if (x >= img_width)
				break;
			for (size_t j = 0; j < roi.height; j++)
			{
				int y = yy + j;
				if (y >= img_height)
					break;
				src->at(x, y, 0) = color.red;
				src->at(x, y, 1) = color.green;
				src->at(x, y, 2) = color.blue;
			}
		}
	}


	void
		line(ByteImage::Ptr src, shape::Line const & l, Color const & color)
	{
		line(src, l.pt1, l.pt2, color);
	}

	void
		line(ByteImage::Ptr src, shape::Point const & pt1, shape::Point const & pt2, Color const & color)
	{
		if (src == nullptr)
			throw std::invalid_argument("No image given");
		if (src->channels() != 3)
			throw std::invalid_argument("No RGB image given");
		if (pt1.x < 0 || pt1.x > src->width() || pt1.y < 0 || pt1.y > src->height() ||
pt2.x < 0 || pt2.x > src->width() || pt2.y < 0 || pt2.y > src->height())
throw std::invalid_argument("Line must not be beyond the image");
if (pt1.x == pt2.x)
{
	int max = std::max(pt1.y, pt2.y);
	int min = std::min(pt1.y, pt2.y);
	for (int i = min; i <= max; i++)
	{
		int x = pt1.x;
		int y = i;
		src->at(x, y, 0) = color.red;
		src->at(x, y, 1) = color.green;
		src->at(x, y, 2) = color.blue;
	}
	return;
}
else if (pt1.y == pt2.y)
{
	int max = std::max(pt1.x, pt2.x);
	int min = std::min(pt1.x, pt2.x);
	for (int i = min; i <= max; i++)
	{
		int x = i;
		int y = pt1.y;
		src->at(x, y, 0) = color.red;
		src->at(x, y, 1) = color.green;
		src->at(x, y, 2) = color.green;
	}
	return;
}
else
{
	float tan = static_cast<float>(pt2.y - pt1.y) / (pt2.x - pt1.x);
	if (std::abs(tan) <= 1)
	{
		if (pt1.x < pt2.x)
		{
			for (int i = pt1.x; i <= pt2.x; i++)
			{
				int x = i;
				int y = std::round(tan * (i - pt1.x) + pt1.y);
				src->at(x, y, 0) = color.red;
				src->at(x, y, 1) = color.green;
				src->at(x, y, 2) = color.blue;
			}
			return;
		}
		else
		{
			for (int i = pt2.x; i <= pt1.x; i++)
			{
				int x = i;
				int y = std::round(tan * (i - pt2.x) + pt2.y);
				src->at(x, y, 0) = color.red;
				src->at(x, y, 1) = color.green;
				src->at(x, y, 2) = color.blue;
			}
			return;
		}

	}
	else
	{
		if (pt1.y < pt2.y)
		{
			for (int i = pt1.y; i < pt2.y; i++)
			{
				int x = std::round((i - pt1.y) / tan + pt1.x);
				int y = i;
				src->at(x, y, 0) = color.red;
				src->at(x, y, 1) = color.green;
				src->at(x, y, 2) = color.blue;
			}
			return;
		}
		else
		{
			for (int i = pt2.y; i < pt1.y; i++)
			{
				int x = std::round((i - pt2.y) / tan + pt2.x);
				int y = i;
				src->at(x, y, 0) = color.red;
				src->at(x, y, 1) = color.green;
				src->at(x, y, 2) = color.blue;
			}
			return;
		}
	}

}
	}

	ByteImage::Ptr generateChessoard(int rows, int columns, int cube)
	{
		
		ByteImage::Ptr ret = ByteImage::create(columns * cube, rows * cube, 3);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				if ((i + j) % 2 == 0)
				{
					shape::Rect roi(j * cube, i * cube, cube, cube);
					fillRect(ret, Color(255, 255, 255), roi);
				}
			}
		}
		return ret;
	}



}
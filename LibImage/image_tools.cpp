
#include <math.h>

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
		line(ByteImage::Ptr src, shape::Line const & l, Color const & color)
	{
		line(src, l.pt1, l.pt2,color);
	}

	void line(ByteImage::Ptr src, shape::Point const & pt1, shape::Point const & pt2, Color const & color)
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
			for (int i = pt1.y; i <= pt2.y; i++)
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
			for (int i = pt1.x; i <= pt2.x; i++)
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
	}



}
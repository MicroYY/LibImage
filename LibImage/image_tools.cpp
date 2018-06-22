#include "image_tools.h"

namespace image
{

	ByteImage::Ptr fill(ByteImage::ConstPtr src, Color const & color)
	{
		if (src == nullptr)
			throw std::invalid_argument("No image given");
		int const c = src->channels();
		if (c != 3)
			throw std::invalid_argument("Channels must be 3");
		ByteImage::Ptr img = ByteImage::create(src->width(), src->height(), 3);
		for (int i = 0; i < src->GetPixelAmount(); i++)
		{
			img->at(i, 0) = color.red;
			img->at(i, 1) = color.green;
			img->at(i, 2) = color.blue;
		}
		return img;
	}

}
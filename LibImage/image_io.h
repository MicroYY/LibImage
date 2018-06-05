#pragma once


#include <string>

#include "image.h"

namespace image
{

	struct ImageHeaders
	{
		int width;
		int height;
		int channels;
		ImageType type;
	};



	ByteImage::Ptr
		load_file(std::string const& filename);



	/****************************** PNG ******************************/

	ByteImage::Ptr
		load_png_file(std::string const& filename);

	void
		save_png_file(ByteImage::ConstPtr image,
			std::string const& filename, int compression_level = 1);



	/****************************** JPG ******************************/
	ByteImage::Ptr
		load_jpg_file(std::string const& filename, std::string* exif = nullptr);

	void
		save_jpg_file(ByteImage::ConstPtr image,
			std::string const& filename, int quality);


}

#include <iostream>


#include "image_io.h"
#include "image_tools.h"

int main()
{

	image::ByteImage::Ptr img = image::load_jpg_file("..\\x.jpg");
	image::ByteImage::Ptr img2 = image::hstack<uint8_t>(img, img);
	image::ByteImage::Ptr img3 = image::vstack<uint8_t>(img, img);
	image::save_png_file(img2, "3.png");
	image::save_png_file(img3, "4.png");


	return 0;
}
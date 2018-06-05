
#include <iostream>


#include "image_io.h"
#include "image_tools.h"

int main()
{

	image::ByteImage::Ptr img = image::load_png_file("..\\test.png");
	image::ByteImage::Ptr out = image::RGB2Gray<uint8_t>(img);
	
	image::save_png_file(out, "5.png");
	//image::ByteImage::Ptr img2 = image::hstack<uint8_t>(img, img);
	//image::ByteImage::Ptr img3 = image::vstack<uint8_t>(img, img);
	//image::save_png_file(img2, "3.png");
	//image::save_png_file(img3, "4.png");


	return 0;
}

#include <iostream>


#include "image_io.h"
#include "image_tools.h"
#include "shape.h"

int main()
{

	image::ByteImage::Ptr img = image::load_png_file("..\\test.png");
	//image::ByteImage::Ptr out = image::RGB2Gray<uint8_t>(img);
	image::ByteImage::Ptr out = image::ByteImage::create(*img,shape::Rect(960,540,960,540));
	image::ByteImage::Ptr out2 = (*img)(shape::Rect(0,0,1920,1080));
	out = image::fill(out, image::Color(255, 255, 0));
	image::save_png_file(out2, "7.png");
	image::save_png_file(out, "8.png");
	//image::ByteImage::Ptr img2 = image::hstack<uint8_t>(img, img);
	//image::ByteImage::Ptr img3 = image::vstack<uint8_t>(img, img);
	//image::save_png_file(img2, "3.png");
	//image::save_png_file(img3, "4.png");


	return 0;
}
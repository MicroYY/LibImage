
#include <iostream>


#include "image_io.h"
#include "image_tools.h"
#include "color.h"


int main()
{

	image::ByteImage::Ptr img = image::load_png_file("..\\test.png");
	//image::ByteImage::Ptr out = image::RGB2Gray<uint8_t>(img);
	/*image::ByteImage::Ptr out = image::ByteImage::create(*img,shape::Rect(960,540,960,540));
	image::ByteImage::Ptr out2 = (*img)(shape::Rect(0,0,1920,1080));
	out = image::fill(out, image::Color(255, 255, 0));
	image::save_png_file(out2, "7.png");
	image::save_png_file(out, "8.png");*/
	//image::ByteImage::Ptr img2 = image::hstack<uint8_t>(img, img);
	//image::ByteImage::Ptr img3 = image::vstack<uint8_t>(img, img);
	//image::save_png_file(img2, "3.png");
	//image::save_png_file(img3, "4.png");

	/*image::ByteImage::Ptr in = image::load_jpg_file("../l.jpg");
	image::ByteImage::Ptr img2 = image::hstack<uint8_t>(img, img);
	image::save_png_file(img2, "2.png");*/

	/*image::ByteImage::Ptr i = image::ByteImage::create(1000, 1000, 3);
	image::fill(i, image::Color(0, 0, 255));
	image::line(i, shape::Point(900,20),shape::Point(20,900), image::Color(0, 255, 255));
	image::save_png_file(i, "9.png");*/

	//image::ByteImage::Ptr i = image::ByteImage::create(1200, 1000, 3);
	//image::fill(i, image::Color(0, 0, 0));
	//image::fillRect(i, image::Color(255, 255, 255), shape::Rect(100, 50, 50, 20));
	//image::save_png_file(i, "i.png");

	image::ByteImage::Ptr ii = image::generateChessoard(11, 8, 60);
	image::save_png_file(ii, "ii.png");

	return 0;
}
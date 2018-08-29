#pragma once


#include <algorithm>

#include "image.h"
#include "functions.h"
#include "color.h"



namespace image
{
	
	/*
		用固定RGB填充整个图片
	*/
	void fill(ByteImage::Ptr src, Color const& color);

	/*
		用固定RGB填充某个矩形区域
	*/
	void fillRect(ByteImage::Ptr src, Color const& color, shape::Rect roi);

	/*****************************   绘制图形   *****************************/

	/*
		画线段
	*/
	void line(ByteImage::Ptr src, shape::Line const& l,Color const& color);
	void line(ByteImage::Ptr src, shape::Point const& pt1, shape::Point const& pt2, Color const& color);

	ByteImage::Ptr generateChessoard(int rows, int columns, int cube);



	/*****************************   形状尺寸有关   *****************************/

	/*
		两张图片水平拼接
	*/
	template<typename T>
	typename Image<T>::Ptr
		hstack(typename Image<T>::ConstPtr img1, typename Image<T>::ConstPtr img2);

	/*
		两张图片垂直拼接
	*/
	template<typename T>
	typename Image<T>::Ptr
		vstack(typename Image<T>::ConstPtr img1, typename Image<T>::ConstPtr img2);



	/*****************************   颜色有关   *****************************/

	enum cvtType
	{
		CVT_TYPE_MAXIMUM,
		CVT_TYPE_LIGHTNESS,
		CVT_TYPE_LUMINOSITY,
		CVT_TYPE_LUMINANCE,
		CVT_TYPE_AVERAGE
	};

	template<typename T>
	typename Image<T>::Ptr
		RGB2Gray(typename Image<T>::ConstPtr img, cvtType type);









	/*****************************   implementation   *****************************/

	template<typename T>
	typename Image<T>::Ptr
		hstack(typename Image<T>::ConstPtr img1, typename Image<T>::ConstPtr img2)
	{
		if (img1->height() != img2->height() || img1->channels() != img2->channels())
			throw std::invalid_argument("两幅图片无法水平拼接");

		Image<T>::Ptr ret = Image<T>::create(img1->width() + img2->width(),
			img1->height(),
			img1->channels());
		auto iter1 = img1->begin();
		auto iter2 = img2->begin();
		int off1 = img1->width() * img1->channels();
		int off2 = img2->width() * img2->channels();
		for (auto iter = ret->begin(); iter != ret->end();
			iter1 += off1, iter2 += off2, iter += (off1 + off2))
		{
			std::copy(iter1, iter1 + off1, iter);
			std::copy(iter2, iter2 + off2, iter + off1);
		}
		return ret;
	}

	template<typename T>
	typename Image<T>::Ptr
		vstack(typename Image<T>::ConstPtr img1, typename Image<T>::ConstPtr img2)
	{
		if (img1->width() != img2->width() || img1->channels() != img2->channels())
			throw std::invalid_argument("两幅图片无法垂直拼接");

		Image<T>::Ptr ret = Image<T>::create(img1->width(),
			img1->height() + img2->height(),
			img1->channels());
		std::copy(img1->begin(), img1->end(), ret->begin());
		std::copy(img2->begin(), img2->end(), ret->begin() + img1->GetValueAmount());
		return ret;
	}



	template<typename T>
	inline T
		RGB2Gray_maximum(T const* v)
	{
		return *std::max_element(v, v + 3);
	}

	template<typename T>
	inline T
		RGB2Gray_lightness(T const* v)
	{
		T const* max = std::max_element(v, v + 3);
		T const* min = std::min_element(v, v + 3);
		return math::interpolate(*max, *min, 0.5f, 0.5f);
	}

	template<typename T>
	inline T
		RGB2Gray_luminosity(T const* v)
	{
		return math::interpolate(v[0], v[1], v[2], 0.21f, 0.72f, 0.07f);
	}

	template<typename T>
	inline T
		RGB2Gray_luminance(T const* v)
	{
		return math::interpolate(v[0], v[1], v[2], 0.30f, 0.59f, 0.11f);
	}

	template<typename T>
	inline T
		RGB2Gray_average(T const* v)
	{
		float third(1.0f / 3.0f);
		return math::interpolate(v[0], v[1], v[2], third, third, third);
	}

	template<typename T>
	typename Image<T>::Ptr
		RGB2Gray(typename Image<T>::ConstPtr img, cvtType type = CVT_TYPE_AVERAGE)
	{
		if (img == nullptr)
			throw std::invalid_argument("Null image given");

		int channels = img->channels();
		if (channels != 3 && channels != 4)
			throw std::invalid_argument("Image must be RGB or RGBA");

		bool has_alpha = (channels == 4);

		typename Image<T>::Ptr out(Image<T>::create());
		out->allocate(img->width(), img->height(), 1 + has_alpha);

		typedef T(*RGB2GrayFunc)(T const*);
		RGB2GrayFunc func;
		switch (type)
		{
		case CVT_TYPE_MAXIMUM:
			func = RGB2Gray_maximum<T>;
			break;
		case CVT_TYPE_LIGHTNESS:
			func = RGB2Gray_lightness;
			break;
		case CVT_TYPE_LUMINOSITY:
			func = RGB2Gray_luminosity;
			break;
		case CVT_TYPE_LUMINANCE:
			func = RGB2Gray_luminance;
			break;
		case CVT_TYPE_AVERAGE:
			func = RGB2Gray_average;
			break;
		default:
			throw std::invalid_argument("Invalid conversion type");
			break;
		}
		int outpos = 0;
		int inpos = 0;
		int pixels = img->GetPixelAmount();
		for (int i = 0; i < pixels; i++)
		{
			T const* v = &img->at(inpos);
			//每个像素插值
			out->at(outpos) = func(v);
			if (has_alpha)
				out->at(outpos + 1) = img->at(inpos + 3);
			outpos += 1 + has_alpha;
			inpos += 3 + has_alpha;
		}
		return out;
	}

}
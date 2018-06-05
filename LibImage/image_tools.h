#pragma once


#include <algorithm>

#include "image.h"



namespace image
{
	
	/*****************************   形状尺寸有关   *****************************/

	/*
		两张图片水平拼接
	*/
	template<typename T>
	typename Image<T>::Ptr
		hstack(typename Image<T>::ConstPtr img1,typename Image<T>::ConstPtr img2);

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
		RGB2Gray(typename Image<T>::ConstPtr img,cvtType type);



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

	}

	template<typename T>
	typename Image<T>::Ptr 
		RGB2Gray(typename Image<T>::ConstPtr img, cvtType type)
	{
		if (img == nullptr)
			throw std::invalid_argument("Null image given");

		int channels = img->channels();
		if (channels != 3 && channels != 4)
			throw std::invalid_argument("Image must be RGB or RGBA");

		bool has_alpha = (channels == 4);

		typename Image<T>::Ptr out(Image<T>::Create());
		out->allocate(img->widht(), img->height(), 1 + has_alpha);

		typedef T(*RGB2GrayFunc)(T const*);
		RGB2GrayFunc func;
		switch (type)
		{
		case image::CVT_TYPE_MAXIMUM:
			break;
		case image::CVT_TYPE_LIGHTNESS:
			break;
		case image::CVT_TYPE_LUMINOSITY:
			break;
		case image::CVT_TYPE_LUMINANCE:
			break;
		case image::CVT_TYPE_AVERAGE:
			break;
		default:
			break;
		}
	}

}
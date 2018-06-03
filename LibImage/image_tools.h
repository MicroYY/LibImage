#pragma once

#include "image.h"



namespace image
{
	
	/*****************************   尺寸有关   *****************************/

	/*
		两张图片水平合并
	*/
	template<typename T>
	typename Image<T>::Ptr
		hstack(typename Image<T>::ConstPtr img1,typename Image<T>::ConstPtr img2);

	/*
		两张图片垂直合并
	*/
	template<typename T>
	typename Image<T>::Ptr
		vstack(typename Image<T>::ConstPtr img1, typename Image<T>::ConstPtr img2);





	



	template<typename T>
	typename Image<T>::Ptr 
		hstack(typename Image<T>::ConstPtr img1, typename Image<T>::ConstPtr img2)
	{
		if (img1->height() != img2->height() || img1->channels() != img2->channels())
			throw std::invalid_argument("两幅图片无法水平合并");

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
			throw std::invalid_argument("两幅图片无法垂直合并");

		Image<T>::Ptr ret = Image<T>::create(img1->width(),
			img1->height() + img2->height(),
			img1->channels());
		std::copy(img1->begin(), img1->end(), ret->begin());
		std::copy(img2->begin(), img2->end(), ret->begin() + img1->GetValueAmount());
		return ret;
	}

}
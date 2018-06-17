#pragma once

#include <memory>
#include <vector>

#include "shape.h"


namespace image
{
	enum ImageType
	{
		IMAGE_TYPE_UNKNOWN,

		IMAGE_TYPE_SINT8,
		IMAGE_TYPE_SINT16,
		IMAGE_TYPE_SINT32,
		IMAGE_TYPE_SINT64,

		IMAGE_TYPE_UINT8,
		IMAGE_TYPE_UINT16,
		IMAGE_TYPE_UINT32,
		IMAGE_TYPE_UINT64,

		IMAGE_TYPE_FLOAT,
		IMAGE_TYPE_DOUBLE
	};

	template<typename T>
	class Image;
	typedef Image<uint8_t> ByteImage;
	typedef Image<uint16_t> RawImage;
	typedef Image<char> CharImage;
	typedef Image<float> FloatImage;
	typedef Image<double> DoubleImage;
	typedef Image<int> IntImage;



	template<typename T>
	class Image
	{
	public:
		typedef std::shared_ptr<Image<T>> Ptr;
		typedef std::shared_ptr<Image<T>const> ConstPtr;

		typedef T ValueType;
		typedef std::vector<T> ImageData;

	public:

		/*
			构造函数
		*/
		Image();
		~Image();
		Image(int width, int height, int channels);
		Image(Image<T> const& src);

		Image(Image<T> const& src, shape::Rect const& roi);



		static Ptr create();
		static Ptr create(int width, int height, int channels);
		static Ptr create(Image<T> const& src);

		static Ptr create(Image<T> const& src, shape::Rect const& roi);

		int width() const;
		int height() const;
		int channels() const;

		void allocate(int width, int height, int channels);

		bool valid() const;

		/*
			返回图像类型
		*/
		ImageType GetType() const;


		/*
			返回数据集合
		*/
		ImageData const& GetData() const;
		ImageData& GetData();

		/*
			返回数据指针
		*/
		T const* GetDataPointer() const;
		T* GetDataPointer();

		/*
			迭代器
		*/
		T* begin();
		T const* begin() const;
		T* end();
		T const* end() const;

		/*
			像素数量与像素值数量
		*/
		int GetPixelAmount() const;
		int GetValueAmount() const;

		/*
			索引
		*/
		T const& at(int index) const;
		T& at(int index);

		T const& at(int pixel_index, int channel) const;
		T& at(int pixel_index, int channel);

		T const& at(int x, int y, int channel) const;
		T& at(int x, int y, int channel);

		/*
			操作符重载
		*/
		T& operator[] (int index);
		T const& operator[] (int index) const;

		T& operator() (int index);
		T const& operator() (int index) const;
		T& operator() (int pixel_index, int channel);
		T const& operator() (int pixel_index, int channel) const;
		T& operator() (int x, int y, int channel);
		T const& operator() (int x, int y, int channel) const;

		Ptr operator()(shape::Rect const& roi) const;

		/*
			一些基本操作
		*/
		void fill(T const& value);


	private:
		int w, h, c;
		ImageData data;
	};

	template<typename T>
	inline
		Image<T>::Image() :
		w(T(0)), h(T(0)), c(T(0)), data(T(0))
	{
	}

	template<typename T>
	inline
		Image<T>::~Image()
	{
		// TODO
	}

	template<typename T>
	inline
		Image<T>::Image(int width, int height, int channels)
	{
		this->allocate(width, height, channels);
	}


	template<typename T>
	inline
		Image<T>::Image(Image<T> const& src) :
		w(src.w), h(src.h), c(src.c), data(src.data)
	{
	}

	template<typename T>
	Image<T>::Image(Image<T> const & src, shape::Rect const & roi)
		:w(roi.width), h(roi.height), c(src.c)
	{
		if (src.w < (roi.width + roi.x) || src.h < (roi.height + roi.y))
			throw std::invalid_argument("ROI must be smaller than src");

		this->data.resize(roi.width * roi.height * src.c);
		auto iterDst = this->begin();
		int offDst = roi.width * src.c;
		auto iterSrc = src.begin();
		iterSrc += (roi.y * this->w + roi.x) * this->c;
		int offSrc = src.w * src.c;
		for (; iterDst < this->end(); iterSrc += offSrc, iterDst += offDst)
		{
			std::copy(iterSrc, iterSrc + offDst, iterDst);
		}
	}

	template<typename T>
	inline typename Image<T>::Ptr
		Image<T>::create()
	{
		return Ptr(new Image<T>());
	}

	template<typename T>
	inline typename Image<T>::Ptr
		Image<T>::create(int width, int height, int channels)
	{
		return Ptr(new Image<T>(width, height, channels));
	}

	template<typename T>
	inline typename Image<T>::Ptr
		Image<T>::create(Image<T> const & src)
	{
		return Ptr(new Image<T>(src));
	}

	template<typename T>
	inline typename Image<T>::Ptr
		Image<T>::create(Image<T> const & src, shape::Rect const & roi)
	{
		return Ptr(new Image<T>(src, roi));
	}

	template<typename T>
	inline int
		Image<T>::width() const
	{
		return this->w;
	}

	template<typename T>
	inline int
		Image<T>::height() const
	{
		return this->h;
	}

	template<typename T>
	inline int
		Image<T>::channels() const
	{
		return this->c;
	}




	template<typename T>
	void
		Image<T>::allocate(int width, int height, int channels)
	{
		this->w = width;
		this->h = height;
		this->c = channels;
		this->data.resize(width * height * channels);
	}

	template<typename T>
	inline bool
		Image<T>::valid() const
	{
		return this->w && this->h && this->c;
	}

	template<typename T>
	inline ImageType
		Image<T>::GetType() const
	{
		return IMAGE_TYPE_UNKNOWN;
	}

	template<>
	inline ImageType
		Image<int8_t>::GetType() const
	{
		return IMAGE_TYPE_SINT8;
	}

	template<>
	inline ImageType
		Image<int16_t>::GetType() const
	{
		return IMAGE_TYPE_SINT16;
	}

	template<>
	inline ImageType
		Image<int32_t>::GetType() const
	{
		return IMAGE_TYPE_SINT32;
	}

	template<>
	inline ImageType
		Image<int64_t>::GetType() const
	{
		return IMAGE_TYPE_SINT64;
	}

	template<>
	inline ImageType
		Image<uint8_t>::GetType() const
	{
		return IMAGE_TYPE_UINT8;
	}

	template<>
	inline ImageType
		Image<uint16_t>::GetType() const
	{
		return IMAGE_TYPE_UINT16;
	}

	template<>
	inline ImageType
		Image<uint32_t>::GetType() const
	{
		return IMAGE_TYPE_UINT32;
	}

	template<>
	inline ImageType
		Image<uint64_t>::GetType() const
	{
		return IMAGE_TYPE_UINT64;
	}

	template<>
	inline ImageType
		Image<float>::GetType() const
	{
		return IMAGE_TYPE_FLOAT;
	}

	template<>
	inline ImageType
		Image<double>::GetType() const
	{
		return IMAGE_TYPE_DOUBLE;
	}




	template<typename T>
	inline typename Image<T>::ImageData const&
		Image<T>::GetData() const
	{
		return this->data;
	}

	template<typename T>
	inline typename Image<T>::ImageData&
		Image<T>::GetData()
	{
		return this->data;
	}

	template<typename T>
	inline T const*
		Image<T>::GetDataPointer() const
	{
		return this->data.empty() ? nullptr : &this->data[0];
	}

	template<typename T>
	inline T * Image<T>::GetDataPointer()
	{
		return this->data.empty() ? nullptr : &this->data[0];
	}

	template<typename T>
	inline T*
		Image<T>::begin()
	{
		return this->data.empty() ? nullptr : &this->data[0];
	}

	template<typename T>
	inline T const*
		Image<T>::begin() const
	{
		return this->data.empty() ? nullptr : &this->data[0];
	}

	template<typename T>
	inline T*
		Image<T>::end()
	{
		return this->data.empty() ? nullptr : this->begin() + this->data.size();
	}

	template<typename T>
	inline T const*
		Image<T>::end() const
	{
		return this->data.empty() ? nullptr : this->begin() + this->data.size();
	}

	template<typename T>
	inline int
		Image<T>::GetPixelAmount() const
	{
		return this->w * this->h;
	}

	template<typename T>
	inline int
		Image<T>::GetValueAmount() const
	{
		return static_cast<int>(this->data.size());
	}

	template<typename T>
	inline T const&
		Image<T>::at(int index) const
	{
		return this->data[index];
	}

	template<typename T>
	inline T&
		Image<T>::at(int index)
	{
		return this->data[index];
	}

	template<typename T>
	inline T const&
		Image<T>::at(int pixel_index, int channel) const
	{
		return this->data[this->c * pixel_index + channel];
	}

	template<typename T>
	inline T&
		Image<T>::at(int pixel_index, int channel)
	{
		return this->data[this->c * pixel_index + channel];
	}

	template<typename T>
	inline T const&
		Image<T>::at(int x, int y, int channel) const
	{
		//return this->at(y * this->w + x, channel);
		return this->data[channel + this->c * (x + this->w * y)];
	}

	template<typename T>
	inline T&
		Image<T>::at(int x, int y, int channel)
	{
		return this->data[channel + this->c * (x + this->w * y)];
	}

	template<typename T>
	inline T&
		Image<T>::operator[](int index)
	{
		return this->data[index];
	}

	template<typename T>
	inline T const&
		Image<T>::operator[](int index) const
	{
		return this->data[index];
	}

	template<typename T>
	inline T&
		Image<T>::operator()(int index)
	{
		return this->data[index];
	}

	template<typename T>
	inline T const&
		Image<T>::operator()(int index) const
	{
		return this->data[index];
	}

	template<typename T>
	inline T&
		Image<T>::operator()(int pixel_index, int channel)
	{
		return this->data[channel + this->c * pixel_index];
	}

	template<typename T>
	inline T const&
		Image<T>::operator()(int pixel_index, int channel) const
	{
		return this->data[channel + this->c * pixel_index];
	}

	template<typename T>
	inline T&
		Image<T>::operator()(int x, int y, int channel)
	{
		return this->data[channel + this->c * (x + this->w * y)];
	}

	template<typename T>
	inline T const&
		Image<T>::operator()(int x, int y, int channel) const
	{
		return this->data[channel + this->c * (x + this->w * y)];
	}

	template<typename T>
	inline typename Image<T>::Ptr 
		Image<T>::operator()(shape::Rect const & roi) const
	{
		return Ptr(new Image<T>(*this,roi));
	}




	template<typename T>
	inline void
		Image<T>::fill(T const & value)
	{
		std::fill(this->data.begin(), this->data.end(), value);
	}
}
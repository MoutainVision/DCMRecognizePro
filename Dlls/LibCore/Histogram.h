#pragma once

#include<string.h>

#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

namespace avs
{

	struct LIBCORE_API HistogramResult
	{
		HistogramResult()
		{
			min = max = mode = half_height_width = 0;
			std = cv = mean = skewness = 0;

		}

		bool operator == (const HistogramResult& r)
		{
			return (min == r.min && max == r.max &&
				mode == r.mode && std == r.std && cv == r.cv && mean == r.mean &&
				skewness == r.skewness &&
				half_height_width == r.half_height_width);
		}

		bool operator != (const HistogramResult& r)
		{
			return !(*this == r);
		}

		int min;
		int max;
		int mode;
		double std;
		double cv;
		double mean;
		double skewness;
		int half_height_width;
	};

	class LIBCORE_API Histogram
	{
	public:
		// 增加默认位数
		Histogram(int levels = 256)
		{
			_count = 0;
			_data = 0;
			setLevels(levels);
		}

		~Histogram()
		{
			delete[]_data;
		}

		Histogram& operator = (const Histogram& hist)
		{
			if (this == &hist)
				return *this;
			Histogram& nchist = (Histogram&)hist;
			if (_count != nchist.getLevels())
			{
				delete[]_data;
				_count = nchist.getLevels();
				_data = new int[_count];
			}

			memcpy(_data, (int*)nchist.ptr(), _count * sizeof(int));

			return *this;
		}

		int* ptr()
		{
			return _data;
		}

		void getResult(HistogramResult& res);

		// 设置直方图范围
		void setLevels(int count);

		int getLevels();

		// 设置直方图的位数
		void set(int bit = 8);
	private:
		int* _data;
		int _count;
	};
}

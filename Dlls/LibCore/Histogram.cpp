#include "histogram.h"
#include<cmath>

using namespace std;

namespace avs
{
	void Histogram::getResult(HistogramResult& res)
	{
		for (int i = 0; i < _count; i++)
		{
			if (_data[i] > 0)
			{
				res.min = i;
				break;
			}
		}
		for (int i = _count - 1; i >= 0; i--)
		{
			if (_data[i] > 0)
			{
				res.max = i;
				break;
			}
		}
		int maxi = 0;
		int maxv = _data[maxi];
		for (int i = 1; i < _count; i++)
		{
			if (_data[i] > maxv)
			{
				maxi = i;
				maxv = _data[maxi];
			}
		}
		res.mode = maxi;

		double mean = 0, dval = 0, std = 0, cv = 0, skewness = 0;
		int cnt = 0;

		for (int i = 0; i < _count; i++)
		{
			cnt += _data[i];
			mean += _data[i] * i;
		}
		if (cnt > 0)
		{
			mean /= cnt;
			for (int i = 0; i < _count; i++)
			{
				dval = (mean - i);
				std += _data[i] * dval * dval;
				skewness += _data[i] * dval * dval * dval;

			}
			std /= (cnt - 1);
			std = sqrt(std);
			if (std != 0)
			{
				skewness /= (cnt - 1) * pow(std, 3);
			}
			cv = (mean != 0) ? (100 * std / mean) : 100;
		}

		int pkmin = 0;
		int pkmax = 0;
		int range = 0;
		int pk = maxi;
		int pkvalue = _data[maxi];
		int pkhalf = (int)(pkvalue * 0.4);
		double left_peak_rate = 0.05; //20 / 256.0;
		double right_peak_rate = 0.95; //245 / 256.0;
		if ((pk > left_peak_rate * _count) && (pk < right_peak_rate * _count))
		{
			int* hist2 = new int[_count];
			memset(hist2, 0, sizeof(int) * _count);
			int* hist3 = new int[_count];
			memset(hist3, 0, sizeof(int) * _count);
			for (int i = 1; i < _count - 1; i++)
			{
				hist2[i] = ((_data[(i - 1)] + 2 * _data[i] + _data[(i + 1)]) / 4);
			}
			for (int i = 1; i < _count - 1; i++)
			{
				hist3[i] = ((hist2[(i - 1)] + 2 * hist2[i] + hist2[(i + 1)]) / 4);
			}
			pkvalue = hist3[pk];
			pkmin = pk - 1;
			while ((pkmin > 0) && (hist3[pkmin] > pkhalf))
			{
				pkmin--;
			}
			pkmax = pk + 1;
			while ((pkmax < _count - 1) && (hist3[pkmax] > pkhalf))
			{
				pkmax++;
			}
			range = pkmax - pkmin;

			delete[]hist2;
			delete[]hist3;
		}

		res.mean = mean;
		res.std = std;
		res.cv = cv;
		res.skewness = skewness;
		res.half_height_width = range;

		return;
	}

	void Histogram::setLevels(int count)
	{
		if (count != _count)
		{
			delete[]_data;
			_count = count;
			_data = new int[_count];
		}

		memset(_data, 0, sizeof(int) * _count);

		return;
	}

	int Histogram::getLevels()
	{
		return _count;
	}

	void Histogram::set(int bit)
	{
		setLevels(1 << bit);

		return;
	}

}


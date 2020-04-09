#include "Utility.h"

#include "CommonDef.h"

#include<cstring>
#include<time.h>
#include<fstream>
#include<io.h>

using std::fstream;

namespace avs
{
	int round(double x)
	{
		if (x < 0.0)
			return (int)(x - 0.5);
		else
			return (int)(x + 0.5);
	}

	double hypot(double a, double b)
	{
		double fa = fabs(a);
		double fb = fabs(b);

		if (fa > fb)
		{
			return fa * sqrt(1.0 + (fb / fa)*(fb / fa));
		}
		else if (fa < fb)
		{
			return fb * sqrt(1.0 + (fa / fb)*(fa / fb));
		}
		else
		{
			return 0.0;
		}
	}

	void getRandomArray(vector<int> &aRandomArr, size_t nLength, int nLower, int nUpper)
	{
		srand(time(nullptr));

		for (size_t k = 0; k < nLength; k++)
		{
			aRandomArr.push_back(rand() % (nUpper-nLower+1) + nLower);
		}

		srand(1);

		return;
	}

	void getRandomArray(vector<double> &aRandomArr, size_t nLength, double dLower, double dUpper)
	{
		srand(time(nullptr));

		for (size_t k = 0; k < nLength; k++)
		{
			aRandomArr.push_back((double)rand() / RAND_MAX * (dUpper - dLower) + dLower);
		}

		srand(1);

		return;
	}

	int compareDoubleA(const void *a, const void *b)
	{
		return *(double*)a > *(double*)b ? 1 : -1;
	}
	int compareDoubleD(const void *a, const void *b)
	{
		return *(double*)a > *(double*)b ? -1 : 1;
	}

	int compareDoubleDataElementA(const void *a, const void *b)
	{
		DoubleDataElement eA = *(DoubleDataElement*)a;

		DoubleDataElement eB = *(DoubleDataElement*)b;

		return eA.val > eB.val ? 1 : -1;
	}
	int compareDoubleDataElementD(const void *a, const void *b)
	{
		DoubleDataElement eA = *(DoubleDataElement*)a;

		DoubleDataElement eB = *(DoubleDataElement*)b;

		return eA.val > eB.val ? -1 : 1;
	}

	int compareIntegerA(const void *a, const void *b)
	{
		return *(int*)a > *(int*)b ? 1 : -1;
	}
	int compareIntegerD(const void *a, const void *b)
	{
		return *(int*)a > *(int*)b ? -1 : 1;
	}

	int compareIntegerDataElementA(const void *a, const void *b)
	{
		IntegerDataElement eA = *(IntegerDataElement*)a;

		IntegerDataElement eB = *(IntegerDataElement*)b;

		return eA.val > eB.val ? 1 : -1;
	}
	int compareIntegerDataElementD(const void *a, const void *b)
	{
		IntegerDataElement eA = *(IntegerDataElement*)a;

		IntegerDataElement eB = *(IntegerDataElement*)b;

		return eA.val > eB.val ? -1 : 1;
	}


	bool getMedian(int &m, int *pArr, int begin, int end)
	{
		if (nullptr == pArr || 0 > begin || begin > end)
		{
			return false;
		}

		if (begin+1 >= end)
		{
			m = pArr[begin];

			return true;
		}

		int *pA = nullptr;
		if (nullptr == (pA = new int[end - begin + 1]))
		{
			return false;
		}

		memcpy(pA, pArr + begin, (end - begin + 1) * sizeof(int));

		qsort(pA, (end - begin + 1), sizeof(int), compareIntegerA);
		
		m = *(pA + (end - begin + 1) / 2);
		
		delete[]pA;

		return true;
	}

	bool getMedian(double &m, double *pArr, int begin, int end)
	{
		if (nullptr == pArr || 0 > begin || begin > end)
		{
			return false;
		}

		if (begin + 1 >= end)
		{
			m = pArr[begin];

			return true;
		}

		double *pA = nullptr;
		if (nullptr == (pA = new double[end - begin + 1]))
		{
			return false;
		}

		memcpy(pA, pArr + begin, (end - begin + 1) * sizeof(double));

		qsort(pA, (end - begin + 1), sizeof(double), compareDoubleA);//be careful when you are sorting the floating arrays!!!
		
		m = *(pA + (end - begin + 1) / 2);
		
		delete[]pA;

		return true;
	}

	bool sort(double *pArr, int n, bool bAscending, int *pIndex)
	{
		if (nullptr == pArr || 0 >= n)
		{
			return false;
		}

		if (nullptr == pIndex)
		{
			if (bAscending)
			{
				qsort(pArr, n, sizeof(double), compareDoubleA);//be careful when you are sorting the floating arrays!!!
			}
			else
			{
				qsort(pArr, n, sizeof(double), compareDoubleD);//be careful when you are sorting the floating arrays!!!
			}
		}
		else
		{
			DoubleDataElement *pData = nullptr;
			if (nullptr == (pData = new DoubleDataElement[n]))
			{
				return false;
			}

			for (int i = 0; i < n; i++)
			{
				pData[i].val = pArr[i];
				pData[i].key = i;
			}

			if (bAscending)
			{
				qsort(pData, n, sizeof(DoubleDataElement), compareDoubleDataElementA);
			}
			else
			{
				qsort(pData, n, sizeof(DoubleDataElement), compareDoubleDataElementD);
			}

			for (int i = 0; i < n; i++)
			{
				pArr[i]   = pData[i].val;
				pIndex[i] = pData[i].key;
			}

			delete[]pData;
		}

		return true;
	}

	bool sort(int *pArr, int n, bool bAscending, int *pIndex)
	{
		if (nullptr == pArr || 0 >= n)
		{
			return false;
		}

		if (nullptr == pIndex)
		{
			if (bAscending)
			{
				qsort(pArr, n, sizeof(int), compareIntegerA);//be careful when you are sorting the floating arrays!!!
			}
			else
			{
				qsort(pArr, n, sizeof(int), compareIntegerD);//be careful when you are sorting the floating arrays!!!
			}
		}
		else
		{
			IntegerDataElement *pData = nullptr;
			if (nullptr == (pData = new IntegerDataElement[n]))
			{
				return false;
			}

			for (int i = 0; i < n; i++)
			{
				pData[i].val = pArr[i];
				pData[i].key = i;
			}

			if (bAscending)
			{
				qsort(pData, n, sizeof(IntegerDataElement), compareIntegerDataElementA);
			}
			else
			{
				qsort(pData, n, sizeof(IntegerDataElement), compareIntegerDataElementD);
			}

			for (int i = 0; i < n; i++)
			{
				pArr[i] = pData[i].val;
				pIndex[i] = pData[i].key;
			}

			delete[]pData;
		}

		return true;
	}


	bool getMeanStd(double &mean, double &std, double *data, int n)
	{
		if (nullptr == data || 0 >= n)
		{
			return false;
		}

		mean = 0;
		for (int i = 0; i < n; i++)
		{
			mean += data[i];
		}
		mean /= n;

		std = 0;
		for (int i = 0; i < n; i++)
		{
			std += (data[i] - mean) * (data[i] - mean);
		}

		if (n > 1)
		{
			std = sqrt(std / (n - 1));
		}

		return true;
	}

	bool normalizeMeanStd(double *data, int n, double *mean, double *std)
	{
		double c, s;
		if (!getMeanStd(c, s, data, n))
		{
			return false;
		}

		if (fabs(s) > DBL_EPSILON)
		{
			for (int i = 0; i < n; i++)
			{
				data[i] = (data[i] - c) / s;
			}
		}

		if (nullptr != mean)
		{
			*mean = c;
		}

		if (nullptr != std)
		{
			*std = s;
		}

		return true;
	}

	bool normalizeUnit(double *pA, int n, double *dMinVal, double *dMaxVal)
	{
		if (nullptr == pA || 0 >= n)
		{
			return false;
		}

		double dMin = pA[0];
		double dMax = pA[0];
		for (int i = 1; i < n; i++)
		{
			if (pA[i] < dMin)
			{
				dMin = pA[i];
			}

			if (pA[i] > dMax)
			{
				dMax = pA[i];
			}
		}

		if (dMax - dMin > DBL_EPSILON)
		{
			for (int i = 0; i < n; i++)
				pA[i] = (pA[i] - dMin) / (dMax - dMin);
		}
		else
		{
			for (int i = 0; i < n; i++)
				pA[i] = 1.0;
		}

		if (nullptr != dMinVal)
		{
			*dMinVal = dMin;
		}

		if (nullptr != dMaxVal)
		{
			*dMaxVal = dMax;
		}

		return true;
	}


	bool getGaussianKernel(vector<double> &aK, int nRadius, double dSigma)
	{
		if (dSigma < 0.1 || dSigma > 250)
		{
			return false;
		}

		if (nRadius < 0)
		{
			return false;
		}

		double s2 = 2 * dSigma *dSigma;

		int length = 2 * nRadius + 1;

		double *pKernel = new double[length*length];

		int x;
		double sum = 0.0;
		for (x = -nRadius; x <= nRadius; x++)
		{
			for (int y = -nRadius; y <= nRadius; y++)
			{
				double w = exp(-(x*x + y * y) / s2);
				pKernel[(x + nRadius)*length + (y + nRadius)] = w;
				sum += w;

			}
		}

		aK.clear();

		for (x = -nRadius; x <= nRadius; x++)
		{
			for (int y = -nRadius; y <= nRadius; y++)
			{
				pKernel[(x + nRadius)*length + (y + nRadius)] /= sum;
			}
		}

		aK.insert(aK.end(), pKernel, pKernel + length * length);

		delete[]pKernel;

		return true;
	}

	bool getGaussianKernel(vector<double> &aK, double dSigma)
	{
		if (dSigma < 0.1 || dSigma > 250)
		{
			return false;
		}

		double s2 = 2 * dSigma * dSigma;

		int n = 0;
		bool bEnough = true;
		double sum = 0.0;

		double *pKernel = nullptr;

		do
		{
			if (nullptr != pKernel)
			{
				delete[]pKernel;
			}

			int length = 2 * n + 1;
			pKernel = new double[length*length];
			bEnough = true;
			sum = 0.0;
			for (int x = -n; x <= n; x++)
			{
				for (int y = -n; y <= n; y++)
				{
					double w = exp(-(x*x + y * y) / s2);
					pKernel[(x + n)*length + (y + n)] = w;

					if (pKernel[0] * 255 > 1.49)
					{
						if (exp(-(n + 1)*(n + 1) / s2) * 255 > 1.49)
						{
							bEnough = false;
							break;
						}
					}

					sum += w;
				}

				if (!bEnough)
				{
					break;
				}
			}

			if (!bEnough)
			{
				n++;
			}

		} while (!bEnough);

		int length = 2 * n + 1;
		for (int x = 0; x < length; x++)
		{
			for (int y = 0; y < length; y++)
			{
				pKernel[x*length + y] /= sum;
			}
		}

		aK.clear();
		aK.insert(aK.end(), pKernel, pKernel + length * length);

		delete[]pKernel;

		return true;
	}


	bool gaussianSmooth3(unsigned char *pImg, int nWidth, int nPitch, int nHeight, ImageRect *aoi)
	{
		//3*3 kernel
		//1  2  1
		//2  4  2  
		//1  2  1
		//

		int xs, xe, ys, ye;
		if (nullptr == aoi)
		{
			xs = 0;
			xe = nWidth - 1;
			ys = 0;
			ye = nHeight - 1;
		}
		else
		{
			xs = aoi->xs;
			xe = aoi->xe;
			ys = aoi->ys;
			ye = aoi->ye;
		}

		if (nullptr == pImg ||
			xs < 0 || xs > xe || xe > nWidth - 1 ||
			ys < 0 || ys > ye || ye > nHeight - 1 ||
			nPitch < nWidth)
		{
			return false;
		}

		int nC = nPitch / nWidth;

		unsigned char *pTmp = new unsigned char[nPitch*nHeight];
		memcpy(pTmp, pImg, nPitch*nHeight * sizeof(unsigned char));

		if (nC == 1)
		{
			for (int y = ys + 1; y <= ye - 1; y++)
			{
				for (int x = xs + 1; x <= xe - 1; x++)
				{
					int pos = y * nPitch + x;

					int sum = (pTmp[pos] << 2)
						+ (pTmp[pos - 1] << 1) + (pTmp[pos + 1] << 1) + (pTmp[pos - nPitch] << 1) + (pTmp[pos + nPitch] << 1)
						+ pTmp[pos + nPitch + 1] + pTmp[pos + nPitch - 1] + pTmp[pos - nPitch + 1] + pTmp[pos - nPitch - 1];
					pImg[pos] = sum >> 4;
				}
			}
		}
		else if (nC >= 3)
		{
			for (int y = ys + 1; y <= ye - 1; y++)
			{
				for (int x = xs + 1; x <= xe - 1; x++)
				{
					int pos = y * nPitch + x * nC;

					int sum = (pTmp[pos] << 2)
						+ (pTmp[pos - nC] << 1) + (pTmp[pos + nC] << 1) + (pTmp[pos - nPitch] << 1) + (pTmp[pos + nPitch] << 1)
						+ pTmp[pos + nPitch + nC] + pTmp[pos + nPitch - nC] + pTmp[pos - nPitch + nC] + pTmp[pos - nPitch - nC];
					pImg[pos] = sum >> 4;

					pos++;
					sum = (pTmp[pos] << 2)
						+ (pTmp[pos - nC] << 1) + (pTmp[pos + nC] << 1) + (pTmp[pos - nPitch] << 1) + (pTmp[pos + nPitch] << 1)
						+ pTmp[pos + nPitch + nC] + pTmp[pos + nPitch - nC] + pTmp[pos - nPitch + nC] + pTmp[pos - nPitch - nC];
					pImg[pos] = sum >> 4;

					pos++;
					sum = (pTmp[pos] << 2)
						+ (pTmp[pos - nC] << 1) + (pTmp[pos + nC] << 1) + (pTmp[pos - nPitch] << 1) + (pTmp[pos + nPitch] << 1)
						+ pTmp[pos + nPitch + nC] + pTmp[pos + nPitch - nC] + pTmp[pos - nPitch + nC] + pTmp[pos - nPitch - nC];
					pImg[pos] = sum >> 4;
				}
			}
		}
		else
		{
			delete[]pTmp;
			return false;
		}

		delete[]pTmp;

		return true;
	}

	bool gaussianSmooth5(unsigned char *pImg, int nWidth, int nPitch, int nHeight, ImageRect *aoi)
	{
		//5*5 kernel
		//0  1  2  1  0
		//1  4  8  4  1  
		//2  8  16 8  2
		//1  4  8  4  1
		//0  1  2  1  0
		//

		int xs, xe, ys, ye;
		if (nullptr == aoi)
		{
			xs = 0;
			xe = nWidth - 1;
			ys = 0;
			ye = nHeight - 1;
		}
		else
		{
			xs = aoi->xs;
			xe = aoi->xe;
			ys = aoi->ys;
			ye = aoi->ye;
		}

		if (nullptr == pImg ||
			xs < 0 || xs > xe || xe >= nWidth ||
			ys < 0 || ys > ye || ye >= nHeight ||
			nPitch < nWidth)
		{
			return false;
		}

		int nC = nPitch / nWidth;

		unsigned char *pTmp = new unsigned char[nPitch*nHeight];
		memcpy(pTmp, pImg, nPitch*nHeight * sizeof(unsigned char));

		int nPitch2 = 2 * nPitch;

		if (nC == 1)
		{
			for (int y = ys + 2; y <= ye - 2; y++)
			{
				for (int x = xs + 2; x <= xe - 2; x++)
				{
					int pos = y * nPitch + x;

					int sum = (pTmp[pos] << 4) + (pTmp[pos - 1] << 3) + (pTmp[pos + 1] << 3) + (pTmp[pos - nPitch] << 3) + (pTmp[pos + nPitch] << 3)
						+ (pTmp[pos + nPitch + 1] << 2) + (pTmp[pos + nPitch - 1] << 2) + (pTmp[pos - nPitch + 1] << 2) + (pTmp[pos - nPitch - 1] << 2)
						+ (pTmp[pos + 2] << 1) + (pTmp[pos - 2] << 1) + (pTmp[pos - nPitch2] << 1) + (pTmp[pos + nPitch2] << 1)
						+ pTmp[pos + 2 - nPitch] + pTmp[pos + 2 + nPitch] + pTmp[pos - 2 - nPitch] + pTmp[pos - 2 + nPitch]
						+ pTmp[pos - nPitch2 + 1] + pTmp[pos - nPitch2 - 1] + pTmp[pos + nPitch2 - 1] + pTmp[pos + nPitch2 + 1];
					pImg[pos] = (unsigned char)(sum / 80);
				}
			}
		}
		else if (nC >= 3)
		{
			int nC2 = 2 * nC;

			for (int y = ys + 2; y <= ye - 2; y++)
			{
				for (int x = xs + 2; x <= xe - 2; x++)
				{
					int pos = y * nPitch + x * nC;

					int sum = (pTmp[pos] << 4) + (pTmp[pos - nC] << 3) + (pTmp[pos + nC] << 3) + (pTmp[pos - nPitch] << 3) + (pTmp[pos + nPitch] << 3)
						+ (pTmp[pos + nPitch + nC] << 2) + (pTmp[pos + nPitch - nC] << 2) + (pTmp[pos - nPitch + nC] << 2) + (pTmp[pos - nPitch - nC] << 2)
						+ (pTmp[pos + nC2] << 1) + (pTmp[pos - nC2] << 1) + (pTmp[pos - nPitch2] << 1) + (pTmp[pos + nPitch2] << 1)
						+ pTmp[pos + nC2 - nPitch] + pTmp[pos + nC2 + nPitch] + pTmp[pos - nC2 - nPitch] + pTmp[pos - nC2 + nPitch]
						+ pTmp[pos - nPitch2 + nC] + pTmp[pos - nPitch2 - nC] + pTmp[pos + nPitch2 - nC] + pTmp[pos + nPitch2 + nC];
					pImg[pos] = (unsigned char)(sum / 80);

					pos++;
					sum = (pTmp[pos] << 4) + (pTmp[pos - nC] << 3) + (pTmp[pos + nC] << 3) + (pTmp[pos - nPitch] << 3) + (pTmp[pos + nPitch] << 3)
						+ (pTmp[pos + nPitch + nC] << 2) + (pTmp[pos + nPitch - nC] << 2) + (pTmp[pos - nPitch + nC] << 2) + (pTmp[pos - nPitch - nC] << 2)
						+ (pTmp[pos + nC2] << 1) + (pTmp[pos - nC2] << 1) + (pTmp[pos - nPitch2] << 1) + (pTmp[pos + nPitch2] << 1)
						+ pTmp[pos + nC2 - nPitch] + pTmp[pos + nC2 + nPitch] + pTmp[pos - nC2 - nPitch] + pTmp[pos - nC2 + nPitch]
						+ pTmp[pos - nPitch2 + nC] + pTmp[pos - nPitch2 - nC] + pTmp[pos + nPitch2 - nC] + pTmp[pos + nPitch2 + nC];
					pImg[pos] = (unsigned char)(sum / 80);

					pos++;
					sum = (pTmp[pos] << 4) + (pTmp[pos - nC] << 3) + (pTmp[pos + nC] << 3) + (pTmp[pos - nPitch] << 3) + (pTmp[pos + nPitch] << 3)
						+ (pTmp[pos + nPitch + nC] << 2) + (pTmp[pos + nPitch - nC] << 2) + (pTmp[pos - nPitch + nC] << 2) + (pTmp[pos - nPitch - nC] << 2)
						+ (pTmp[pos + nC2] << 1) + (pTmp[pos - nC2] << 1) + (pTmp[pos - nPitch2] << 1) + (pTmp[pos + nPitch2] << 1)
						+ pTmp[pos + nC2 - nPitch] + pTmp[pos + nC2 + nPitch] + pTmp[pos - nC2 - nPitch] + pTmp[pos - nC2 + nPitch]
						+ pTmp[pos - nPitch2 + nC] + pTmp[pos - nPitch2 - nC] + pTmp[pos + nPitch2 - nC] + pTmp[pos + nPitch2 + nC];
					pImg[pos] = (unsigned char)(sum / 80);
				}
			}
		}
		else
		{
			delete[]pTmp;
			return false;
		}

		delete[]pTmp;

		return true;
	}



	int otsu(unsigned char *pImg, int nW, int nH, int nP, vector<ImageRect> &aAOI, double dA)
	{
		int x = 0, y = 0;
		int i, j, threshold = 0;

		int pixelCount[256];
		float pixelPro[256];

		//初始化
		for (i = 0; i < 256; i++)
		{
			pixelCount[i] = 0;
			pixelPro[i] = 0.0;
		}

		int nC = nP / nW;

		unsigned pixelSum = 0;

		//统计图像所选区域中的灰度级分布
		for (unsigned n = 0; n != aAOI.size(); ++n)
		{
			unsigned xs = aAOI[n].xs;
			unsigned xe = aAOI[n].xe;
			unsigned ys = aAOI[n].ys;
			unsigned ye = aAOI[n].ye;

			unsigned js = xs * nC;
			unsigned je = xe * nC + nC - 1;

			for (i = ys; i <= ye; i++)
			{
				for (j = js; j <= je; j++)
				{
					pixelCount[pImg[i * nP + j]]++;
				}
			}

			pixelSum += (xe - xs + 1) * nC;
		}

		//计算每个灰度级在图像所选区域中的比例
		for (i = 0; i < 256; i++)
		{
			pixelPro[i] = (float)(pixelCount[i]) / (float)(pixelSum);
		}

		//经典ostu算法,得到前景和背景的分割
		//遍历灰度级[0,255],计算出方差最大的灰度值,为最佳阈值
		float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
		for (i = 0; i < 256; i++)
		{
			w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
			for (j = 0; j < 256; j++)
			{
				if (j <= i) //背景部分
				{
					//以i为阈值分类，第一类总的概率
					w0 += pixelPro[j];
					u0tmp += j * pixelPro[j];
				}
				else //前景部分
				{
					//以i为阈值分类，第二类总的概率
					w1 += pixelPro[j];
					u1tmp += j * pixelPro[j];
				}
			}
			u0 = u0tmp / w0; //第一类的平均灰度
			u1 = u1tmp / w1; //第二类的平均灰度
			u = u0tmp + u1tmp; //整幅图像的平均灰度
			//计算类间方差
			deltaTmp = pow((double)w0, dA) * (u0 - u)*(u0 - u) + pow((double)w1, dA) * (u1 - u)*(u1 - u);
			//找出最大类间方差以及对应的阈值
			if (deltaTmp > deltaMax)
			{
				deltaMax = deltaTmp;
				threshold = i;
			}
		}
		//返回最佳阈值;
		return threshold;
	}


	// 二值化
	// 1. pImageData 图像数据
	// 2. nWidth 图像宽度
	// 3. nHeight 图像高度
	// 4. nWidthStep 图像行大小
	// 5. nThreshold 阈值
	bool binarization(unsigned char *pImage, int nWidth, int nHeight, int nPitch,
		vector<ImageRect> &aAOI, int nT)
	{
		int nThreshold;
		if (nT < 0 || nT > 255)
		{
			nThreshold = otsu(pImage, nWidth, nHeight, nPitch, aAOI);
		}
		else
		{
			nThreshold = nT;
		}

		int nChannels = nPitch / nWidth;

		int i = 0;
		int j = 0;
		unsigned char *pLine = nullptr;
		for (unsigned n = 0; n != aAOI.size(); ++n)
		{
			unsigned xs = aAOI[n].xs;
			unsigned xe = aAOI[n].xe;
			unsigned ys = aAOI[n].ys;
			unsigned ye = aAOI[n].ye;

			int ps = xs * nChannels;
			int pe = xe * nChannels;

			for (pLine = pImage + ys * nPitch, j = ys; j <= ye; j++, pLine += nPitch)
			{
				for (i = ps; i <= pe; i = i + nChannels)
				{
					bool bRet = false;
					for (int k = 0; k < nChannels; k++)
					{
						if (pLine[i + k] >= nThreshold)
						{
							bRet = true;
						}
					}

					if (bRet)
					{
						for (int k = 0; k < nChannels; k++)
						{
							pLine[i + k] = 0xff;
						}
					}
					else
					{
						for (int k = 0; k < nChannels; k++)
						{
							pLine[i + k] = 0x00;
						}
					}
				}
			}
		}

		return true;
	}


	bool getConfidenceInterval(double &dUpper, double &dLower, double dAcc, int nRec, int nConfidenceLevel)
	{
		if (dAcc < 0.0 || dAcc > 1.0 || nRec < 0 || nConfidenceLevel < 0 || nConfidenceLevel > 100)
		{
			return false;
		}

		double dZ;

		switch (nConfidenceLevel)
		{
		case 99:
			dZ = 2.58;
			break;

		case 98:
			dZ = 2.33;
			break;

		case 95:
			dZ = 1.96;
			break;

		case 90:
			dZ = 1.65;
			break;

		case 80:
			dZ = 1.28;
			break;

		case 70:
			dZ = 1.04;
			break;

		case 50:
			dZ = 0.67;
			break;

		default:
			return false;
		}

		double dD = dZ * sqrt(dZ * dZ + 4 * nRec * dAcc - 4 * nRec * dAcc * dAcc);

		dLower = (2 * nRec * dAcc + dZ * dZ - dD) / 2 / (nRec + dZ * dZ);

		dUpper = (2 * nRec * dAcc + dZ * dZ + dD) / 2 / (nRec + dZ * dZ);


		return true;

	}

	string::size_type findSubStrWithNoCase(string str, string substr)
	{
		//turn all strings to lowercase for finding
		for (string::size_type ix = 0; ix != str.size(); ++ix)
		{
			str[ix] = tolower(str[ix]);
		}

		for (string::size_type ix = 0; ix != substr.size(); ++ix)
		{
			substr[ix] = tolower(substr[ix]);
		}

		return str.find(substr);
	}

	void getFileList(vector<string> &aFileList, const string &strFolder, const string &strExt)
	{
		struct _finddata_t fd;
		string root(strFolder);
		root += "\\*.*";
		long hFile = _findfirst(root.c_str(), &fd);
		if (hFile == -1)//the given path is an empty directory
		{
			return;
		}

		do
		{
			size_t strLength = strlen(fd.name);
			if (((strLength == 1) && (fd.name[0] == '.'))//current directory
				|| ((strLength == 2) && (fd.name[0] == '.') && (fd.name[1] == '.'))//parent directory
				)
			{
				continue;
			}

			string full_path = strFolder + "\\" + fd.name;

			if (fd.attrib & _A_SUBDIR)//current object is a directory
			{
				getFileList(aFileList, full_path, strExt);
			}
			else//current object is a file
			{
				if (strExt == "*.*")
				{
					aFileList.push_back(full_path);
				}
				else
				{
					string::size_type pos = full_path.rfind('\\');
					string ext = full_path.substr(pos + 1);
					pos = ext.rfind('.');
					if (pos != string::npos)//the file has a postfix
					{
						ext = ext.substr(pos);//get the postfix

						if (findSubStrWithNoCase(ext, strExt) != string::npos)
						{//the postfix is in the predefined postfix list
							aFileList.push_back(full_path);
						}
					}
					else//the file has no postfix
					{
						if (strExt == "")//i do want to return files with no postfix
						{
							aFileList.push_back(full_path);
						}
					}
				}
			}

		} while (_findnext(hFile, &fd) == 0);

		_findclose(hFile);

		return;
	}

	bool isFileExisted(const char *szFile)
	{
		return ((_access(szFile, 0)) != -1);
	}

	// from h2o
	size_t base64_encode(char *_dst, const void *_src, size_t len, int url_encoded)
	{
		const char *MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";

		const char *MAP_URL_ENCODED = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789-_";

		char *dst = _dst;
		const uint8_t *src = reinterpret_cast<const uint8_t *>(_src);
		const char *map = url_encoded ? MAP_URL_ENCODED : MAP;
		uint32_t quad;

		for (; len >= 3; src += 3, len -= 3)
		{
			quad = ((uint32_t)src[0] << 16) | ((uint32_t)src[1] << 8) | src[2];
			*dst++ = map[quad >> 18];
			*dst++ = map[(quad >> 12) & 63];
			*dst++ = map[(quad >> 6) & 63];
			*dst++ = map[quad & 63];
		}

		if (len != 0)
		{
			quad = (uint32_t)src[0] << 16;
			*dst++ = map[quad >> 18];
			if (len == 2)
			{
				quad |= (uint32_t)src[1] << 8;
				*dst++ = map[(quad >> 12) & 63];
				*dst++ = map[(quad >> 6) & 63];
				if (!url_encoded)
					*dst++ = '=';
			}
			else
			{
				*dst++ = map[(quad >> 12) & 63];
				if (!url_encoded)
				{
					*dst++ = '=';
					*dst++ = '=';
				}
			}
		}

		*dst = '\0';
		return dst - _dst;
	}

	bool base64_encode(Buffer &_dst, const void *_src, size_t len, int url_encoded)
	{
		return false;
	}


	bool fileToBase64(char *base64, int &size, const char *szFileName)
	{
		fstream f(szFileName, std::ios_base::binary | std::ios_base::in);
		if (!f.good() || f.eof() || !f.is_open())
		{
			return false;
		}
		f.seekg(0, std::ios_base::beg);
		fstream::pos_type begin_pos = f.tellg();
		f.seekg(0, std::ios_base::end);
		size_t nFileSize = f.tellg() - begin_pos;
		
		unsigned char *pBuf = nullptr;
		if (nullptr == (pBuf = new unsigned char[nFileSize]))
		{
			return false;
		}

		f.seekg(0, std::ios::beg);
		f.read((char *)pBuf, nFileSize);

		size = base64_encode(base64, pBuf, nFileSize, 0);
		
		return true;
	}

	bool fileToBase64(Buffer &base64, const char *szFileName)
	{
		return false;
	}

}

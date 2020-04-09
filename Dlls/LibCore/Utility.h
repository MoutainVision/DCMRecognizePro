#pragma once


#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include "CommonDef.h"

#include"Buffer.h"

#include<vector>
#include<string>

using std::vector;
using std::string;

namespace avs
{
	/**
	*@brief 获取最接近的整数
	*
	*@param x [in]		输入浮点数
	*
	*@return 最近的整数
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API int round(double x);

	/**
	*@brief 计算两个数的平方和的根。相对于简单的sqrt(a^2+b^2)，该计算方法能有效防止数据溢出
	*
	*@param a [in]	输入浮点数
	*
	*@param b [in]	输入浮点数
	*
	*@return 两个数的平方和之根
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API double hypot(double a, double b);


	//LIBCORE_API unsigned calcBPP(EPixelFormat pixFmt);

	//LIBCORE_API unsigned calcImagePitch(unsigned nW, unsigned nBpp);



	/**
	*@brief 获取指定范围内的随机整数序列
	*
	*@param aRandomArr [out]	带输出的随机数序列
	*
	*@param nLength [in] 随机数个数
	*
	*@param nLower [in]	下限
	*
	*@param nUpper [in]	上限
	*
	*@return -
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API void getRandomArray(vector<int> &aRandomArr, size_t nLength, int nLower = 0, int nUpper = 10);

	/**
	*@brief 获取指定范围内的随机浮点数序列
	*
	*@param aRandomArr [out]	带输出的随机数序列
	*
	*@param nLength [in] 随机数个数
	*
	*@param nLower [in]	下限
	*
	*@param nUpper [in]	上限
	*
	*@return -
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API void getRandomArray(vector<double> &aRandomArr, size_t nLength, double dLower = 0.0, double dUpper = 1.0);

	/**
	*@brief 获取整数数组指定范围内的中值
	*
	*@param m [out]	待返回的中值
	*
	*@param pArr [in] 数组指针
	*
	*@param begin [in]	起始位置
	*
	*@param end [in]	终止位置
	*
	*@return -成功则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool getMedian(int &m, int *pArr, int begin, int end);

	/**
	*@brief 获取浮点数组指定范围内的中值
	*
	*@param m [out]	待返回的中值
	*
	*@param pArr [in] 数组指针
	*
	*@param begin [in]	起始位置
	*
	*@param end [in]	终止位置
	*
	*@return -成功则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool getMedian(double &m, double *pArr, int begin, int end);

	/**
	*@brief 将浮点数组排序
	*
	*@param pArr [in/out] 数组指针
	*
	*@param n [in]	数组长度
	*
	*@param bAscending [in]	是否按升序进行排序
	*
	*@param pIndex [in/out]	指标数组指针。如果不为空（nullptr），则该指标数组存储了排序后的数组中
	*                       每个元素对应的旧的下标。例如pIndex[0]等于3，则表示排序前的第3个元素变成
	*						了排序后的第0个元素。
	*
	*@return -成功则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool sort(double *pArr, int n, bool bAscending = true, int *pIndex = nullptr);

	/**
	*@brief 将整数数组排序
	*
	*@param pArr [in/out] 数组指针
	*
	*@param n [in]	数组长度
	*
	*@param bAscending [in]	是否按升序进行排序
	*
	*@param pIndex [in/out]	指标数组指针。如果不为空（nullptr），则该指标数组存储了排序后的数组中
	*                       每个元素对应的旧的下标。例如pIndex[0]等于3，则表示排序前的第3个元素变成
	*						了排序后的第0个元素。
	*
	*@return -成功则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool sort(int *pArr, int n, bool bAscending = true, int *pIndex = nullptr);

	/**
		*@brief get the mean and standard variance of the data sequence
		*@param data	[in] data sequence
		*@param n		[in] number of data sequence
		*@param mean	[out] mean of data sequence
		*@param std		[out] standard variance of data sequence
		*@return true if everything is OK, else return false
		*@note -
		*@remarks -
		*/
	LIBCORE_API bool getMeanStd(double &mean, double &std, double *data, int n);

	/**
	*@brief normalize the data sequence with (mean, std)
	*@param data	[in/out] data sequence
	*@param n		[in] number of data sequence
	*@param c		[in] mean of data sequence
	*@param s		[in] standard variance of data sequence
	*@return true if everything is OK, else return false
	*@note -
	*@remarks -
	*/
	LIBCORE_API bool normalizeMeanStd(double *data, int n, double *mean=nullptr, double *std=nullptr);

	/**
	*@brief normalize the data sequence to [0, 1]
	*@param data	[in/out] data sequence
	*@param n		[in] number of data sequence
	*@param dMin	[out] pointer to the minimum of data sequence
	*@param dMax	[out] pointer to the maximum of data sequence
	*@return true if everything is OK, else return false
	*@note -
	*@remarks -
	*/
	LIBCORE_API bool normalizeUnit(double *data, int n, double *dMin = nullptr, double *dMax = nullptr);


	//get Gaussian kernel with given std and radius
	//aK is a (2*nRadius+1) * (2*nRadius+1) vector
	LIBCORE_API bool getGaussianKernel(vector<double> &aK, int nRadius, double dSigma = 3.0);

	//get Gaussian kernel with given std,
	//aK is a (2*nRadius+1) * (2*nRadius+1) vector where nRadius will be determined based on std
	LIBCORE_API bool getGaussianKernel(vector<double> &aK, double dSigma = 3.0);

	//Gaussian Smooth with below Kernel:
	//1  2  1
	//2  4  2  
	//1  2  1
	LIBCORE_API bool gaussianSmooth3(unsigned char *pImg, int nWidth, int nPitch, int nHeight, ImageRect *aoi = nullptr);

	//Gaussian Smooth with below Kernel:
	//0  1  2  1  0
	//1  4  8  4  1  
	//2  8  16 8  2
	//1  4  8  4  1
	//0  1  2  1  0
	LIBCORE_API bool gaussianSmooth5(unsigned char *pImg, int nWidth, int nPitch, int nHeight, ImageRect *aoi = nullptr);


	/**
	*@brief 获取图像指定区域的灰度阈值
	*
	*@param pImage [in]		图像内存指针
	*
	*@param nWidth [in]		图像宽度
	*
	*@param nHeight [in]	图像高度
	*
	*@param nPitch [in]		图像字节宽度
	*
	*@param aAOI [in]		感兴趣区域序列
	*
	*@param dA [in]			类间方差计算参数
	*
	*@return 灰度阈值
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API int otsu(unsigned char *pImage, int nWidth, int nHeight, int nPitch, vector<ImageRect> &aAOI, double dA = 1.0);

	/**
	*@brief 将图像指定区域二值化
	*
	*@param pImage [in/out]	图像内存指针
	*
	*@param nWidth [in]		图像宽度
	*
	*@param nHeight [in]	图像高度
	*
	*@param nPitch [in]		图像字节宽度
	*
	*@param aAOI [in]		感兴趣区域序列
	*
	*@param nThreshold [in]	灰度阈值，如果为-1，则表示自适应二值化
	*
	*@return 成功则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool binarization(unsigned char *pImage, int nWidth, int nHeight, int nPitch,
		vector<ImageRect> &aAOI, int nThreshold = -1);

	/**
	*@brief 计算置信区间
	*
	*@param dUpper [out]	置信区间上限
	*
	*@param dLower [out]	置信区间下限
	*
	*@param dAcc [in]		准确性
	*
	*@param nRec [in]		样本数
	*
	*@param nConfidenceLevel [in]	置信水平
	*
	*@return 成功则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool getConfidenceInterval(double &dUpper, double &dLower, double dAcc, int nRec, int nConfidenceLevel = 95);

	/**
	*@brief 以从左至右顺序在字符串中不分大小写寻找指定的子串
	*
	*@param str [in]	待搜索的字符串
	*
	*@param substr [in]	待匹配的字符串
	*
	*@return 成功则返回第一个匹配到的位置，否则返回-1
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API string::size_type findSubStrWithNoCase(string str, string substr);

	/**
	*@brief 获得文件夹中具有指定后缀名的文件列表
	*
	*@param strFileList [out]	待返回的文件列表
	*
	*@param strFolder [in]	待搜索的文件夹名称
	*
	*@param strExt [in]	文件后缀名
	*
	*@return -
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API void getFileList(vector<string> &aFileList, const string &strFolder, const string &sExt="*.*");

	/**
	*@brief 检查文件是否存在
	*
	*@param szFile [in]	待检查的文件名
	*
	*@return -若存在则返回true，否则返回false
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API bool isFileExisted(const char *szFile);

	/**
	*@brief 将指定缓存转成base64格式
	*
	*@param _dst [out]	待输出的base64字节流
	*
	*@param _src [in]	输入缓存
	*
	*@param len [in]	输入缓存长度
	*
	*@param url_encoded [in]	是否以url方式加密，默认为0
	*
	*@return -若存在则返回true，否则返回false
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API size_t base64_encode(char *_dst, const void *_src, size_t len, int url_encoded=0);

	/**
	*@brief 将指定缓存转成base64格式
	*
	*@param _dst [out]	待输出的base64字节缓存
	*
	*@param _src [in]	输入缓存
	*
	*@param len [in]	输入缓存长度
	*
	*@param url_encoded [in]	是否以url方式加密，默认为0
	*
	*@return -若存在则返回true，否则返回false
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API bool base64_encode(Buffer &_dst, const void *_src, size_t len, int url_encoded=0);

	/**
	*@brief 将指定文件转成base64格式
	*
	*@param base64 [out]	待输出的base64字节流
	*
	*@param size [out]	带输出的base64字节流长度
	*
	*@param szFileName [in]	文件名
	*
	*@return -若存在则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool fileToBase64(char *base64, int &size, const char *szFileName);

	/**
	*@brief 将指定文件转成base64格式
	*
	*@param base64 [out]	待输出的base64字节缓存
	*
	*@param szFileName [in]	文件名
	*
	*@return -若存在则返回true，否则返回false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool fileToBase64(Buffer &base64, const char *szFileName);

}

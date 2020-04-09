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
	*@brief ��ȡ��ӽ�������
	*
	*@param x [in]		���븡����
	*
	*@return ���������
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API int round(double x);

	/**
	*@brief ������������ƽ���͵ĸ�������ڼ򵥵�sqrt(a^2+b^2)���ü��㷽������Ч��ֹ�������
	*
	*@param a [in]	���븡����
	*
	*@param b [in]	���븡����
	*
	*@return ��������ƽ����֮��
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API double hypot(double a, double b);


	//LIBCORE_API unsigned calcBPP(EPixelFormat pixFmt);

	//LIBCORE_API unsigned calcImagePitch(unsigned nW, unsigned nBpp);



	/**
	*@brief ��ȡָ����Χ�ڵ������������
	*
	*@param aRandomArr [out]	����������������
	*
	*@param nLength [in] ���������
	*
	*@param nLower [in]	����
	*
	*@param nUpper [in]	����
	*
	*@return -
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API void getRandomArray(vector<int> &aRandomArr, size_t nLength, int nLower = 0, int nUpper = 10);

	/**
	*@brief ��ȡָ����Χ�ڵ��������������
	*
	*@param aRandomArr [out]	����������������
	*
	*@param nLength [in] ���������
	*
	*@param nLower [in]	����
	*
	*@param nUpper [in]	����
	*
	*@return -
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API void getRandomArray(vector<double> &aRandomArr, size_t nLength, double dLower = 0.0, double dUpper = 1.0);

	/**
	*@brief ��ȡ��������ָ����Χ�ڵ���ֵ
	*
	*@param m [out]	�����ص���ֵ
	*
	*@param pArr [in] ����ָ��
	*
	*@param begin [in]	��ʼλ��
	*
	*@param end [in]	��ֹλ��
	*
	*@return -�ɹ��򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool getMedian(int &m, int *pArr, int begin, int end);

	/**
	*@brief ��ȡ��������ָ����Χ�ڵ���ֵ
	*
	*@param m [out]	�����ص���ֵ
	*
	*@param pArr [in] ����ָ��
	*
	*@param begin [in]	��ʼλ��
	*
	*@param end [in]	��ֹλ��
	*
	*@return -�ɹ��򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool getMedian(double &m, double *pArr, int begin, int end);

	/**
	*@brief ��������������
	*
	*@param pArr [in/out] ����ָ��
	*
	*@param n [in]	���鳤��
	*
	*@param bAscending [in]	�Ƿ������������
	*
	*@param pIndex [in/out]	ָ������ָ�롣�����Ϊ�գ�nullptr�������ָ������洢��������������
	*                       ÿ��Ԫ�ض�Ӧ�ľɵ��±ꡣ����pIndex[0]����3�����ʾ����ǰ�ĵ�3��Ԫ�ر��
	*						�������ĵ�0��Ԫ�ء�
	*
	*@return -�ɹ��򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool sort(double *pArr, int n, bool bAscending = true, int *pIndex = nullptr);

	/**
	*@brief ��������������
	*
	*@param pArr [in/out] ����ָ��
	*
	*@param n [in]	���鳤��
	*
	*@param bAscending [in]	�Ƿ������������
	*
	*@param pIndex [in/out]	ָ������ָ�롣�����Ϊ�գ�nullptr�������ָ������洢��������������
	*                       ÿ��Ԫ�ض�Ӧ�ľɵ��±ꡣ����pIndex[0]����3�����ʾ����ǰ�ĵ�3��Ԫ�ر��
	*						�������ĵ�0��Ԫ�ء�
	*
	*@return -�ɹ��򷵻�true�����򷵻�false
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
	*@brief ��ȡͼ��ָ������ĻҶ���ֵ
	*
	*@param pImage [in]		ͼ���ڴ�ָ��
	*
	*@param nWidth [in]		ͼ����
	*
	*@param nHeight [in]	ͼ��߶�
	*
	*@param nPitch [in]		ͼ���ֽڿ��
	*
	*@param aAOI [in]		����Ȥ��������
	*
	*@param dA [in]			��䷽��������
	*
	*@return �Ҷ���ֵ
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API int otsu(unsigned char *pImage, int nWidth, int nHeight, int nPitch, vector<ImageRect> &aAOI, double dA = 1.0);

	/**
	*@brief ��ͼ��ָ�������ֵ��
	*
	*@param pImage [in/out]	ͼ���ڴ�ָ��
	*
	*@param nWidth [in]		ͼ����
	*
	*@param nHeight [in]	ͼ��߶�
	*
	*@param nPitch [in]		ͼ���ֽڿ��
	*
	*@param aAOI [in]		����Ȥ��������
	*
	*@param nThreshold [in]	�Ҷ���ֵ�����Ϊ-1�����ʾ����Ӧ��ֵ��
	*
	*@return �ɹ��򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool binarization(unsigned char *pImage, int nWidth, int nHeight, int nPitch,
		vector<ImageRect> &aAOI, int nThreshold = -1);

	/**
	*@brief ������������
	*
	*@param dUpper [out]	������������
	*
	*@param dLower [out]	������������
	*
	*@param dAcc [in]		׼ȷ��
	*
	*@param nRec [in]		������
	*
	*@param nConfidenceLevel [in]	����ˮƽ
	*
	*@return �ɹ��򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool getConfidenceInterval(double &dUpper, double &dLower, double dAcc, int nRec, int nConfidenceLevel = 95);

	/**
	*@brief �Դ�������˳�����ַ����в��ִ�СдѰ��ָ�����Ӵ�
	*
	*@param str [in]	���������ַ���
	*
	*@param substr [in]	��ƥ����ַ���
	*
	*@return �ɹ��򷵻ص�һ��ƥ�䵽��λ�ã����򷵻�-1
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API string::size_type findSubStrWithNoCase(string str, string substr);

	/**
	*@brief ����ļ����о���ָ����׺�����ļ��б�
	*
	*@param strFileList [out]	�����ص��ļ��б�
	*
	*@param strFolder [in]	���������ļ�������
	*
	*@param strExt [in]	�ļ���׺��
	*
	*@return -
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API void getFileList(vector<string> &aFileList, const string &strFolder, const string &sExt="*.*");

	/**
	*@brief ����ļ��Ƿ����
	*
	*@param szFile [in]	�������ļ���
	*
	*@return -�������򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API bool isFileExisted(const char *szFile);

	/**
	*@brief ��ָ������ת��base64��ʽ
	*
	*@param _dst [out]	�������base64�ֽ���
	*
	*@param _src [in]	���뻺��
	*
	*@param len [in]	���뻺�泤��
	*
	*@param url_encoded [in]	�Ƿ���url��ʽ���ܣ�Ĭ��Ϊ0
	*
	*@return -�������򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API size_t base64_encode(char *_dst, const void *_src, size_t len, int url_encoded=0);

	/**
	*@brief ��ָ������ת��base64��ʽ
	*
	*@param _dst [out]	�������base64�ֽڻ���
	*
	*@param _src [in]	���뻺��
	*
	*@param len [in]	���뻺�泤��
	*
	*@param url_encoded [in]	�Ƿ���url��ʽ���ܣ�Ĭ��Ϊ0
	*
	*@return -�������򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks - 
	*/
	LIBCORE_API bool base64_encode(Buffer &_dst, const void *_src, size_t len, int url_encoded=0);

	/**
	*@brief ��ָ���ļ�ת��base64��ʽ
	*
	*@param base64 [out]	�������base64�ֽ���
	*
	*@param size [out]	�������base64�ֽ�������
	*
	*@param szFileName [in]	�ļ���
	*
	*@return -�������򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool fileToBase64(char *base64, int &size, const char *szFileName);

	/**
	*@brief ��ָ���ļ�ת��base64��ʽ
	*
	*@param base64 [out]	�������base64�ֽڻ���
	*
	*@param szFileName [in]	�ļ���
	*
	*@return -�������򷵻�true�����򷵻�false
	*
	*@note -
	*
	*@remarks -
	*/
	LIBCORE_API bool fileToBase64(Buffer &base64, const char *szFileName);

}

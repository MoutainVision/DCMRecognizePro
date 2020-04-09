#include "Image.h"
#include "Utility.h"
#include<cstring>

#include "Histogram.h"

#include "HeatMap.h"


#if XIMAGE_SUPPORT_DISTORTION_CORRECTION
	#pragma comment(lib,"LibDistortionCorrection.lib")
#endif // XMAGE_SUPPORT_DISTORTION_CORRECTION

#if XIMAGE_SUPPORT_SETTING_IO_XML	
	#pragma comment(lib,"LibTinyXML.lib")
#endif // XIMAGE_SUPPORT_SETTING_IO_XML

namespace avs
{
	void ImageProcessinChainSetting::setSetting(ImageProcessinChainSetting setting)
	{
		byrEnhEnabled = setting.byrEnhEnabled;
		dbyrEnabled = setting.dbyrEnabled;
		dbyrPara.eDstPixFmt = setting.dbyrPara.eDstPixFmt;
		dbyrPara.eDByrMethod = setting.dbyrPara.eDByrMethod;
		bbEnabled = setting.bbEnabled;
		bbFileName = setting.bbFileName;
		wbEnabled = setting.wbEnabled;
		wbPara.method = setting.wbPara.method;
		wbPara.nMaxGray = setting.wbPara.nMaxGray;
		wbPara.dRatio = setting.wbPara.dRatio;
		calcWBEnabled = setting.calcWBEnabled;
		useWBROIEnabled = setting.useWBROIEnabled;
		wbROI.xs = setting.wbROI.xs;
		wbROI.xe = setting.wbROI.xe;
		wbROI.ys = setting.wbROI.ys;
		wbROI.ye = setting.wbROI.ye;
		ptGain.x = setting.ptGain.x;
		ptGain.y = setting.ptGain.y;
		ptGain.z = setting.ptGain.z;
		brightEnhEnabled = setting.brightEnhEnabled;
		brightEnhValue = setting.brightEnhValue;
		contraEnhEnabled = setting.contraEnhEnabled;
		contraEnhValue = setting.contraEnhValue;
		gammaEnhEnabled = setting.gammaEnhEnabled;
		gammaEnhValue = setting.gammaEnhValue;
		histEnhEnabled = setting.histEnhEnabled;
		rgbEnhEnabled = setting.rgbEnhEnabled;
		shpnessEnhEnabled = setting.shpnessEnhEnabled;
		colorEnhEnabled = setting.colorEnhEnabled;

		return;
	}

#if XIMAGE_SUPPORT_SETTING_IO_XML

	void ImageProcessinChainSetting::settingToParamAtt(std::vector<ParamInfo> &vctPAttri)
	{
		ParamInfo pa;
		pa.bSupChild = true;

		strcpy_s(pa.sName, "byrEnhEnabled");
		sprintf_s(pa.sValue, "%d", byrEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "dbyrEnabled");
		sprintf_s(pa.sValue, "%d", dbyrEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "dbyrPara");
		sprintf_s(pa.sValue, "");
		pa.bSupChild = false;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "bbEnabled");
		sprintf_s(pa.sValue, "%d", bbEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "bbFileName");
		sprintf_s(pa.sValue, "%s", bbFileName.c_str());
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "wbEnabled");
		sprintf_s(pa.sValue, "%d", wbEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "wbPara");
		sprintf_s(pa.sValue, "");
		pa.bSupChild = false;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "calcWBEnabled");
		sprintf_s(pa.sValue, "%d", calcWBEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "useWBROIEnabled");
		sprintf_s(pa.sValue, "%d", useWBROIEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "wbROI");
		sprintf_s(pa.sValue, "");
		pa.bSupChild = false;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "ptGain");
		sprintf_s(pa.sValue, "");
		pa.bSupChild = false;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "brightEnhEnabled");
		sprintf_s(pa.sValue, "%d", brightEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "brightEnhValue");
		sprintf_s(pa.sValue, "%d", brightEnhValue);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "contraEnhEnabled");
		sprintf_s(pa.sValue, "%d", contraEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "contraEnhValue");
		sprintf_s(pa.sValue, "%d", contraEnhValue);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "gammaEnhEnabled");
		sprintf_s(pa.sValue, "%d", gammaEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "gammaEnhValue");
		sprintf_s(pa.sValue, "%f", gammaEnhValue);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "histEnhEnabled");
		sprintf_s(pa.sValue, "%d", histEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "rgbEnhEnabled");
		sprintf_s(pa.sValue, "%d", rgbEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "shpnessEnhEnabled");
		sprintf_s(pa.sValue, "%d", shpnessEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "colorEnhEnabled");
		sprintf_s(pa.sValue, "%d", colorEnhEnabled);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		pa.vctParentName.clear();
		pa.vctParentName.push_back("dbyrPara");

		strcpy_s(pa.sName, "eDstPixFmt");
		sprintf_s(pa.sValue, "%d", dbyrPara.eDstPixFmt);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "eDByrMethod");
		sprintf_s(pa.sValue, "%d", dbyrPara.eDByrMethod);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		pa.vctParentName.clear();
		pa.vctParentName.push_back("wbPara");

		strcpy_s(pa.sName, "method");
		sprintf_s(pa.sValue, "%d", wbPara.method);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "nMaxGray");
		sprintf_s(pa.sValue, "%d", wbPara.nMaxGray);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "dRatio");
		sprintf_s(pa.sValue, "%f", wbPara.dRatio);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		pa.vctParentName.clear();
		pa.vctParentName.push_back("wbROI");

		strcpy_s(pa.sName, "xs");
		sprintf_s(pa.sValue, "%d", wbROI.xs);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "xe");
		sprintf_s(pa.sValue, "%d", wbROI.xe);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "ys");
		sprintf_s(pa.sValue, "%d", wbROI.ys);
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "ye");
		sprintf_s(pa.sValue, "%d", wbROI.ye);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		pa.vctParentName.clear();
		pa.vctParentName.push_back("ptGain");

		strcpy_s(pa.sName, "x");
		sprintf_s(pa.sValue, "%f", ptGain.x);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "y");
		sprintf_s(pa.sValue, "%f", ptGain.y);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		strcpy_s(pa.sName, "z");
		sprintf_s(pa.sValue, "%f", ptGain.z);
		pa.bSupChild = true;
		vctPAttri.push_back(pa);

		return;
	}

	void ImageProcessinChainSetting::paramAttToSetting(std::vector<ParamInfo> vctPAttri)
	{
		for (int j = 0; j < (int)vctPAttri.size(); j++)
		{
			std::string name(vctPAttri[j].sName);

			if (vctPAttri[j].vctParentName.size() == 0)
			{
				if (name.compare("byrEnhEnabled") == 0)
				{
					byrEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("dbyrEnabled") == 0)
				{
					dbyrEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("bbEnabled") == 0)
				{
					bbEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("bbFileName") == 0)
				{
					bbFileName = vctPAttri[j].sValue;
				}

				if (name.compare("wbEnabled") == 0)
				{
					wbEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("calcWBEnabled") == 0)
				{
					calcWBEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("useWBROIEnabled") == 0)
				{
					useWBROIEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("brightEnhEnabled") == 0)
				{
					brightEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("brightEnhValue") == 0)
				{
					brightEnhValue = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("contraEnhEnabled") == 0)
				{
					contraEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("contraEnhValue") == 0)
				{
					contraEnhValue = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("gammaEnhEnabled") == 0)
				{
					gammaEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("gammaEnhValue") == 0)
				{
					gammaEnhValue = atof(vctPAttri[j].sValue);
				}

				if (name.compare("histEnhEnabled") == 0)
				{
					histEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("rgbEnhEnabled") == 0)
				{
					rgbEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("shpnessEnhEnabled") == 0)
				{
					shpnessEnhEnabled = atoi(vctPAttri[j].sValue);
				}

				if (name.compare("colorEnhEnabled") == 0)
				{
					colorEnhEnabled = atoi(vctPAttri[j].sValue);
				}
			}

			if (vctPAttri[j].vctParentName.size() == 1)
			{
				if (vctPAttri[j].vctParentName[0].compare("dbyrPara") == 0)
				{
					if (name.compare("eDstPixFmt") == 0)
					{
						dbyrPara.eDstPixFmt = (EPixelFormat)atoi(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("eDByrMethod") == 0)
					{
						dbyrPara.eDByrMethod = (EDebayerMethod)atoi(vctPAttri[j].sValue);
						continue;
					}
				}

				if (vctPAttri[j].vctParentName[0].compare("wbPara") == 0)
				{
					if (name.compare("eDstPixFmt") == 0)
					{
						wbPara.method = (EWBMethod)atoi(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("nMaxGray") == 0)
					{
						wbPara.nMaxGray = atoi(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("dRatio") == 0)
					{
						wbPara.dRatio = atof(vctPAttri[j].sValue);
						continue;
					}
				}

				if (vctPAttri[j].vctParentName[0].compare("wbROI") == 0)
				{
					if (name.compare("xs") == 0)
					{
						wbROI.xs = atoi(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("xe") == 0)
					{
						wbROI.xe = atoi(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("ys") == 0)
					{
						wbROI.ys = atoi(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("ye") == 0)
					{
						wbROI.ye = atoi(vctPAttri[j].sValue);
						continue;
					}
				}

				if (vctPAttri[j].vctParentName[0].compare("ptGain") == 0)
				{
					if (name.compare("x") == 0)
					{
						ptGain.x = atof(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("y") == 0)
					{
						ptGain.y = atof(vctPAttri[j].sValue);
						continue;
					}
					if (name.compare("z") == 0)
					{
						ptGain.z = atof(vctPAttri[j].sValue);
						continue;
					}
				}
			}
		}

		return;
	}
#endif // XIMAGE_SUPPORT_SETTING_IO_XML

	bool ImageProcessinChainSetting::load(const char *szSettingFile, std::string strTypeName)
	{
#if XIMAGE_SUPPORT_SETTING_IO_XML
		std::vector<ParamInfo> vctPAttri;
		if (!readXmlFileVector(vctPAttri, szSettingFile, strTypeName.c_str()))
			return false;

		if (vctPAttri.size() > 0)
		{
			paramAttToSetting(vctPAttri);
			return true;
		}
#endif // XIMAGE_SUPPORT_SETTING_IO_XML

		return false;
	}

	bool ImageProcessinChainSetting::save(const char *szSettingFile, std::string strTypeName)
	{
#if XIMAGE_SUPPORT_SETTING_IO_XML
		std::vector<ParamInfo>	vctPAttri;

		settingToParamAtt(vctPAttri);

		if (vctPAttri.size() > 0)
		{
			return writeXmlFileVector(vctPAttri, szSettingFile, strTypeName.c_str());
		}
#endif // XIMAGE_SUPPORT_SETTING_IO_XML

		return false;
	}

	/////////////////////////////////////////////////////////////////////////////////
	//Begin of implementation of xImage class
	/////////////////////////////////////////////////////////////////////////////////

	string xImage::getSupportedFileFormats()
	{
		string str = "";

#if XIMAGE_SUPPORT_BMP
		str += ".bmp\t";
#endif // XIMAGE_SUPPORT_BMP

#if XIMAGE_SUPPORT_JPG
		str += ".jpg\t";
#endif // XIMAGE_SUPPORT_BMP

#if XIMAGE_SUPPORT_PNG
		str += ".png\t";
#endif // XIMAGE_SUPPORT_BMP

#if XIMAGE_SUPPORT_TIF
		str += ".tif\t";
#endif // XIMAGE_SUPPORT_BMP

#if XIMAGE_SUPPORT_JP2
		str += ".jp2\t";
#endif // XIMAGE_SUPPORT_JP2

#if XIMAGE_SUPPORT_PGX
		str += ".pgx\t";
#endif // XIMAGE_SUPPORT_PGX

#if XIMAGE_SUPPORT_PNM
		str += ".pnm\t";
#endif // XIMAGE_SUPPORT_PNM

#if XIMAGE_SUPPORT_RAW
		str += ".raw\t";
#endif // XIMAGE_SUPPORT_RAW


		return str;
	}

	unsigned xImage::calcBPP(EPixelFormat pixFmt)
	{
		unsigned nBpp = 0;

		switch (pixFmt)
		{
		case PIXEL_FORMAT_MONO8://8 bits of mono information.
			nBpp = 8;
			break;

		case PIXEL_FORMAT_411YUV8:	//YUV 4:1:1. (Y sample at every pixel, U and V sampled 
									//at every fourth pixel horizontally on each line). 
									//A macropixel contains 8 pixels in 3 u_int32s.
									//or with a packed, 6 byte/4 pixel macroblock structure.
			nBpp = 12;
			break;

		case PIXEL_FORMAT_422YUV8:	//YUV 4:2:2. (Y sample at every pixel, U and V sampled at 
									//every second pixel horizontally on each line). 
									//A macropixel contains 2 pixels in 1 u_int32.
			nBpp = 16;
			break;

		case PIXEL_FORMAT_444YUV8: //YUV 4:4:4. 
			nBpp = 24;
			break;

		case PIXEL_FORMAT_MONO16:  //16 bits of mono information. 
			nBpp = 16;
			break;

		case PIXEL_FORMAT_RGB16:   //R = G = B = 16 bits. 
			nBpp = 48;
			break;

		case PIXEL_FORMAT_S_MONO16: //16 bits of signed mono information. 
			nBpp = 16;
			break;

		case PIXEL_FORMAT_S_RGB16: //R = G = B = 16 bits signed. 
			nBpp = 48;
			break;

		case PIXEL_FORMAT_RAW8:    //8 bit raw data output of sensor. 
			nBpp = 8;
			break;

		case PIXEL_FORMAT_RAW16:   //16 bit raw data output of sensor.
			nBpp = 16;
			break;

		case PIXEL_FORMAT_MONO12:  //12 bits of mono information. 
			nBpp = 12;
			break;

		case PIXEL_FORMAT_RAW12:   //12 bit raw data output of sensor. 
			nBpp = 12;
			break;

		case PIXEL_FORMAT_BGR:     //24 bit BGR. 
			nBpp = 24;
			break;

		case PIXEL_FORMAT_BGRU:    //32 bit BGRU. 
			nBpp = 32;
			break;

		case PIXEL_FORMAT_RGB:     //24 bit RGB. 
			nBpp = 24;
			break;

		case PIXEL_FORMAT_RGBU:    //32 bit RGBU. 
			nBpp = 32;
			break;

		case PIXEL_FORMAT_BGR16:   //R = G = B = 16 bits. 
			nBpp = 48;
			break;

		case PIXEL_FORMAT_BGRU16:  //64 bit BGRU. 
			nBpp = 64;
			break;

		case PIXEL_FORMAT_INDEXED_1:
			nBpp = 1;
			break;

		case PIXEL_FORMAT_INDEXED_2:
			nBpp = 2;
			break;
			
		case PIXEL_FORMAT_INDEXED_4:
			nBpp = 4;
			break;

		case PIXEL_FORMAT_INDEXED_8:
			nBpp = 8;
			break;

		default:
			break;

		}

		return nBpp;
	}

	unsigned xImage::calcImagePitch(unsigned nW, unsigned nBpp, bool bAligned)
	{
		if (bAligned)
		{
			return ((nW * nBpp + 31) & ~31) >> 3;
		}
		else
		{
			return (nW*nBpp + 7) / 8;
		}
	}

	/**
	 * Initialize the internal structures
	 */
	void xImage::initialize()
	{
		m_pBuffer = nullptr;
		m_nWidth = 0;
		m_nHeight = 0;
		m_nBpp = 0;
		m_nPitch = 0;
		m_nImgSize = 0;
		m_pixFmt = UNSPECIFIED_PIXEL_FORMAT;
		m_byrFmt = BAYER_FORMAT_UNKNOWN;
		m_bAligned = true;

		m_pPalette = nullptr;
		m_nPalSize = 0;

		//init pointers
		m_pAlpha = nullptr;

		//init structures
		memset(&m_bmpHead, 0, sizeof(BITMAPINFOHEADER));
		memset(&m_extInfo, 0, sizeof(XIMAGEINFO));

		//init default attributes
		int16_t test = 1;
		m_extInfo.bLittleEndianHost = (*((char *)&test) == 1);
		m_extInfo.dwType = XIMAGE_FORMAT_UNKNOWN;
		m_extInfo.fQuality = 90.0f;
		m_extInfo.nAlphaMax = 255;
		m_extInfo.nBkgndIndex = -1;
		m_extInfo.bEnabled = true;
		m_extInfo.nJpegScale = 1;
		setXDPI(XIMAGE_DEFAULT_DPI);
		setYDPI(XIMAGE_DEFAULT_DPI);

		return;
	}

	xImage::xImage(void)
		: m_pBuffer(nullptr)
		, m_nWidth(0)
		, m_nHeight(0)
		, m_nBpp(0)
		, m_nPitch(0)
		, m_nImgSize(0)
		, m_pixFmt(UNSPECIFIED_PIXEL_FORMAT)
		, m_byrFmt(BAYER_FORMAT_UNKNOWN)
		, m_bAligned(true)
		, m_pPalette(nullptr)
		, m_nPalSize(0)
		, m_pAlpha(nullptr)
	{
		memset(&m_bmpHead, 0, sizeof(BITMAPINFOHEADER));
		memset(&m_extInfo, 0, sizeof(XIMAGEINFO));

		//init default attributes
		int16_t test = 1;
		m_extInfo.bLittleEndianHost = (*((char *)&test) == 1);
		m_extInfo.dwType = XIMAGE_FORMAT_UNKNOWN;
		m_extInfo.fQuality = 90.0f;
		m_extInfo.nAlphaMax = 255;
		m_extInfo.nBkgndIndex = -1;
		m_extInfo.bEnabled = true;
		m_extInfo.nJpegScale = 1;
		setXDPI(XIMAGE_DEFAULT_DPI);
		setYDPI(XIMAGE_DEFAULT_DPI);
	}

	xImage::xImage(EImageFormat fmt)
	{
		initialize();
		m_extInfo.dwType = fmt;
	}

	xImage::xImage(const char *szImgFile)
		: m_pBuffer(nullptr)
		, m_nWidth(0)
		, m_nHeight(0)
		, m_nBpp(0)
		, m_nPitch(0)
		, m_nImgSize(0)
		, m_pixFmt(UNSPECIFIED_PIXEL_FORMAT)
		, m_byrFmt(BAYER_FORMAT_UNKNOWN)
		, m_bAligned(true)
		, m_pPalette(nullptr)
		, m_nPalSize(0)
		, m_pAlpha(nullptr)
	{
		memset(&m_bmpHead, 0, sizeof(BITMAPINFOHEADER));
		memset(&m_extInfo, 0, sizeof(XIMAGEINFO));

		int16_t test = 1;
		m_extInfo.bLittleEndianHost = (*((char *)&test) == 1);
		m_extInfo.dwType = XIMAGE_FORMAT_UNKNOWN;
		m_extInfo.fQuality = 90.0f;
		m_extInfo.nAlphaMax = 255;
		m_extInfo.nBkgndIndex = -1;
		m_extInfo.bEnabled = true;
		m_extInfo.nJpegScale = 1;
		setXDPI(XIMAGE_DEFAULT_DPI);
		setYDPI(XIMAGE_DEFAULT_DPI);

		load(szImgFile);
	}

	xImage::xImage(const xImage& img)
	{
		initialize();

		copyFrom(img);
	}

	//xImage::xImage(unsigned nW, unsigned nH, unsigned nBpp, bool bAligned = true)
	//{
	//	
	//}

	xImage::xImage(unsigned nW, unsigned nH, bool bAligned, EPixelFormat pixFmt, EBayerFormat bayFmt, unsigned char ucInitVal)
	{		
		initialize();
		
		create(nW, nH, bAligned, pixFmt, bayFmt, ucInitVal);
	}


	xImage::xImage(const unsigned char *pBuf, unsigned nW, unsigned nH, bool bAligned, EPixelFormat pixFmt, EBayerFormat bayFmt)
	{
		initialize();

		create(pBuf, nW, nH, bAligned, pixFmt, bayFmt);
	}

	void xImage::release()
	{
#if XIMAGE_SUPPORT_ALPHA
		alphaDelete();
#endif
		m_extInfo.pImage = nullptr;
		memset(&m_extInfo, 0, sizeof(XIMAGEINFO));
		memset(&m_bmpHead, 0, sizeof(BITMAPINFOHEADER));
		if (nullptr != m_pPalette)
		{
			delete[]m_pPalette;
			m_pPalette = nullptr;
		}
		m_nPalSize = 0;

		if (nullptr != m_pBuffer)
		{
			delete[]m_pBuffer;
			m_pBuffer = nullptr;
		}
		m_nWidth = m_nHeight = m_nBpp = m_nPitch = m_nImgSize = 0;
		m_pixFmt = UNSPECIFIED_PIXEL_FORMAT;
		m_byrFmt = BAYER_FORMAT_UNKNOWN;
		m_bAligned = true;

		return;
	}

	xImage::~xImage()
	{
		release();
	}
	
	bool xImage::create(unsigned nW, unsigned nH, bool bAligned, EPixelFormat pixFmt, EBayerFormat bayFmt, unsigned char ucInitVal)
	{
		if (nW != m_nWidth || nH != m_nHeight || bAligned != m_bAligned ||
			pixFmt != m_pixFmt || bayFmt != m_byrFmt)
		{
			unsigned nBpp = calcBPP(pixFmt);
			if (nBpp > 0 && nW > 0 && nH > 0)
			{
				bool isBayerImage = false;
				bool isValidFormat = false;
				if (pixFmt == PIXEL_FORMAT_RAW8 || pixFmt == PIXEL_FORMAT_RAW12 || pixFmt == PIXEL_FORMAT_RAW16)
				{
					if (bayFmt == BAYER_FORMAT_BGGR || bayFmt == BAYER_FORMAT_GBRG ||
						bayFmt == BAYER_FORMAT_GRBG || bayFmt == BAYER_FORMAT_RGGB)
					{
						isBayerImage = true;
						isValidFormat = true;
					}
					else
					{
						isValidFormat = false;
					}
				}
				else
				{
					if (bayFmt == BAYER_FORMAT_NONE)
					{
						isValidFormat = true;
					}
				}

				if (isValidFormat)
				{
					unsigned nP = calcImagePitch(nW, nBpp, bAligned);
					unsigned nImgSize = nH * nP;
					unsigned char *pBuf = nullptr;
					if (nullptr != (pBuf = new unsigned char[nImgSize]))
					{
						bool bPaletteOK = true;
						RGBQUAD *pPal = nullptr;
						unsigned nPal = 0;
						if (!isBayerImage && nBpp <= 8)
						{
							nPal = 1 << nBpp;
							if (nullptr == (pPal = new RGBQUAD[nPal]))
							{
								bPaletteOK = false;
							}
							else
							{
								for (unsigned k = 0; k < nPal; k++)
								{
									pPal[k].rgbBlue = pPal[k].rgbGreen = pPal[k].rgbRed = k;
								}
							}
						}

						if (!bPaletteOK)
						{
							delete[]pBuf;
							pBuf = nullptr;
						}
						else
						{
							bool bAlphaOK = true;
							unsigned char *pAlpha = nullptr;
#if XIMAGE_SUPPORT_ALPHA
							if (PIXEL_FORMAT_BGRU == m_pixFmt ||
								PIXEL_FORMAT_BGRU16 == m_pixFmt ||
								PIXEL_FORMAT_RGBU == m_pixFmt)
							{
								if (nullptr == (pAlpha = new unsigned char[nW*nH]))
								{
									bAlphaOK = false;
								}
							}
#endif
							if (!bAlphaOK)
							{
								if (nullptr != pPal)
								{
									delete[]pPal;
									pPal = nullptr;
								}

								delete[]pBuf;
								pBuf = nullptr;
							}
							else
							{
								release();

								initialize();

								m_pBuffer = pBuf;
								memset(m_pBuffer, ucInitVal, nImgSize);
								m_nWidth = nW;
								m_nHeight = nH;
								m_nPitch = nP;
								m_nImgSize = nImgSize;
								m_nBpp = nBpp;
								m_bAligned = bAligned;
								m_pixFmt = pixFmt;
								m_byrFmt = bayFmt;

								m_pPalette = pPal;
								m_nPalSize = nPal;

								m_pAlpha = pAlpha;

								m_extInfo.pImage = m_pBuffer;
								m_extInfo.dwEffWidth = nP;
								m_extInfo.dwType = XIMAGE_FORMAT_UNKNOWN;

								// initialize BITMAPINFOHEADER
								m_bmpHead.biSize = sizeof(BITMAPINFOHEADER); //<ralphw>
								m_bmpHead.biWidth = nW;		// fill in width from parameter
								m_bmpHead.biHeight = nH;	// fill in height from parameter
								m_bmpHead.biPlanes = 1;			// must be 1
								m_bmpHead.biBitCount = nBpp;	// from parameter
								m_bmpHead.biCompression = 0;	//0==BI_RGB
								m_bmpHead.biSizeImage = nImgSize;
								m_bmpHead.biClrUsed = nPal;

								return true;
							}//AlphaOK
						}//PaletteOK
					}//pBuf!=nullptr
				}//isValidFormat
			}//nBpp>0&&nW>0&&nH>0
		}
		else
		{
			return true;
		}

		return false;
	}

	bool xImage::create(const unsigned char *pBuf, unsigned nW, unsigned nH, bool bAligned, EPixelFormat pixFmt, EBayerFormat byrFmt)
	{
		if (pBuf == m_pBuffer)
		{//identity test
			return true;
		}

		if (create(nW, nH, bAligned, pixFmt, byrFmt))
		{
			if (nullptr != pBuf && nullptr != m_pBuffer)
			{
				memcpy(m_pBuffer, pBuf, m_nImgSize);
			}

			return true;
		}

		return false;
	}

	bool xImage::create(unsigned nWidth, unsigned nHeight, unsigned nBpp, EImageFormat fmt)
	{
		// destroy the existing image (if any)
		destroy();

		// prevent further actions if width or height are not vaild <Balabasnia>
		if ((nWidth == 0) || (nHeight == 0)) 
		{
			//strcpy(m_extInfo.szLastError, "CxImage::Create : width and height must be greater than zero");
			return false;
		}

		// Make sure bits per pixel is valid
		if (nBpp <= 1)	nBpp = 1;
		else if (nBpp <= 4)	nBpp = 4;
		else if (nBpp <= 8)	nBpp = 8;
		else				nBpp = 24;

		unsigned nPitch = ((((nBpp * nWidth) + 31) / 32) * 4);
		size_t nImgSize = nPitch * nHeight;
		unsigned char *pBuf = nullptr;
		if (nullptr == (pBuf = new unsigned char[nImgSize]))
		{
			return false;
		}
		
		// set the correct bpp value

		unsigned nColorUsed;
		switch (nBpp) 
		{
		case 1:
			nColorUsed = 2;
			break;

		case 4:
			nColorUsed = 16; 
			break;

		case 8:
			nColorUsed = 256; 
			break;

		default:
			nColorUsed = 0;
			break;
		}
			   
		RGBQUAD *pPal = nullptr;
		if (nColorUsed > 0)
		{
			if (nullptr == (pPal = new RGBQUAD[nColorUsed]))
			{
				delete[]pBuf;
				
				return false;
			}
			
			memset(pPal, 0, nColorUsed * sizeof(RGBQUAD));
		}

		m_pBuffer  = pBuf;

		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_nPitch = nPitch;
		m_nBpp = nBpp;
		m_nImgSize = nImgSize;
		m_bAligned = true;
		m_byrFmt = BAYER_FORMAT_UNKNOWN;
		m_pixFmt = UNSPECIFIED_PIXEL_FORMAT;

		m_pPalette = pPal;

		//set the common image informations
		int16_t test = 1;
		m_extInfo.bLittleEndianHost = (*((char *)&test) == 1);
		m_extInfo.dwEffWidth = nPitch;
		m_extInfo.dwType = fmt;		
		m_extInfo.pImage = m_pBuffer;
		m_extInfo.fQuality = 90.0f;
		m_extInfo.nAlphaMax = 255;
		m_extInfo.nBkgndIndex = -1;
		m_extInfo.bEnabled = true;
		m_extInfo.nJpegScale = 1;
		setXDPI(XIMAGE_DEFAULT_DPI);
		setYDPI(XIMAGE_DEFAULT_DPI);


		// initialize BITMAPINFOHEADER
		m_bmpHead.biSize = sizeof(BITMAPINFOHEADER); //<ralphw>
		m_bmpHead.biWidth = nWidth;		// fill in width from parameter
		m_bmpHead.biHeight = nHeight;	// fill in height from parameter
		m_bmpHead.biPlanes = 1;			// must be 1
		m_bmpHead.biBitCount = nBpp;	// from parameter
		m_bmpHead.biCompression = 0;	//0==BI_RGB
		m_bmpHead.biSizeImage = nImgSize;
		m_bmpHead.biClrUsed = nColorUsed;
		//    head.biXPelsPerMeter = 0; See SetXDPI
		//    head.biYPelsPerMeter = 0; See SetYDPI
		//    head.biClrImportant = 0;  See SetClrImportant

#if XIMAGE_SUPPORT_ALPHA
		if (m_pAlpha)
		{
			alphaDelete();
		}
#endif //XIMAGE_SUPPORT_ALPHA

		return true;
	}

	void xImage::destroy()
	{
		release();

		return;
	}

	////////////////////////////////////////////////////////////////////////////////
/**
 * Transfers the image from an existing source image. The source becomes empty.
 * \return true if everything is ok
 */
	bool xImage::transfer(xImage &from, bool bTransferFrames /*=true*/)
	{
		destroy();

		memcpy(&m_bmpHead, &from.m_bmpHead, sizeof(BITMAPINFOHEADER));
		memcpy(&m_extInfo, &from.m_extInfo, sizeof(XIMAGEINFO));

		m_pBuffer = from.getBuffer();
		//pSelection = from.pSelection;
#if XIMAGE_SUPPORT_ALPHA
		m_pAlpha = from.getAlpha();
#endif
		//ppLayers = from.ppLayers;

		m_pPalette = from.getPalette();

		//memset(&from.head, 0, sizeof(BITMAPINFOHEADER));
		//memset(&from.info, 0, sizeof(XIMAGEINFO));
		//from.pDib = from.pSelection = from.pAlpha = NULL;
		//from.ppLayers = NULL;

		//if (bTransferFrames) {
		//	DestroyFrames();
		//	ppFrames = from.ppFrames;
		//	from.ppFrames = NULL;
		//}

		return true;
	}


	unsigned xImage::getCodecOption(EImageFormat fmt)
	{
		return m_extInfo.dwCodecOpt[getImageFormatIndex(fmt)];
	}
	bool xImage::setCodecOption(unsigned opt, EImageFormat fmt)
	{
		m_extInfo.dwCodecOpt[getImageFormatIndex(fmt)] = opt;
		return true;
	}


	bool xImage::copyData(const unsigned char *pBuf, unsigned nBufSize)
	{
		if (m_pBuffer == pBuf)
		{
			return true;
		}

		if (nullptr == m_pBuffer || nullptr == pBuf || nBufSize != m_nImgSize)
		{
			return false;
		}

		memcpy(m_pBuffer, pBuf, m_nImgSize * sizeof(unsigned char));

		return true;
	}


	bool xImage::copyData(int xdst, int ydst, xImage &srcImg, int xsrc, int ysrc, int cx, int cy)
	{
		if (!isValid() || !srcImg.isValid())
		{
			return false;
		}

		if (srcImg.getBPP() != getBPP())
		{
			return false;
		}

		int nC = srcImg.getChannels();

		int nPSrc = srcImg.getPitch();
		int nWSrc = srcImg.getWidth();
		int nHSrc = srcImg.getHeight();

		if (0 > cx || 0 > cy ||
			0 > xdst || xdst + cx > m_nWidth || 0 > ydst || ydst + cy > m_nHeight ||
			0 > xsrc || xsrc + cx > nWSrc || 0 > ysrc || ysrc + cy > nHSrc)
		{
			return false;
		}

		unsigned char *pImgSrc = srcImg.getBuffer();
		pImgSrc += ysrc * nPSrc + xsrc * nC;

		unsigned char *pImgDst = m_pBuffer + ydst * m_nPitch + xdst * nC;

		unsigned nByte = cx * nC * sizeof(unsigned char);

		for (int y = 0; y < cy; y++)
		{
			memcpy(pImgDst, pImgSrc, nByte);

			pImgSrc += nPSrc;

			pImgDst += m_nPitch;
		}

		return true;
	}

	bool xImage::copyData(int xdst, int ydst, xImage &srcImg, const ImageRect &r)
	{
		return copyData(xdst, ydst, srcImg, r.xs, r.ys, r.xe-r.xs+1, r.ye-r.ys+1);
	}

	inline bool xImage::isValid()
	{
		return (nullptr != m_pBuffer && m_nImgSize > 0);
	}

	const inline bool xImage::isValid() const
	{
		return (nullptr != m_pBuffer && m_nImgSize > 0);
	}

	inline unsigned char* xImage::getScanLine(unsigned y)
	{
		if (nullptr == m_pBuffer || y >= m_nHeight)
		{
			return nullptr;
		}

		return m_pBuffer + y * m_nPitch;
	}
	const inline unsigned char* xImage::getScanLine(unsigned y) const
	{
		if (nullptr == m_pBuffer || y >= m_nHeight)
		{
			return nullptr;
		}

		return m_pBuffer + y * m_nPitch;
	}

	inline unsigned char* xImage::getBuffer()
	{
		return m_pBuffer;
	}
	const inline unsigned char* xImage::getBuffer() const
	{
		return m_pBuffer;
	}

	inline unsigned xImage::getWidth()
	{
		return m_nWidth;
	}
	const inline unsigned xImage::getWidth() const
	{
		return m_nWidth;
	}

	inline unsigned xImage::getHeight()
	{
		return m_nHeight;
	}
	const inline unsigned xImage::getHeight() const
	{
		return m_nHeight;
	}

	const inline unsigned xImage::getBPP() const
	{
		return m_nBpp;
	}
	inline unsigned xImage::getBPP()
	{
		return m_nBpp;
	}

	inline unsigned xImage::getChannels()
	{
		return m_nBpp / 8;
	}

	const inline unsigned xImage::getChannels() const
	{
		return m_nBpp / 8;
	}

	inline unsigned xImage::getPitch()
	{
		return m_nPitch;
	}
	const inline unsigned xImage::getPitch() const
	{
		return m_nPitch;
	}

	inline unsigned xImage::getImageSize()
	{
		return m_nImgSize;
	}
	const inline unsigned xImage::getImageSize() const
	{
		return m_nImgSize;
	}

	inline EPixelFormat xImage::getPixelFormat()
	{
		return m_pixFmt;
	}
	const inline EPixelFormat xImage::getPixelFormat() const
	{
		return m_pixFmt;
	}

	inline EBayerFormat xImage::getBayerFormat()
	{
		return m_byrFmt;
	}
	const inline EBayerFormat xImage::getBayerFormat() const
	{
		return m_byrFmt;
	}

	inline bool xImage::getAlignment()
	{
		return m_bAligned;
	}
	const inline bool xImage::getAlignment() const
	{
		return m_bAligned;
	}

	inline bool xImage::isGrayscale()
	{
		return (m_pixFmt == PIXEL_FORMAT_MONO8 || m_pixFmt == PIXEL_FORMAT_MONO12 || m_pixFmt == PIXEL_FORMAT_MONO16);
	}

	inline bool xImage::isBGR()
	{
		return (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU || m_pixFmt == PIXEL_FORMAT_BGR16 || m_pixFmt == PIXEL_FORMAT_BGRU16);
	}
	const inline bool xImage::isBGR() const
	{
		return (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU || m_pixFmt == PIXEL_FORMAT_BGR16 || m_pixFmt == PIXEL_FORMAT_BGRU16);
	}

	inline bool xImage::isRGB()
	{
		return (m_pixFmt == PIXEL_FORMAT_RGB8 || m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU || m_pixFmt == PIXEL_FORMAT_RGB16);
	}
	const inline bool xImage::isRGB() const
	{
		return (m_pixFmt == PIXEL_FORMAT_RGB8 || m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU || m_pixFmt == PIXEL_FORMAT_RGB16);
	}

	bool xImage::isInside(int x, int y)
	{
		return (0 <= y && y < m_nHeight && 0 <= x && x < m_nWidth);
	}


	bool xImage::copyFrom(const xImage& srcImg)
	{
		unsigned nImgSize = srcImg.getImageSize();
		if (0 == nImgSize && nullptr != srcImg.getBuffer())
		{
			return false;
		}

		unsigned nClrUsed = srcImg.getPaletteItemCount();
		if (0 == nClrUsed && nullptr != srcImg.getPalette())
		{
			return false;
		}

		unsigned nWidth = srcImg.getWidth();
		unsigned nHeight = srcImg.getHeight();
#if XIMAGE_SUPPORT_ALPHA
		if ((0 == nWidth || 0 == nHeight) && nullptr != srcImg.getAlpha())
		{
			return false;
		}
#endif

		bool bNewBufferNeeded = false;
		unsigned char *pBuffer = nullptr;		
		if (m_nImgSize != nImgSize)
		{
			bNewBufferNeeded = true;

			if (nImgSize > 0 && nullptr != srcImg.getBuffer())
			{
				pBuffer = new unsigned char[nImgSize];
				if (nullptr == pBuffer)
				{
					return false;
				}
				memcpy(pBuffer, srcImg.getBuffer(), nImgSize);
			}
		}
		else
		{
			if (nullptr == m_pBuffer)
			{
				if (nImgSize > 0 && nullptr != srcImg.getBuffer())
				{
					pBuffer = new unsigned char[nImgSize];
					if (nullptr == pBuffer)
					{						
						return false;
					}
				}
			}
		}

		bool bNewPaletteNeeded = false;
		RGBQUAD *pPal = nullptr;
		if (m_bmpHead.biClrUsed != nClrUsed)
		{
			bNewBufferNeeded = true;

			if (nClrUsed > 0 && nullptr != srcImg.getPalette())
			{
				pPal = new RGBQUAD[nClrUsed];
				if (nullptr == pPal)
				{
					if (nullptr != pBuffer)
					{
						delete[]pBuffer;
					}

					return false;
				}
				memcpy(pPal, srcImg.getPalette(), nClrUsed * sizeof(RGBQUAD));
			}
		}
		else
		{
			if (nullptr == m_pPalette)
			{
				if (nClrUsed > 0 && nullptr != srcImg.getPalette())
				{
					pPal = new RGBQUAD[nClrUsed];
					if (nullptr == pPal)
					{
						if (nullptr != pBuffer)
						{
							delete[]pBuffer;
						}

						return false;
					}
				}
			}
		}

#if XIMAGE_SUPPORT_ALPHA
		bool bNewAlphaNeeded = false;
		unsigned char *pAlpha = nullptr;
		if (m_nWidth != nWidth || m_nHeight != nHeight)
		{
			bNewAlphaNeeded = true;

			if (nWidth > 0 && nHeight > 0 && nullptr != srcImg.getAlpha())
			{
				pAlpha = new unsigned char[nWidth*nHeight];
				if (nullptr == pAlpha)
				{
					if (nullptr != pBuffer)
					{
						delete[]pBuffer;
					}
					if (nullptr != pPal)
					{
						delete[]pPal;
					}

					return false;
				}
				memcpy(pAlpha, srcImg.getAlpha(), nWidth*nHeight);
			}
		}
		else
		{
			if (nullptr == m_pAlpha)
			{
				if (nWidth > 0 && nHeight > 0 && nullptr != srcImg.getAlpha())
				{
					pAlpha = new unsigned char[nWidth*nHeight];
					if (nullptr == pAlpha)
					{
						if (nullptr != pBuffer)
						{
							delete[]pBuffer;
						}
						if (nullptr != pPal)
						{
							delete[]pPal;
						}

						return false;
					}
				}
			}
		}
#endif

		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		if (bNewBufferNeeded)
		{
			if (nullptr != m_pBuffer)
			{
				delete[]m_pBuffer;
			}
			m_pBuffer = pBuffer;
		}
		else
		{
			if (nullptr == m_pBuffer)
			{
				if (nullptr != pBuffer)
				{
					memcpy(pBuffer, srcImg.getBuffer(), nImgSize);
					m_pBuffer = pBuffer;
				}
			}
			else
			{
				if (nullptr == srcImg.getBuffer())
				{
					delete[]m_pBuffer;
					m_pBuffer = nullptr;
				}
				else
				{
					memcpy(m_pBuffer, srcImg.getBuffer(), nImgSize);
				}
			}
		}
		m_nImgSize = nImgSize;
			   
		////////////////////////////////////////////////////////////////////////////////////
		if (bNewPaletteNeeded)
		{
			if (nullptr != m_pPalette)
			{
				delete[]m_pPalette;
			}
			m_pPalette = pPal;
		}
		else
		{
			if (nullptr == m_pPalette)
			{
				if (nullptr != pPal)
				{
					memcpy(pPal, srcImg.getPalette(), nClrUsed * sizeof(RGBQUAD));
					m_pPalette = pPal;
				}
			}
			else
			{
				if (nullptr == srcImg.getPalette())
				{
					delete[]m_pPalette;
					m_pPalette = nullptr;
				}
				else
				{
					memcpy(m_pPalette, srcImg.getPalette(), nClrUsed * sizeof(RGBQUAD));
				}
			}
		}
		m_bmpHead.biClrUsed = nClrUsed;

#if XIMAGE_SUPPORT_ALPHA
		////////////////////////////////////////////////////////////////////////////////////
		if (bNewAlphaNeeded)
		{
			if (nullptr != m_pAlpha)
			{
				delete[]m_pAlpha;
			}
			m_pAlpha = pAlpha;
		}
		else
		{
			if (nullptr == m_pAlpha)
			{
				if (nullptr != pAlpha)
				{
					memcpy(pAlpha, srcImg.getAlpha(), nWidth * nHeight * sizeof(unsigned char));
					m_pAlpha = pAlpha;
				}
			}
			else
			{
				if (nullptr == srcImg.getAlpha())
				{
					delete[]m_pAlpha;
					m_pAlpha = nullptr;
				}
				else
				{
					memcpy(m_pAlpha, srcImg.getAlpha(), nWidth * nHeight * sizeof(unsigned char));
				}
			}
		}
#endif

		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_nPitch = srcImg.getPitch();
		m_nBpp = srcImg.getBPP();
		m_bAligned = srcImg.getAlignment();
		m_byrFmt = srcImg.getBayerFormat();
		m_pixFmt = srcImg.getPixelFormat();

		memcpy(&m_bmpHead, &srcImg.m_bmpHead, sizeof(BITMAPINFOHEADER));

		memcpy(&m_extInfo, &srcImg.m_extInfo, sizeof(XIMAGEINFO));
		m_extInfo.pImage = m_pBuffer;

		return true;
	}

	bool xImage::copyTo(xImage& dstImg)
	{
		return dstImg.copyFrom(*this);
	}

	bool xImage::swap(xImage *pDstImg)
	{
		if (isValid() && (isRGB() || isBGR()))
		{
			if (m_pixFmt == PIXEL_FORMAT_BGR16 ||
				m_pixFmt == PIXEL_FORMAT_RGB16 ||
				m_pixFmt == PIXEL_FORMAT_BGRU16)
			{
				//not supported yet...
				return false;
			}

			unsigned nC = getChannels();

			if (nullptr == pDstImg)
			{
				unsigned pos = 0;
				for (unsigned y = 0; y < m_nHeight; y++)
				{
					unsigned posx = pos;
					for (unsigned x = 0; x < m_nWidth; x++)
					{
						unsigned char c = m_pBuffer[posx];
						m_pBuffer[posx] = m_pBuffer[posx + 2];
						m_pBuffer[posx + 2] = c;

						posx += nC;
					}

					pos += m_nPitch;
				}

				switch (m_pixFmt)
				{
				case PIXEL_FORMAT_RGB:
					m_pixFmt = PIXEL_FORMAT_BGR;
					break;

				case PIXEL_FORMAT_RGBU:
					m_pixFmt = PIXEL_FORMAT_BGRU;
					break;

				case PIXEL_FORMAT_BGR:
					m_pixFmt = PIXEL_FORMAT_RGB;
					break;

				case PIXEL_FORMAT_BGRU:
					m_pixFmt = PIXEL_FORMAT_RGBU;
					break;
				}

				return true;
			}
			else
			{
				EPixelFormat dstPixFmt;
				switch (m_pixFmt)
				{
				case PIXEL_FORMAT_RGB:
					dstPixFmt = PIXEL_FORMAT_BGR;
					break;

				case PIXEL_FORMAT_RGBU:
					dstPixFmt = PIXEL_FORMAT_BGRU;
					break;

				case PIXEL_FORMAT_BGR:
					dstPixFmt = PIXEL_FORMAT_RGB;
					break;

				case PIXEL_FORMAT_BGRU:
					dstPixFmt = PIXEL_FORMAT_RGBU;
					break;
				}

				if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pBuf = pDstImg->getBuffer();

				unsigned pos = 0;
				for (unsigned y = 0; y < m_nHeight; y++)
				{
					unsigned posx = pos;
					for (unsigned x = 0; x < m_nWidth; x++)
					{
						pBuf[posx]	 = m_pBuffer[posx+2];
						pBuf[posx+1] = m_pBuffer[posx+1];
						pBuf[posx+2] = m_pBuffer[posx];

						posx += nC;
					}

					pos += m_nPitch;
				}

				return true;
			}
		}

		return false;
	}

	bool xImage::swapUG(xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (m_pixFmt != PIXEL_FORMAT_BGR && m_pixFmt != PIXEL_FORMAT_RGB)
		{
			return false;
		}

		EPixelFormat dstPixFmt;
		if (m_pixFmt == PIXEL_FORMAT_BGR)
		{
			dstPixFmt = PIXEL_FORMAT_RGBU;
		}
		else//== PIXEL_FORMAT_RGB
		{
			dstPixFmt = PIXEL_FORMAT_BGRU;
		}

		unsigned char *pBufSrc = m_pBuffer;
		unsigned nCSrc = getChannels();
		unsigned nPSrc = m_nPitch;

		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned char *pBufDst = pDstImg->getBuffer();
			unsigned nCDst = pDstImg->getChannels();
			unsigned nPDst = pDstImg->getPitch();
			
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned posSrc = 0;
				unsigned posDst = 0;

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pBufDst[posDst]		= pBufSrc[posSrc + 2];
					pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
					pBufDst[posDst + 2] = pBufSrc[posSrc];

					posSrc += nCSrc;
					posDst += nCDst;
				}

				pBufSrc += nPSrc;
				pBufDst += nPDst;
			}

			return true;
		}

		xImage dstImg(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE);
		if (!dstImg.isValid())
		{
			return false;
		}

		unsigned char *pBufDst = dstImg.getBuffer();
		unsigned nCDst = dstImg.getChannels();
		unsigned nPDst = dstImg.getPitch();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned posSrc = 0;
			unsigned posDst = 0;

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				pBufDst[posDst] = pBufSrc[posSrc + 2];
				pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
				pBufDst[posDst + 2] = pBufSrc[posSrc];

				posSrc += nCSrc;
				posDst += nCDst;
			}

			pBufSrc += nPSrc;
			pBufDst += nPDst;
		}

		return copyFrom(dstImg);
	}

	bool xImage::swapDG(xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (m_pixFmt != PIXEL_FORMAT_BGRU && m_pixFmt != PIXEL_FORMAT_RGBU)
		{
			return false;
		}

		EPixelFormat dstPixFmt;
		if (m_pixFmt == PIXEL_FORMAT_BGRU)
		{
			dstPixFmt = PIXEL_FORMAT_RGB;
		}
		else//== PIXEL_FORMAT_RGBU
		{
			dstPixFmt = PIXEL_FORMAT_BGR;
		}

		unsigned char *pBufSrc = m_pBuffer;
		unsigned nCSrc = getChannels();
		unsigned nPSrc = m_nPitch;

		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned char *pBufDst = pDstImg->getBuffer();
			unsigned nCDst = pDstImg->getChannels();
			unsigned nPDst = pDstImg->getPitch();
			
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned posSrc = 0;
				unsigned posDst = 0;

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pBufDst[posDst]		= pBufSrc[posSrc + 2];
					pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
					pBufDst[posDst + 2] = pBufSrc[posSrc];

					posSrc += nCSrc;
					posDst += nCDst;
				}

				pBufSrc += nPSrc;
				pBufDst += nPDst;
			}

			return true;
		}

		xImage dstImg(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE);
		if (!dstImg.isValid())
		{
			return false;
		}

		unsigned char *pBufDst = dstImg.getBuffer();
		unsigned nCDst = dstImg.getChannels();
		unsigned nPDst = dstImg.getPitch();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned posSrc = 0;
			unsigned posDst = 0;

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				pBufDst[posDst] = pBufSrc[posSrc + 2];
				pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
				pBufDst[posDst + 2] = pBufSrc[posSrc];

				posSrc += nCSrc;
				posDst += nCDst;
			}

			pBufSrc += nPSrc;
			pBufDst += nPDst;
		}

		return copyFrom(dstImg);
	}

	bool xImage::rgb24To32(xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (m_pixFmt != PIXEL_FORMAT_BGR && m_pixFmt != PIXEL_FORMAT_RGB)
		{
			return false;
		}

		EPixelFormat dstPixFmt;
		if (m_pixFmt == PIXEL_FORMAT_BGR)
		{
			dstPixFmt = PIXEL_FORMAT_RGBU;
		}
		else//== PIXEL_FORMAT_RGB
		{
			dstPixFmt = PIXEL_FORMAT_BGRU;
		}

		unsigned char *pBufSrc = m_pBuffer;
		unsigned nCSrc = getChannels();
		unsigned nPSrc = m_nPitch;

		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned char *pBufDst = pDstImg->getBuffer();
			unsigned nCDst = pDstImg->getChannels();
			unsigned nPDst = pDstImg->getPitch();

			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned posSrc = 0;
				unsigned posDst = 0;

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pBufDst[posDst]		= pBufSrc[posSrc];
					pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
					pBufDst[posDst + 2] = pBufSrc[posSrc + 2];

					posSrc += nCSrc;
					posDst += nCDst;
				}

				pBufSrc += nPSrc;
				pBufDst += nPDst;
			}

			return true;
		}

		xImage dstImg(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE);
		if (!dstImg.isValid())
		{
			return false;
		}

		unsigned char *pBufDst = dstImg.getBuffer();
		unsigned nCDst = dstImg.getChannels();
		unsigned nPDst = dstImg.getPitch();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned posSrc = 0;
			unsigned posDst = 0;

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				pBufDst[posDst]		= pBufSrc[posSrc];
				pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
				pBufDst[posDst + 2] = pBufSrc[posSrc + 2];

				posSrc += nCSrc;
				posDst += nCDst;
			}

			pBufSrc += nPSrc;
			pBufDst += nPDst;
		}

		return copyFrom(dstImg);
	}


	bool xImage::rgb32To24(xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (m_pixFmt != PIXEL_FORMAT_BGRU && m_pixFmt != PIXEL_FORMAT_RGBU)
		{
			return false;
		}

		EPixelFormat dstPixFmt;
		if (m_pixFmt == PIXEL_FORMAT_BGRU)
		{
			dstPixFmt = PIXEL_FORMAT_RGB;
		}
		else//== PIXEL_FORMAT_RGBU
		{
			dstPixFmt = PIXEL_FORMAT_BGR;
		}

		unsigned char *pBufSrc = m_pBuffer;
		unsigned nCSrc = getChannels();
		unsigned nPSrc = m_nPitch;

		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned char *pBufDst = pDstImg->getBuffer();
			unsigned nCDst = pDstImg->getChannels();
			unsigned nPDst = pDstImg->getPitch();
			
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned posSrc = 0;
				unsigned posDst = 0;

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pBufDst[posDst]		= pBufSrc[posSrc];
					pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
					pBufDst[posDst + 2] = pBufSrc[posSrc + 2];

					posSrc += nCSrc;
					posDst += nCDst;
				}

				pBufSrc += nPSrc;
				pBufDst += nPDst;
			}

			return true;
		}

		xImage dstImg(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE);
		if (!dstImg.isValid())
		{
			return false;
		}

		unsigned char *pBufDst = dstImg.getBuffer();
		unsigned nCDst = dstImg.getChannels();
		unsigned nPDst = dstImg.getPitch();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned posSrc = 0;
			unsigned posDst = 0;

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				pBufDst[posDst]		= pBufSrc[posSrc];
				pBufDst[posDst + 1] = pBufSrc[posSrc + 1];
				pBufDst[posDst + 2] = pBufSrc[posSrc + 2];

				posSrc += nCSrc;
				posDst += nCDst;
			}

			pBufSrc += nPSrc;
			pBufDst += nPDst;
		}

		return copyFrom(dstImg);
	}


	xImage& xImage::operator=(const xImage &rhs)
	{
		//identity test
		if (this == &rhs)
		{
			return *this;
		}

		copyFrom(rhs);

		//release();

		//m_nWidth	= rhs.getWidth();
		//m_nHeight	= rhs.getHeight();
		//m_nBpp		= rhs.getBPP();
		//m_nPitch	= rhs.getPitch();
		//m_nImgSize	= rhs.getImageSize();
		//m_pixFmt	= rhs.getPixelFormat();
		//m_byrFmt	= rhs.getBayerFormat();
		//m_bAligned	= rhs.getAlignment();
		//	
		//m_pBuffer = nullptr;

		//if (rhs.isValid())
		//{
		//	if (nullptr != (m_pBuffer = new unsigned char[m_nImgSize]))
		//	{
		//		memcpy(m_pBuffer, rhs.getBuffer(), m_nImgSize * sizeof(unsigned char));
		//	}
		//}

		return *this;
	}



	xImage xImage::operator+(const xImage &rhs)
	{
		//identity test
		if (this == &rhs)
		{
			if (isValid())
			{
				xImage img(*this);

				unsigned char *pBuf = img.getBuffer();
				unsigned nImgSz = img.getImageSize();

				for (unsigned k = 0; k < nImgSz; k++)
				{
					int g = 2 * pBuf[k];

					pBuf[k] = (unsigned char)( g > 255 ? 255 : g);
				}

				return xImage(img);
			}
			else
			{
				return xImage();
			}
		}

		if (!rhs.isValid())
		{
			return xImage();
		}

		if (m_nWidth  != rhs.getWidth() ||
			m_nHeight != rhs.getHeight() ||
			m_nBpp    != rhs.getBPP() ||
			m_pixFmt  != rhs.getPixelFormat() ||
			m_byrFmt  != rhs.getBayerFormat())
		{
			return xImage();
		}

		unsigned nPitch	= rhs.getPitch();
		const unsigned char *pBuffer = rhs.getBuffer();

		unsigned nC = getChannels();

		xImage img = *this;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf0 = img.getScanLine(y);
			const unsigned char *pBuf1 = rhs.getScanLine(y);
			
			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					unsigned g0 = pBuf0[x*nC + c];
					unsigned g1 = pBuf1[x*nC + c];

					pBuf0[x*nC + c] = (unsigned char)((g0 + g1) > 255 ? 255 : (g0 + g1));
				}
			}
		}

		return xImage(img);
	}	

	xImage xImage::operator-(const xImage &rhs)
	{
		//identity test
		if (this == &rhs)
		{
			return xImage(m_nWidth, m_nHeight, m_bAligned, m_pixFmt, m_byrFmt, 0);
		}

		if (!rhs.isValid())
		{
			return xImage();
		}

		if (m_nWidth != rhs.getWidth() ||
			m_nHeight != rhs.getHeight() ||
			m_nBpp != rhs.getBPP() ||
			m_pixFmt != rhs.getPixelFormat() ||
			m_byrFmt != rhs.getBayerFormat())
		{
			return xImage();
		}

		unsigned nPitch	= rhs.getPitch();
		const unsigned char *pBuffer = rhs.getBuffer();

		unsigned nC = getChannels();

		xImage img = *this;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf0 = img.getScanLine(y);
			const unsigned char *pBuf1 = rhs.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					unsigned char g0 = pBuf0[x*nC + c];
					unsigned char g1 = pBuf1[x*nC + c];
			
					pBuf0[x*nC + c] = g0 > g1 ? (g0 - g1) : 0;
				}
			}
		}

		return xImage(img);
	}	

	xImage xImage::operator+(int nOffset)
	{
		if (!isValid())
		{
			return xImage();
		}

		unsigned nC = getChannels();

		xImage img = *this;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf = img.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					int g = pBuf[x*nC + c] + nOffset;

					pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
				}
			}
		}

		return xImage(img);
	}

	xImage xImage::operator-(int nOffset)
	{
		if (!isValid())
		{
			return xImage();
		}

		unsigned nC = getChannels();

		xImage img = *this;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf = img.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					int g = pBuf[x*nC + c] - nOffset;

					pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
				}
			}
		}

		return xImage(img);
	}

	xImage xImage::operator*(float fScale)
	{
		if (!isValid())
		{
			return xImage();
		}

		unsigned nC = getChannels();

		xImage img = *this;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf = img.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					float g = pBuf[x*nC + c] * fScale;

					pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
				}
			}
		}

		return xImage(img);
	}

	xImage xImage::operator/(float fScale)
	{
		if (!isValid() || fabs(fScale) < EPSILON)
		{
			return xImage();
		}

		unsigned nC = getChannels();

		xImage img = *this;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf = img.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					float g = pBuf[x*nC + c] / fScale;

					pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
				}
			}
		}

		return xImage(img);
	}

	xImage& xImage::operator+=(const xImage &rhs)
	{
		//identity test
		if (this == &rhs)
		{
			if (isValid())
			{
				for (unsigned k = 0; k < m_nImgSize; k++)
				{
					int g = 2 * m_pBuffer[k];

					m_pBuffer[k] = (unsigned char)(g > 255 ? 255 : g);
				}
			}

			return *this;
		}

		if (!rhs.isValid())
		{
			return *this;
		}

		if (m_nWidth != rhs.getWidth() ||
			m_nHeight != rhs.getHeight() ||
			m_nBpp != rhs.getBPP() ||
			m_pixFmt != rhs.getPixelFormat() ||
			m_byrFmt != rhs.getBayerFormat())
		{
			return *this;
		}

		unsigned nPitch = rhs.getPitch();
		const unsigned char *pBuffer = rhs.getBuffer();

		unsigned nC = getChannels();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf0 = getScanLine(y);
			const unsigned char *pBuf1 = rhs.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					unsigned g0 = pBuf0[x*nC + c];
					unsigned g1 = pBuf1[x*nC + c];

					pBuf0[x*nC + c] = (unsigned char)((g0 + g1) > 255 ? 255 : (g0 + g1));
				}
			}
		}

		return *this;
	}

	xImage& xImage::operator-=(const xImage &rhs)
	{
		//identity test
		if (this == &rhs)
		{
			if (isValid())
			{
				memset(m_pBuffer, 0, m_nImgSize * sizeof(unsigned char));
			}

			return *this;
		}

		if (!rhs.isValid())
		{
			return *this;
		}

		if (m_nWidth != rhs.getWidth() ||
			m_nHeight != rhs.getHeight() ||
			m_nBpp != rhs.getBPP() ||
			m_pixFmt != rhs.getPixelFormat() ||
			m_byrFmt != rhs.getBayerFormat())
		{
			return *this;
		}

		unsigned nPitch	= rhs.getPitch();
		const unsigned char *pBuffer = rhs.getBuffer();

		unsigned nC = getChannels();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned char *pBuf0 = getScanLine(y);
			const unsigned char *pBuf1 = rhs.getScanLine(y);

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					unsigned char g0 = pBuf0[x*nC + c];
					unsigned char g1 = pBuf1[x*nC + c];
			
					pBuf0[x*nC + c] = g0 > g1 ? (g0 - g1) : 0;
				}
			}
		}

		return *this;
	}	

	xImage& xImage::operator+=(int nOffset)
	{
		if (isValid())
		{
			unsigned nC = getChannels();

			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					for (unsigned c = 0; c < nC; c++)
					{
						int g = pBuf[x*nC + c] + nOffset;

						pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
					}
				}
			}
		}

		return *this;
	}	

	xImage& xImage::operator-=(int nOffset)
	{
		if (isValid())
		{
			unsigned nC = getChannels();

			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					for (unsigned c = 0; c < nC; c++)
					{
						int g = pBuf[x*nC + c] - nOffset;

						pBuf[x*nC + c] = (g > 255 ? 255 : (g < 0 ? 0 : g));
					}
				}
			}
		}

		return *this;
	}	

	xImage& xImage::operator*=(float fScale)
	{
		if (isValid())
		{
			unsigned nC = getChannels();

			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					for (unsigned c = 0; c < nC; c++)
					{
						float g = pBuf[x*nC + c] * fScale;

						pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
					}
				}
			}
		}

		return *this;
	}	

	xImage& xImage::operator/=(float fScale)
	{
		if (isValid() && fabs(fScale) > EPSILON)
		{
			unsigned nC = getChannels();

			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					for (unsigned c = 0; c < nC; c++)
					{
						float g = pBuf[x*nC + c] / fScale;

						pBuf[x*nC + c] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
					}
				}
			}
		}

		return *this;
	}	

	bool xImage::debayerGRBG(xImage& desImg, EPixelFormat desPxFmt, EDebayerMethod dm)
	{
		if (!isValid())
		{
			return false;
		}

		if (BAYER_FORMAT_GRBG != m_byrFmt)
		{
			return false;
		}

		int CHANNEL_R;
		int CHANNEL_G;
		int CHANNEL_B;

		if (desPxFmt == PIXEL_FORMAT_RGB || desPxFmt == PIXEL_FORMAT_RGBU)
		{
			CHANNEL_R = 0;
			CHANNEL_G = 1;
			CHANNEL_B = 2;
		}
		else if (desPxFmt == PIXEL_FORMAT_BGR || desPxFmt == PIXEL_FORMAT_BGRU)
		{
			CHANNEL_R = 2;
			CHANNEL_G = 1;
			CHANNEL_B = 0;
		}
		else
		{
			return false;
		}

		unsigned nWidth = m_nWidth;
		unsigned nHeight = m_nHeight;
		unsigned nScanWidth = m_nPitch;
		unsigned char *pImg = m_pBuffer;

		if (dm == DEBAYER_AVERAGE)
		{
			if (!desImg.create(nWidth, nHeight, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			//the central region with row from 1 to nHeight-1 and column from 1 to nWidth-1
			unsigned pitch = desImg.getPitch();
			unsigned char *pNewImg = desImg.getBuffer();
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[CHANNEL_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
					pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 3;
					pix[CHANNEL_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[CHANNEL_R] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
					pix[CHANNEL_B] = pImg[pos];
					pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;
				}
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[CHANNEL_R] = pImg[pos];
					pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;
					pix[CHANNEL_B] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[CHANNEL_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
					pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 3;
					pix[CHANNEL_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				}
			}

			//the first row, with column from 0 to nWidth-1
			unsigned char *pixel = desImg.getScanLine(0);
			pixel[CHANNEL_R] = pImg[1];
			pixel[CHANNEL_G] = (4 * pImg[0] + pImg[nScanWidth + 1]) / 5;
			pixel[CHANNEL_B] = pImg[nScanWidth];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = pImg[pos];
				pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos + nScanWidth]) / 3;
				pix[CHANNEL_B] = (pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 1;
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) / 6;
				pix[CHANNEL_B] = pImg[pos + nScanWidth];
			}
			unsigned pos = nWidth - 1;
			unsigned char *pix = pixel + 3 * (nWidth - 1);
			pix[CHANNEL_R] = pImg[pos];
			pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + nScanWidth]) >> 1;
			pix[CHANNEL_B] = pImg[pos + nScanWidth - 1];



			//the last row, with column from 0 to nWidth-1
			pixel = desImg.getScanLine(nHeight - 1);
			pos = (nHeight - 1) * nScanWidth;
			pixel[CHANNEL_R] = pImg[pos - nScanWidth + 1];
			pixel[CHANNEL_G] = (pImg[pos + 1] + pImg[pos - nScanWidth]) >> 1;
			pixel[CHANNEL_B] = pImg[pos];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = pImg[pos - nScanWidth];
				pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) / 6;
				pix[CHANNEL_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) >> 1;
				pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth]) / 3;
				pix[CHANNEL_B] = pImg[pos];
			}
			pos = (nHeight - 1) * nScanWidth + nWidth - 1;
			pix = pixel + 3 * (nWidth - 1);
			pix[CHANNEL_R] = pImg[pos - nScanWidth];
			pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1]) / 5;
			pix[CHANNEL_B] = pImg[pos - 1];

			//the first column, with row from 1 to nHeitht-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y);

				pixel[CHANNEL_R] = (pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) >> 1;
				pixel[CHANNEL_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos + 1]) / 3;
				pixel[CHANNEL_B] = pImg[pos];
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y);

				pixel[CHANNEL_R] = pImg[pos + 1];
				pixel[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) / 6;
				pixel[CHANNEL_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
			}

			//the last column, with row from 1 to nHeitht-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[CHANNEL_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				pixel[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) / 6;
				pixel[CHANNEL_B] = pImg[pos - 1];
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[CHANNEL_R] = pImg[pos];
				pixel[CHANNEL_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos - 1]) / 3;
				pixel[CHANNEL_B] = (pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 1;
			}


			return true;
		}

		else if (dm == DEBAYER_BINNING)
		{
			desImg.create(nWidth / 2, nHeight / 2, m_bAligned, desPxFmt, BAYER_FORMAT_NONE);

			for (unsigned y = 0; y < nHeight; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y / 2);
				for (unsigned x = 0; x < nWidth; x += 2)
				{
					unsigned char *pix = pixel + 3 * (x / 2);
					unsigned pos = y * nScanWidth + x;

					pix[CHANNEL_R] = pImg[pos + 1];

					pix[CHANNEL_G] = (pImg[pos] + pImg[pos + nScanWidth + 1]) >> 1;

					pix[CHANNEL_B] = pImg[pos + nScanWidth];
				}
			}

			return true;
		}

		else if (dm == DEBAYER_HQLI)
		{
			if (debayerHQLinear(desImg, 1, 0, desPxFmt))
				return true;
		}
		else if (dm == DEBAYER_BILINEAR)
		{
			return false;
		}

		return false;
	}

	bool xImage::debayerRGGB(xImage& desImg, EPixelFormat desPxFmt, EDebayerMethod dm)
	{
		if (!isValid())
		{
			return false;
		}

		if (BAYER_FORMAT_RGGB != m_byrFmt)
		{
			return false;
		}

		unsigned nChannel_R = 0;
		unsigned nChannel_G = 1;
		unsigned nChannel_B = 2;

		if (desPxFmt == PIXEL_FORMAT_RGB || desPxFmt == PIXEL_FORMAT_RGBU)
		{
			nChannel_R = 0;
			nChannel_G = 1;
			nChannel_B = 2;
		}
		else if (desPxFmt == PIXEL_FORMAT_BGR || desPxFmt == PIXEL_FORMAT_BGRU)
		{
			nChannel_R = 2;
			nChannel_G = 1;
			nChannel_B = 0;
		}
		else
		{
			return false;
		}

		unsigned nWidth = m_nWidth;
		unsigned nHeight = m_nHeight;
		unsigned nScanWidth = m_nPitch;
		unsigned char *pImg = m_pBuffer;

		if (dm == DEBAYER_AVERAGE)
		{
			//the central region with row from 1 to nHeight-2 and column from 1 to nWidth-2
			if (!desImg.create(nWidth, nHeight, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned pitch = desImg.getPitch();
			unsigned char *pNewImg = desImg.getBuffer();
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
					pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;
					pix[nChannel_B] = pImg[pos];
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
					pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) >> 3;
					pix[nChannel_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				}
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
					pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) >> 3;
					pix[nChannel_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = pImg[pos];
					pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;
					pix[nChannel_B] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
				}
			}

			//the first row, with cloumn from 0 to nWidth-1
			unsigned char *pixel = desImg.getScanLine(0);
			pixel[nChannel_R] = pImg[0];
			pixel[nChannel_G] = (pImg[1] + pImg[nScanWidth]) >> 1;
			pixel[nChannel_B] = pImg[nScanWidth + 1];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				pix[nChannel_G] = (4 * pImg[pos] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) / 6;
				pix[nChannel_B] = pImg[pos + nScanWidth];
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = pImg[pos];
				pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos + nScanWidth]) / 3;
				pix[nChannel_B] = (pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 1;
			}
			unsigned pos = nWidth - 1;
			unsigned char *pix = pixel + 3 * (nWidth - 1);
			pix[nChannel_R] = pImg[pos - 1];
			pix[nChannel_G] = (4 * pImg[pos] + pImg[pos + nScanWidth - 1]) / 5;
			pix[nChannel_B] = pImg[pos + nScanWidth];

			//the last row, with column from 0 to nWidth-1
			pixel = (unsigned char*)desImg.getScanLine(nHeight - 1);
			pos = (nHeight - 1) * nScanWidth;
			pixel[nChannel_R] = pImg[pos - nScanWidth];
			pixel[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1]) / 5;
			pixel[nChannel_B] = pImg[pos + 1];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) >> 1;
				pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth]) / 3;
				pix[nChannel_B] = pImg[pos];
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = pImg[pos - nScanWidth];
				pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) / 6;
				pix[nChannel_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
			}
			pos = (nHeight - 1) * nScanWidth + nWidth - 1;
			pix = pixel + 3 * (nWidth - 1);
			pix[nChannel_R] = pImg[pos - nScanWidth - 1];
			pix[nChannel_G] = (pImg[pos - 1] + pImg[pos - nScanWidth]) >> 1;
			pix[nChannel_B] = pImg[pos];

			//the first column, with row from 1 to nHeight-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y);

				pixel[nChannel_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				pixel[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) / 6;
				pixel[nChannel_B] = pImg[pos + 1];
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y);

				pixel[nChannel_R] = pImg[pos];
				pixel[nChannel_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos + 1]) / 3;
				pixel[nChannel_B] = (pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) >> 1;
			}

			//the last column, with row from 1 to nHeight-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[nChannel_R] = (pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 1;
				pixel[nChannel_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos - 1]) / 3;
				pixel[nChannel_B] = pImg[pos];
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = (unsigned char*)desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[nChannel_R] = pImg[pos - 1];
				pixel[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) / 6;
				pixel[nChannel_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
			}


			return true;
		}

		else if (dm == DEBAYER_BINNING)
		{
			if (!desImg.create(nWidth / 2, nHeight / 2, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			for (unsigned y = 0; y < nHeight; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y / 2);
				for (unsigned x = 0; x < nWidth; x += 2)
				{
					unsigned char *pix = pixel + 3 * (x / 2);
					unsigned pos = y * nScanWidth + x;

					pix[nChannel_R] = pImg[pos];

					pix[nChannel_G] = (pImg[pos + 1] + pImg[pos + nScanWidth]) >> 1;

					pix[nChannel_B] = pImg[pos + nScanWidth + 1];
				}
			}

			return true;
		}

		else if (dm == DEBAYER_HQLI)
		{
			if (debayerHQLinear(desImg, 0, 0, desPxFmt))
			{
				return true;
			}
		}

		else if (dm == DEBAYER_BILINEAR)
		{
			return false;
		}

		return false;
	}


	bool xImage::debayerGBRG(xImage& desImg, EPixelFormat desPxFmt, EDebayerMethod dm)
	{
		if (!isValid())
		{
			return false;
		}

		if (BAYER_FORMAT_GBRG != m_byrFmt)
		{
			return false;
		}

		unsigned nChannel_R = 0;
		unsigned nChannel_G = 1;
		unsigned nChannel_B = 2;

		if (desPxFmt == PIXEL_FORMAT_RGB || desPxFmt == PIXEL_FORMAT_RGBU)
		{
			nChannel_R = 0;
			nChannel_G = 1;
			nChannel_B = 2;
		}
		else if (desPxFmt == PIXEL_FORMAT_BGR || desPxFmt == PIXEL_FORMAT_BGRU)
		{
			nChannel_R = 2;
			nChannel_G = 1;
			nChannel_B = 0;
		}
		else
		{
			return false;
		}

		unsigned nWidth = m_nWidth;
		unsigned nHeight = m_nHeight;
		unsigned nScanWidth = m_nPitch;
		unsigned char *pImg = m_pBuffer;

		if (dm == DEBAYER_AVERAGE)
		{
			//the first nHeight-1 row and the first nWidth-1 column
			if (!desImg.create(nWidth, nHeight, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned pitch = desImg.getPitch();
			unsigned char *pNewImg = desImg.getBuffer();
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
					pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 3;
					pix[nChannel_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = pImg[pos];
					pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;
					pix[nChannel_B] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
				}
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
					pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;
					pix[nChannel_B] = pImg[pos];
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;
					pix[nChannel_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
					pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 3;
					pix[nChannel_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				}
			}

			//the first row, with column from 0 to nWidth-1
			unsigned char *pixel = desImg.getScanLine(0);
			pixel[nChannel_R] = pImg[nScanWidth];
			pixel[nChannel_G] = (4 * pImg[0] + pImg[nScanWidth + 1]) / 5;
			pixel[nChannel_B] = pImg[1];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = (pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 1;
				pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos + nScanWidth]) / 3;
				pix[nChannel_B] = pImg[pos];
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = pImg[pos + nScanWidth];
				pix[nChannel_G] = (4 * pImg[pos] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) / 6;
				pix[nChannel_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
			}
			unsigned pos = nWidth - 1;
			unsigned char *pix = pixel + 3 * (nWidth - 1);
			pix[nChannel_R] = pImg[pos + nScanWidth - 1];
			pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + nScanWidth]) >> 1;
			pix[nChannel_B] = pImg[pos];

			//the last row, with column from 0 to nWidth-1
			pixel = desImg.getScanLine(nHeight - 1);
			pos = (nHeight - 1) * nScanWidth;
			pixel[nChannel_R] = pImg[pos];
			pixel[nChannel_G] = (pImg[pos + 1] + pImg[pos - nScanWidth]) >> 1;
			pixel[nChannel_B] = pImg[pos - nScanWidth + 1];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) / 6;
				pix[nChannel_B] = pImg[pos - nScanWidth];
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[nChannel_R] = pImg[pos];
				pix[nChannel_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth]) / 3;
				pix[nChannel_B] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) >> 1;
			}
			pos = (nHeight - 1) * nScanWidth + nWidth - 1;
			pix = pixel + 3 * (nWidth - 1);
			pix[nChannel_R] = pImg[pos - 1];
			pix[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1]) / 5;
			pix[nChannel_B] = pImg[pos - nScanWidth];

			//the first column, with row from 1 to nHeight-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = desImg.getScanLine(y);

				pixel[nChannel_R] = pImg[pos];
				pixel[nChannel_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos + 1]) / 3;
				pixel[nChannel_B] = (pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) >> 1;
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = desImg.getScanLine(y);

				pixel[nChannel_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				pixel[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) / 6;
				pixel[nChannel_B] = pImg[pos + 1];
			}

			//the last column, with row from 1 to nHeight-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[nChannel_R] = pImg[pos - 1];
				pixel[nChannel_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) / 6;
				pixel[nChannel_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[nChannel_R] = (pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 1;
				pixel[nChannel_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos - 1]) / 3;
				pixel[nChannel_B] = pImg[pos];
			}

			return true;
		}

		else if (dm == DEBAYER_BINNING)
		{
			if (!desImg.create(nWidth / 2, nHeight / 2, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			for (unsigned y = 0; y < nHeight; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y / 2);
				for (unsigned x = 0; x < nWidth; x += 2)
				{
					unsigned char *pix = pixel + 3 * (x / 2);
					unsigned pos = y * nScanWidth + x;

					pix[nChannel_R] = pImg[pos + nScanWidth];

					pix[nChannel_G] = (pImg[pos] + pImg[pos + nScanWidth + 1]) >> 1;

					pix[nChannel_B] = pImg[pos + 1];
				}
			}

			return true;
		}

		else if (dm == DEBAYER_HQLI)
		{
			if (debayerHQLinear(desImg, 0, 1, desPxFmt))
				return true;
		}
		else if (dm == DEBAYER_BILINEAR)
		{
			return false;
		}

		return false;
	}


	bool xImage::debayerBGGR(xImage& desImg, EPixelFormat desPxFmt, EDebayerMethod dm)
	{
		if (!isValid())
		{
			return false;
		}

		if (BAYER_FORMAT_BGGR != m_byrFmt)
		{
			return false;
		}

		int CHANNEL_R;
		int CHANNEL_G;
		int CHANNEL_B;

		if (desPxFmt == PIXEL_FORMAT_RGB || desPxFmt == PIXEL_FORMAT_RGBU)
		{
			CHANNEL_R = 0;
			CHANNEL_G = 1;
			CHANNEL_B = 2;
		}
		else if (desPxFmt == PIXEL_FORMAT_BGR || desPxFmt == PIXEL_FORMAT_BGRU)
		{
			CHANNEL_R = 2;
			CHANNEL_G = 1;
			CHANNEL_B = 0;
		}
		else
		{
			return false;
		}

		unsigned nWidth = m_nWidth;
		unsigned nHeight = m_nHeight;
		unsigned nScanWidth = m_nPitch;
		unsigned char *pImg = m_pBuffer;

		if (dm == DEBAYER_AVERAGE)
		{
			//clock_t ts = clock();
						//the first nHeight-1 row and the first nWidth-1 column
			if (!desImg.create(nWidth, nHeight, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nDesPitch = desImg.getPitch();

			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;

					pix[CHANNEL_R] = pImg[pos];

					pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;

					pix[CHANNEL_B] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;

					pix[CHANNEL_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;

					//pix[CHANNEL_G] = pImg[pos];
					pix[CHANNEL_G] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1] + pImg[pos] * 4) >> 3;

					pix[CHANNEL_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				}
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y);
				for (unsigned x = 1; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;

					pix[CHANNEL_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;

					//pix[CHANNEL_G] = pImg[pos];
					pix[CHANNEL_G] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1] + pImg[pos] * 4) >> 3;

					pix[CHANNEL_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				}
				for (unsigned x = 2; x < nWidth - 1; x += 2)
				{
					unsigned char *pix = pixel + 3 * x;
					unsigned pos = y * nScanWidth + x;

					pix[CHANNEL_R] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 2;

					pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 2;

					pix[CHANNEL_B] = pImg[pos];
				}
			}


			//the first row, with column from 0 to nWidth-1
			unsigned char *pixel = desImg.getScanLine(0);
			pixel[CHANNEL_R] = pImg[nScanWidth + 1];
			pixel[CHANNEL_G] = (pImg[nScanWidth] + pImg[1]) >> 1;
			pixel[CHANNEL_B] = pImg[0];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = pImg[pos + nScanWidth];
				pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) / 6;
				pix[CHANNEL_B] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = (pImg[pos + nScanWidth - 1] + pImg[pos + nScanWidth + 1]) >> 1;
				pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos + nScanWidth]) / 3;
				pix[CHANNEL_B] = pImg[pos];
			}
			unsigned pos = nWidth - 1;
			unsigned char *pix = pixel + 3 * (nWidth - 1);
			pix[CHANNEL_R] = pImg[pos + nScanWidth];
			pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos + nScanWidth - 1]) / 5;
			pix[CHANNEL_B] = pImg[pos - 1];

			//the last row, with column from 0 to nWidth-1
			pixel = desImg.getScanLine(nHeight - 1);
			pos = (nHeight - 1) * nScanWidth;
			pixel[CHANNEL_R] = pImg[pos + 1];
			pixel[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1]) / 5;
			pixel[CHANNEL_B] = pImg[pos - nScanWidth];
			for (unsigned x = 1; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = pImg[pos];
				pix[CHANNEL_G] = (pImg[pos - 1] + pImg[pos + 1] + pImg[pos - nScanWidth]) / 3;
				pix[CHANNEL_B] = (pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) >> 1;
			}
			for (unsigned x = 2; x < nWidth - 1; x += 2)
			{
				unsigned pos = (nHeight - 1) * nScanWidth + x;
				unsigned char *pix = pixel + 3 * x;
				pix[CHANNEL_R] = (pImg[pos - 1] + pImg[pos + 1]) >> 1;
				pix[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos - nScanWidth + 1]) / 6;
				pix[CHANNEL_B] = pImg[pos - nScanWidth];
			}
			pos = (nHeight - 1) * nScanWidth + nWidth - 1;
			pix = pixel + 3 * (nWidth - 1);
			pix[CHANNEL_R] = pImg[pos];
			pix[CHANNEL_G] = (pImg[pos - nScanWidth] + pImg[pos - 1]) >> 1;
			pix[CHANNEL_B] = pImg[pos - nScanWidth - 1];

			//the first column, with row from 1 to nHeight-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = desImg.getScanLine(y);

				pixel[CHANNEL_R] = pImg[pos + 1];
				pixel[CHANNEL_G] = (4 * pImg[pos] + pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) / 6;
				pixel[CHANNEL_B] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth;
				unsigned char *pixel = desImg.getScanLine(y);

				pixel[CHANNEL_R] = (pImg[pos - nScanWidth + 1] + pImg[pos + nScanWidth + 1]) >> 1;
				pixel[CHANNEL_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos + 1]) / 3;
				pixel[CHANNEL_B] = pImg[pos];
			}

			//the last column, with row from 1 to nHeight-2
			for (unsigned y = 1; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[CHANNEL_R] = pImg[pos];
				pixel[CHANNEL_G] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth] + pImg[pos - 1]) / 3;
				pixel[CHANNEL_B] = (pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 1;
			}
			for (unsigned y = 2; y < nHeight - 1; y += 2)
			{
				unsigned pos = y * nScanWidth + nWidth - 1;
				unsigned char *pixel = desImg.getScanLine(y) + 3 * (nWidth - 1);

				pixel[CHANNEL_R] = (pImg[pos - nScanWidth] + pImg[pos + nScanWidth]) >> 1;
				pixel[CHANNEL_G] = (2 * pImg[pos] + pImg[pos - nScanWidth - 1] + pImg[pos + nScanWidth - 1]) >> 2;
				pixel[CHANNEL_B] = pImg[pos - 1];
			}

			//clock_t te = clock();
			//ofstream ofs("debayertime.txt", ios_base::app|ios_base::out);
			//if (ofs)
			//{
			//	ofs<<te-ts<<endl;
			//}
			return true;
		}

		else if (dm == DEBAYER_BINNING)
		{
			if (!desImg.create(nWidth / 2, nHeight / 2, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			for (unsigned y = 0; y < nHeight; y += 2)
			{
				unsigned char *pixel = desImg.getScanLine(y / 2);
				for (unsigned x = 0; x < nWidth; x += 2)
				{
					unsigned char *pix = pixel + 3 * (x / 2);
					unsigned pos = y * nScanWidth + x;

					pix[CHANNEL_R] = pImg[pos + nScanWidth + 1];

					pix[CHANNEL_G] = (pImg[pos + 1] + pImg[pos + nScanWidth]) >> 1;

					pix[CHANNEL_B] = pImg[pos];
				}
			}

			return true;
		}

		else if (dm == DEBAYER_HQLI)
		{
			if (debayerHQLinear(desImg, 1, 1, desPxFmt))
			{
				return true;
			}
		}
		else if (dm == DEBAYER_BILINEAR)
		{
			return false;
		}


		return false;
	}


	//RGGB (RedX, RedY)(0,0)
	//GRBG (RedX, RedY)(1,0)
	//GBRG (RedX, RedY)(0,1)
	//BGGR (RedX, RedY)(1,1)
	bool xImage::debayerHQLinear(xImage& desImg, int RedX, int RedY, EPixelFormat pixFormat)
	{
		if (!isValid())
		{
			return false;
		}

		unsigned nChannel_R = 0;
		unsigned nChannel_G = 1;
		unsigned nChannel_B = 2;
		if (pixFormat == PIXEL_FORMAT_RGB || pixFormat == PIXEL_FORMAT_RGBU)
		{
			nChannel_R = 0;
			nChannel_G = 1;
			nChannel_B = 2;
		}
		else if (pixFormat == PIXEL_FORMAT_BGR || pixFormat == PIXEL_FORMAT_BGRU)
		{
			nChannel_R = 2;
			nChannel_G = 1;
			nChannel_B = 0;
		}
		else
		{
			return false;
		}

		unsigned Width = m_nWidth;
		unsigned Height = m_nHeight;
		unsigned nScanWidth = m_nPitch;
		unsigned char *Input = m_pBuffer;

		if (!desImg.create(Width, Height, m_bAligned, PIXEL_FORMAT_RGB))
		{
			return false;
		}

		unsigned pitch = desImg.getPitch();

		const int BlueX = 1 - RedX;
		const int BlueY = 1 - RedY;
		/* Neigh holds a copy of the 5x5 neighborhood around the current point */
		unsigned char Neigh[5][5];
		/* NeighPresence is used for boundary handling.  It is set to 0 if the
		   neighbor is beyond the boundaries of the image and 1 otherwise. */
		int NeighPresence[5][5];
		int i, j, x, y, nx, ny;


		for (y = 0, i = 0; y < Height; y++)
		{
			unsigned char *pixel = (unsigned char*)desImg.getScanLine(y);
			for (x = 0; x < Width; x++, i++)
			{
				/* 5x5 neighborhood around the point (x,y) is copied into Neigh */
				for (ny = -2, j = x + Width * (y - 2); ny <= 2; ny++, j += Width)
				{
					for (nx = -2; nx <= 2; nx++)
					{
						if (0 <= x + nx && x + nx < Width
							&& 0 <= y + ny && y + ny < Height)
						{
							Neigh[2 + nx][2 + ny] = Input[j + nx];
							NeighPresence[2 + nx][2 + ny] = 1;
						}
						else
						{
							Neigh[2 + nx][2 + ny] = 0;
							NeighPresence[2 + nx][2 + ny] = 0;
						}
					}
				}

				unsigned pos = y * nScanWidth + x;
				unsigned char *pix = (unsigned char*)pixel + 3 * x;
				double t0, t1;
				if ((x & 1) == RedX && (y & 1) == RedY)
				{
					/* Center pixel is red */
					pix[nChannel_R] = Input[pos];
					t0 = abs(2 * (Neigh[2][1] + Neigh[1][2]
						+ Neigh[3][2] + Neigh[2][3])
						+ (NeighPresence[0][2] + NeighPresence[4][2]
							+ NeighPresence[2][0] + NeighPresence[2][4])*Neigh[2][2]
						- Neigh[0][2] - Neigh[4][2]
						- Neigh[2][0] - Neigh[2][4])
						/ (2 * (NeighPresence[2][1] + NeighPresence[1][2]
							+ NeighPresence[3][2] + NeighPresence[2][3]));
					t1 = abs(4 * (Neigh[1][1] + Neigh[3][1]
						+ Neigh[1][3] + Neigh[3][3]) +
						3 * ((NeighPresence[0][2] + NeighPresence[4][2]
							+ NeighPresence[2][0] + NeighPresence[2][4])*Neigh[2][2]
							- Neigh[0][2] - Neigh[4][2]
							- Neigh[2][0] - Neigh[2][4]))
						/ (4 * (NeighPresence[1][1] + NeighPresence[3][1]
							+ NeighPresence[1][3] + NeighPresence[3][3]));
					pix[nChannel_G] = t0 < 0.0 ? 0 : (t0 > 255 ? 255 : (unsigned char)(t0));// CLIP(t0, pix[nChannel_G]);
					pix[nChannel_B] = t1 < 0.0 ? 0 : (t1 > 255 ? 255 : (unsigned char)(t1));//CLIP(t1, pix[nChannel_B]);
				}
				else if ((x & 1) == BlueX && (y & 1) == BlueY)
				{
					unsigned char *pix = (unsigned char*)pixel + 3 * x;
					/* Center pixel is blue */
					pix[nChannel_B] = Input[pos];
					t0 = abs(2 * (Neigh[2][1] + Neigh[1][2]
						+ Neigh[3][2] + Neigh[2][3])
						+ (NeighPresence[0][2] + NeighPresence[4][2]
							+ NeighPresence[2][0] + NeighPresence[2][4])*Neigh[2][2]
						- Neigh[0][2] - Neigh[4][2]
						- Neigh[2][0] - Neigh[2][4])
						/ (2 * (NeighPresence[2][1] + NeighPresence[1][2]
							+ NeighPresence[3][2] + NeighPresence[2][3]));
					t1 = abs(4 * (Neigh[1][1] + Neigh[3][1]
						+ Neigh[1][3] + Neigh[3][3]) +
						3 * ((NeighPresence[0][2] + NeighPresence[4][2]
							+ NeighPresence[2][0] + NeighPresence[2][4])*Neigh[2][2]
							- Neigh[0][2] - Neigh[4][2]
							- Neigh[2][0] - Neigh[2][4]))
						/ (4 * (NeighPresence[1][1] + NeighPresence[3][1]
							+ NeighPresence[1][3] + NeighPresence[3][3]));
					pix[nChannel_G] = t0 < 0.0 ? 0 : (t0 > 255 ? 255 : (unsigned char)(t0)); //CLIP(t0, pix[nChannel_G]);
					pix[nChannel_R] = t1 < 0.0 ? 0 : (t1 > 255 ? 255 : (unsigned char)(t1)); //CLIP(t1, pix[nChannel_R]);
				}
				else
				{
					unsigned char *pix = (unsigned char*)pixel + 3 * x;
					/* Center pixel is green */
					pix[nChannel_G] = Input[pos];

					if ((y & 1) == RedY)
					{
						/* Left and right neighbors are red */
						t0 = abs(8 * (Neigh[1][2] + Neigh[3][2])
							+ (2 * (NeighPresence[1][1] + NeighPresence[3][1]
								+ NeighPresence[0][2] + NeighPresence[4][2]
								+ NeighPresence[1][3] + NeighPresence[3][3])
								- NeighPresence[2][0] - NeighPresence[2][4])*Neigh[2][2]
							- 2 * (Neigh[1][1] + Neigh[3][1]
								+ Neigh[0][2] + Neigh[4][2]
								+ Neigh[1][3] + Neigh[3][3])
							+ Neigh[2][0] + Neigh[2][4])
							/ (8 * (NeighPresence[1][2] + NeighPresence[3][2]));
						t1 = abs(8 * (Neigh[2][1] + Neigh[2][3])
							+ (2 * (NeighPresence[1][1] + NeighPresence[3][1]
								+ NeighPresence[2][0] + NeighPresence[2][4]
								+ NeighPresence[1][3] + NeighPresence[3][3])
								- NeighPresence[0][2] - NeighPresence[4][2])*Neigh[2][2]
							- 2 * (Neigh[1][1] + Neigh[3][1]
								+ Neigh[2][0] + Neigh[2][4]
								+ Neigh[1][3] + Neigh[3][3])
							+ Neigh[0][2] + Neigh[4][2])
							/ (8 * (NeighPresence[2][1] + NeighPresence[2][3]));
					}
					else
					{
						/* Left and right neighbors are blue */
						t0 = abs(8 * (Neigh[2][1] + Neigh[2][3])
							+ (2 * (NeighPresence[1][1] + NeighPresence[3][1]
								+ NeighPresence[2][0] + NeighPresence[2][4]
								+ NeighPresence[1][3] + NeighPresence[3][3])
								- NeighPresence[0][2] - NeighPresence[4][2])*Neigh[2][2]
-2 * (Neigh[1][1] + Neigh[3][1]
	+ Neigh[2][0] + Neigh[2][4]
	+ Neigh[1][3] + Neigh[3][3])
	+ Neigh[0][2] + Neigh[4][2])
	/ (8 * (NeighPresence[2][1] + NeighPresence[2][3]));
t1 = (8 * (Neigh[1][2] + Neigh[3][2])
	+ (2 * (NeighPresence[1][1] + NeighPresence[3][1]
		+ NeighPresence[0][2] + NeighPresence[4][2]
		+ NeighPresence[1][3] + NeighPresence[3][3])
		- NeighPresence[2][0] - NeighPresence[2][4])*Neigh[2][2]
	- 2 * (Neigh[1][1] + Neigh[3][1]
		+ Neigh[0][2] + Neigh[4][2]
		+ Neigh[1][3] + Neigh[3][3])
	+ Neigh[2][0] + Neigh[2][4])
	/ (8 * (NeighPresence[1][2] + NeighPresence[3][2]));
					}
					pix[nChannel_R] = t0 < 0.0 ? 0 : (t0 > 255 ? 255 : (unsigned char)(t0)); //CLIP(t0, pix[nChannel_R]);
					pix[nChannel_B] = t1 < 0.0 ? 0 : (t1 > 255 ? 255 : (unsigned char)(t1)); //CLIP(t1, pix[nChannel_B]);
				}
			}
		}

		return true;
	}

	bool xImage::debayer(EPixelFormat dstPxFmt, EDebayerMethod dm, xImage *pDstImg)
	{
		if (m_pixFmt == PIXEL_FORMAT_RAW8)
		{
			xImage dstImg;

			if (m_byrFmt == BAYER_FORMAT_RGGB)
			{
				if (!debayerRGGB(dstImg, dstPxFmt, dm))
				{
					return false;
				}
			}
			else if (m_byrFmt == BAYER_FORMAT_GRBG)
			{
				if (!debayerGRBG(dstImg, dstPxFmt, dm))
				{
					return false;
				}
			}
			else if (m_byrFmt == BAYER_FORMAT_GBRG)
			{
				if (!debayerGBRG(dstImg, dstPxFmt, dm))
				{
					return false;
				}
			}
			else if (m_byrFmt == BAYER_FORMAT_BGGR)
			{
				if (!debayerBGGR(dstImg, dstPxFmt, dm))
				{
					return false;
				}
			}
			else
			{
				return false;
			}

			if (nullptr == pDstImg)
			{
				return copyFrom(dstImg);
			}
			else
			{
				return pDstImg->copyFrom(dstImg);
			}
		}

		return false;
	}

	bool xImage::monoToRGB(EPixelFormat dstPixFmt, xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (m_pixFmt != PIXEL_FORMAT_MONO8)
		{
			return false;
		}

		if (dstPixFmt != PIXEL_FORMAT_BGR && dstPixFmt != PIXEL_FORMAT_BGRU &&
			dstPixFmt != PIXEL_FORMAT_RGB && dstPixFmt != PIXEL_FORMAT_RGBU)
		{
			return false;
		}

		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nOffset = 0;

			unsigned nP = pDstImg->getPitch();
			unsigned nC = pDstImg->getChannels();
			unsigned char *pBuf = pDstImg->getBuffer();

			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					memset(pBuf + pos, m_pBuffer[nOffset + x], nC);

					pos += nC;
				}

				pBuf += nP;
				nOffset += m_nPitch;
			}

			return true;
		}

		xImage dstImg(m_nWidth, m_nHeight, m_bAligned, dstPixFmt, BAYER_FORMAT_NONE);
		if (!dstImg.isValid())
		{
			return false;
		}

		unsigned nOffset = 0;

		unsigned nP = dstImg.getPitch();
		unsigned nC = dstImg.getChannels();
		unsigned char *pBuf = dstImg.getBuffer();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned pos = 0;

			for (unsigned x = 0; x < m_nWidth; x++)
			{
				memset(pBuf + pos, m_pBuffer[nOffset + x], nC);

				pos += nC;
			}

			pBuf += nP;
			nOffset += m_nPitch;
		}

		return copyFrom(dstImg);
	}

	bool xImage::convert(EPixelFormat desPxFmt, xImage *pDesImg)
	{
		if (!isValid())
		{
			return false;
		}
		
		if (desPxFmt == PIXEL_FORMAT_MONO8)
		{
			if (m_pixFmt == PIXEL_FORMAT_MONO8)
			{
				if (nullptr == pDesImg)
				{
					return true;
				}
				else
				{
					return copyTo(*pDesImg);
				}
			}

			else if (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU)
			{
				unsigned nC = m_nPitch / m_nWidth;
				unsigned nW = m_nWidth;
				unsigned nH = m_nHeight;
				if (nullptr == pDesImg)
				{
					xImage desImg(nW, nH, m_bAligned, desPxFmt, BAYER_FORMAT_NONE);
					if (!desImg.isValid())
					{
						return false;
					}

					unsigned char *pImg = desImg.getBuffer();
					unsigned nP = desImg.getPitch();
					unsigned nOffset = 0;
					unsigned nOffset1 = 0;
					for (unsigned y = 0; y < nH; y++)
					{
						unsigned pos = nOffset;
						for (unsigned x = 0; x < nW; x++)
						{
							pImg[nOffset1 + x] = RGB2GRAY(m_pBuffer[pos + 2], m_pBuffer[pos + 1], m_pBuffer[pos]);
							pos += nC;
						}
						nOffset  += m_nPitch;
						nOffset1 += nP;
					}

					return copyFrom(desImg);
				}
				else
				{
					if (!pDesImg->create(nW, nH, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
					{
						return false;
					}

					unsigned char *pImg = pDesImg->getBuffer();
					unsigned nP = pDesImg->getPitch();
					unsigned nOffset = 0;
					unsigned nOffset1 = 0;
					for (unsigned y = 0; y < nH; y++)
					{
						unsigned pos = nOffset;
						for (unsigned x = 0; x < nW; x++)
						{
							pImg[nOffset1 + x] = RGB2GRAY(m_pBuffer[pos + 2], m_pBuffer[pos + 1], m_pBuffer[pos]);
							pos += nC;
						}
						nOffset  += m_nPitch;
						nOffset1 += nP;
					}

					return true;
				}
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGB8 || m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU)
			{
				unsigned nC = m_nPitch / m_nWidth;
				unsigned nW = m_nWidth;
				unsigned nH = m_nHeight;
				if (nullptr == pDesImg)
				{
					xImage desImg(nW, nH, m_bAligned, desPxFmt, BAYER_FORMAT_NONE);
					if (!desImg.isValid())
					{
						return false;
					}

					unsigned char *pImg = desImg.getBuffer();
					unsigned nP = desImg.getPitch();
					unsigned nOffset = 0;
					unsigned nOffset1 = 0;
					for (unsigned y = 0; y < nH; y++)
					{
						unsigned pos = nOffset;
						for (unsigned x = 0; x < nW; x++)
						{
							pImg[nOffset1 + x] = RGB2GRAY(m_pBuffer[pos], m_pBuffer[pos + 1], m_pBuffer[pos + 2]);
							pos += nC;
						}
						nOffset += m_nPitch;
						nOffset1 += nP;
					}

					return copyFrom(desImg);
				}
				else
				{
					if (!pDesImg->create(nW, nH, m_bAligned, desPxFmt, BAYER_FORMAT_NONE))
					{
						return false;
					}

					unsigned char *pImg = pDesImg->getBuffer();
					unsigned nP = pDesImg->getPitch();
					unsigned nOffset = 0;
					unsigned nOffset1 = 0;
					for (unsigned y = 0; y < nH; y++)
					{
						unsigned pos = nOffset;
						for (unsigned x = 0; x < nW; x++)
						{
							pImg[nOffset1 + x] = RGB2GRAY(m_pBuffer[pos], m_pBuffer[pos + 1], m_pBuffer[pos + 2]);
							pos += nC;
						}
						nOffset += m_nPitch;
						nOffset1 += nP;
					}

					return true;
				}
			}

			else if (m_pixFmt == PIXEL_FORMAT_RAW8)
			{
				if (nullptr == pDesImg)
				{
					if (!debayer(PIXEL_FORMAT_BGR))
					{
						return false;
					}

					return convert(desPxFmt);
				}
				else
				{
					if (!debayer(PIXEL_FORMAT_BGR, DEBAYER_AVERAGE, pDesImg))
					{
						return false;
					}

					return pDesImg->convert(desPxFmt);
				}
			}
			else
			{
				return false;
			}
		}//convert to Mono8 Image

		else if (desPxFmt == PIXEL_FORMAT_BGR || desPxFmt == PIXEL_FORMAT_BGRU)
		{
			if (m_pixFmt == PIXEL_FORMAT_RAW8)
			{
				return debayer(desPxFmt, DEBAYER_AVERAGE, pDesImg);
			}
			
			/////////////////////////////////////////////////////////////////////////

			else if (m_pixFmt == PIXEL_FORMAT_MONO8)
			{
				return monoToRGB(desPxFmt, pDesImg);
			}
			
			/////////////////////////////////////////////////////////////////////////

			else if (m_pixFmt == PIXEL_FORMAT_BGR && desPxFmt == PIXEL_FORMAT_BGR)
			{
				if (nullptr == pDesImg)
				{
					return true;
				}
				else
				{
					return copyTo(*pDesImg);
				}
			}

			else if (m_pixFmt == PIXEL_FORMAT_BGRU && desPxFmt == PIXEL_FORMAT_BGR)
			{
				return rgb32To24(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGB && desPxFmt == PIXEL_FORMAT_BGR)
			{
				return swap(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGBU && desPxFmt == PIXEL_FORMAT_BGR)
			{
				return swapDG(pDesImg);
			}

			/////////////////////////////////////////////////////////////////////////
			
			else if (m_pixFmt == PIXEL_FORMAT_BGR && desPxFmt == PIXEL_FORMAT_BGRU)
			{
				return rgb24To32(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_BGRU && desPxFmt == PIXEL_FORMAT_BGRU)
			{
				if (nullptr == pDesImg)
				{
					return true;
				}
				else
				{
					return copyTo(*pDesImg);
				}
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGB && desPxFmt == PIXEL_FORMAT_BGRU)
			{
				return swapUG(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGBU && desPxFmt == PIXEL_FORMAT_BGRU)
			{
				return swap(pDesImg);
			}

			/////////////////////////////////////////////////////////////////////////

			else
			{
				return false;
			}

		}//convert to B-G-R image

		else if (desPxFmt == PIXEL_FORMAT_RGB || desPxFmt == PIXEL_FORMAT_RGBU)
		{
			if (m_pixFmt == PIXEL_FORMAT_RAW8)
			{
				return debayer(desPxFmt, DEBAYER_AVERAGE, pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_MONO8)
			{
				return monoToRGB(desPxFmt, pDesImg);
			}

			/////////////////////////////////////////////////////////////////////////

			else if (m_pixFmt == PIXEL_FORMAT_BGR && desPxFmt == PIXEL_FORMAT_RGB)
			{
				return swap(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_BGRU && desPxFmt == PIXEL_FORMAT_RGB)
			{
				return swapDG(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGB && desPxFmt == PIXEL_FORMAT_RGB)
			{
				if (nullptr == pDesImg)
				{
					return true;
				}
				else
				{
					return copyTo(*pDesImg);
				}
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGBU && desPxFmt == PIXEL_FORMAT_RGB)
			{
				return rgb32To24(pDesImg);
			}

			/////////////////////////////////////////////////////////////////////////

			else if (m_pixFmt == PIXEL_FORMAT_BGR && desPxFmt == PIXEL_FORMAT_RGBU)
			{
				return swapUG(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_BGRU && desPxFmt == PIXEL_FORMAT_RGBU)
			{
				return swap(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGB && desPxFmt == PIXEL_FORMAT_RGBU)
			{
				return rgb24To32(pDesImg);
			}

			else if (m_pixFmt == PIXEL_FORMAT_RGBU && desPxFmt == PIXEL_FORMAT_RGBU)
			{
				if (nullptr == pDesImg)
				{
					return true;
				}
				else
				{
					return copyTo(*pDesImg);
				}
			}			

			/////////////////////////////////////////////////////////////////////////

			else
			{
				return false;
			}
		}//convert to R-g-B image

		else
		{
			return false;
		}

	}

	bool xImage::grayscale(xImage *pDstImg)
	{
		return convert(PIXEL_FORMAT_MONO8, pDstImg);
	}

	bool xImage::getRChannel(xImage& rImg)
	{
		if (!isValid())
		{
			return false;
		}

		unsigned nW, nH;
		if (m_pixFmt == PIXEL_FORMAT_RAW8)
		{
			nW = m_nWidth / 2;
			nH = m_nHeight / 2;
			if (m_byrFmt == BAYER_FORMAT_RGGB)
			{
				if (!rImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = rImg.getBuffer();
				unsigned nP = rImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[2 * y*m_nPitch + 2 * x];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_GRBG)
			{
				if (!rImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = rImg.getBuffer();
				unsigned nP = rImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[2 * y*m_nPitch + 2 * x + 1];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_GBRG)
			{
				if (!rImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = rImg.getBuffer();
				unsigned nP = rImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[(2 * y + 1)*m_nPitch + 2 * x];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_BGGR)
			{
				if (!rImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = rImg.getBuffer();
				unsigned nP = rImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[(2 * y + 1)*m_nPitch + 2 * x + 1];
					}
				}

				return true;
			}
		}

		else if (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU)
		{
			nW = m_nWidth;
			nH = m_nHeight;

			if (!rImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nC = m_nBpp / 8;
			unsigned char *pDesImg = rImg.getBuffer();
			unsigned nP = rImg.getPitch();
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					pDesImg[y*nP + x] = m_pBuffer[y*m_nPitch + x * nC + 2];
				}
			}

			return true;
		}

		else if (m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU)
		{
			nW = m_nWidth;
			nH = m_nHeight;

			if (!rImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nC = m_nBpp / 8;
			unsigned char *pDesImg = rImg.getBuffer();
			unsigned nP = rImg.getPitch();
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					pDesImg[y*nP + x] = m_pBuffer[y*m_nPitch + x * nC];
				}
			}

			return true;
		}

		return false;
	}

	bool xImage::getGChannel(xImage& gImg)
	{
		if (!isValid())
		{
			return false;
		}

		unsigned nW, nH;
		if (m_pixFmt == PIXEL_FORMAT_RAW8)
		{
			nW = m_nWidth / 2;
			nH = m_nHeight / 2;
			if (m_byrFmt == BAYER_FORMAT_RGGB || m_byrFmt == BAYER_FORMAT_BGGR)
			{
				if (!gImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = gImg.getBuffer();
				unsigned nP = gImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[2 * y*m_nPitch + 2 * x + 1];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_GRBG || m_byrFmt == BAYER_FORMAT_GBRG)
			{
				if (!gImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = gImg.getBuffer();
				unsigned nP = gImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[2 * y*m_nPitch + 2 * x];
					}
				}

				return true;
			}
		}

		else if (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU || m_pixFmt == PIXEL_FORMAT_RGB8 || m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU)
		{
			nW = m_nWidth;
			nH = m_nHeight;

			if (!gImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nC = m_nBpp / 8;
			unsigned char *pDesImg = gImg.getBuffer();
			unsigned nP = gImg.getPitch();
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					pDesImg[y*nP + x] = m_pBuffer[y*m_nPitch + x * nC + 1];
				}
			}

			return true;
		}


		return false;
	}

	bool xImage::getBChannel(xImage& bImg)
	{
		if (!isValid())
		{
			return false;
		}

		unsigned nW, nH;
		if (m_pixFmt == PIXEL_FORMAT_RAW8)
		{
			nW = m_nWidth / 2;
			nH = m_nHeight / 2;
			if (m_byrFmt == BAYER_FORMAT_RGGB)
			{
				if (!bImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = bImg.getBuffer();
				unsigned nP = bImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[(2 * y + 1)*m_nPitch + 2 * x + 1];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_GRBG)
			{
				if (!bImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = bImg.getBuffer();
				unsigned nP = bImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[(2 * y + 1)*m_nPitch + 2 * x];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_GBRG)
			{
				if (!bImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = bImg.getBuffer();
				unsigned nP = bImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[2 * y*m_nPitch + (2 * x + 1)];
					}
				}

				return true;
			}

			else if (m_byrFmt == BAYER_FORMAT_BGGR)
			{
				if (!bImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
				{
					return false;
				}

				unsigned char *pDesImg = bImg.getBuffer();
				unsigned nP = bImg.getPitch();
				for (unsigned y = 0; y < nH; y++)
				{
					for (unsigned x = 0; x < nW; x++)
					{
						pDesImg[y*nP + x] = m_pBuffer[2 * y*m_nPitch + 2 * x];
					}
				}

				return true;
			}
		}

		else if (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU)
		{
			nW = m_nWidth;
			nH = m_nHeight;

			if (!bImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nC = m_nBpp / 8;
			unsigned char *pDesImg = bImg.getBuffer();
			unsigned nP = bImg.getPitch();
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					pDesImg[y*nP + x] = m_pBuffer[y*m_nPitch + x * nC];
				}
			}

			return true;
		}

		else if (m_pixFmt == PIXEL_FORMAT_RGB8 || m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU)
		{
			nW = m_nWidth;
			nH = m_nHeight;

			if (!bImg.create(nW, nH, m_bAligned, PIXEL_FORMAT_MONO8, BAYER_FORMAT_NONE))
			{
				return false;
			}

			unsigned nC = m_nBpp / 8;
			unsigned char *pDesImg = bImg.getBuffer();
			unsigned nP = bImg.getPitch();
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					pDesImg[y*nP + x] = m_pBuffer[y*m_nPitch + x * nC + 2];
				}
			}

			return true;
		}

		return false;
	}

	bool xImage::getHistogram(int histR[256], int histG[256], int histB[256])
	{
		if (!isValid())
		{
			return false;
		}

		if (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU)
		{
			memset(histR, 0, 256 * sizeof(int));
			memset(histG, 0, 256 * sizeof(int));
			memset(histB, 0, 256 * sizeof(int));

			unsigned char *pimg = getBuffer();
			unsigned nP = getPitch();
			unsigned nH = getHeight();
			unsigned nW = getWidth();
			unsigned nC = getChannels();
			unsigned pos = 0;
			for (unsigned y = 0; y < nH; y++)
			{
				int pos1 = pos;
				for (unsigned x = 0; x < nW; x++)
				{
					histB[pimg[pos1]]++;
					histG[pimg[pos1 + 1]]++;
					histR[pimg[pos1 + 2]]++;
					pos1 += nC;
				}
				pos += nP;
			}

			return true;
		}

		else if (m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU)
		{
			memset(histR, 0, 256 * sizeof(int));
			memset(histG, 0, 256 * sizeof(int));
			memset(histB, 0, 256 * sizeof(int));

			unsigned char *pimg = getBuffer();
			unsigned nP = getPitch();
			unsigned nH = getHeight();
			unsigned nW = getWidth();
			unsigned nC = getChannels();
			unsigned pos = 0;
			for (unsigned y = 0; y < nH; y++)
			{
				unsigned pos1 = pos;
				for (unsigned x = 0; x < nW; x++)
				{
					histR[pimg[pos1]]++;
					histG[pimg[pos1 + 1]]++;
					histB[pimg[pos1 + 2]]++;
					pos1 += nC;
				}
				pos += nP;
			}

			return true;
		}

		else if (m_pixFmt == PIXEL_FORMAT_MONO8)
		{
			memset(histR, 0, 256 * sizeof(int));

			unsigned char *pimg = getBuffer();
			unsigned nP = getPitch();
			unsigned nH = getHeight();
			unsigned nW = getWidth();
			unsigned pos = 0;
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					histR[pimg[pos + x]]++;
				}
				pos += nP;
			}

			return true;
		}

		return false;
	}

	bool xImage::equalizeHistogram()
	{
		int hr[256], hg[256], hb[256];
		if (!getHistogram(hr, hg, hb))
		{
			return false;
		}

		if (m_pixFmt == PIXEL_FORMAT_BGR || m_pixFmt == PIXEL_FORMAT_BGRU)
		{
			unsigned char *pimg = getBuffer();
			unsigned nP = getPitch();
			unsigned nH = getHeight();
			unsigned nW = getWidth();
			unsigned nC = getChannels();

			double pr[256], pg[256], pb[256];
			for (int i = 0; i < 256; i++)
			{
				pr[i] = (double)hr[i] / nW / nH;
				if (i > 0)
					pr[i] += pr[i - 1];

				pg[i] = (double)hg[i] / nW / nH;
				if (i > 0)
					pg[i] += pg[i - 1];

				pb[i] = (double)hb[i] / nW / nH;
				if (i > 0)
					pb[i] += pb[i - 1];
			}

			unsigned pos = 0;
			for (unsigned y = 0; y < nH; y++)
			{
				unsigned pos1 = pos;
				for (unsigned x = 0; x < nW; x++)
				{
					pimg[pos1]		= (unsigned char)(255 * pb[pimg[pos1]]);
					pimg[pos1 + 1]	= (unsigned char)(255 * pg[pimg[pos1 + 1]]);
					pimg[pos1 + 2]	= (unsigned char)(255 * pr[pimg[pos1 + 2]]);
					pos1 += nC;
				}
				pos += nP;
			}

			return true;
		}

		else if (m_pixFmt == PIXEL_FORMAT_RGB || m_pixFmt == PIXEL_FORMAT_RGBU)
		{
			unsigned char *pimg = getBuffer();
			unsigned nP = getPitch();
			unsigned nH = getHeight();
			unsigned nW = getWidth();
			unsigned nC = getChannels();

			double pr[256], pg[256], pb[256];
			for (int i = 0; i < 256; i++)
			{
				pr[i] = (double)hr[i] / nW / nH;
				if (i > 0)
					pr[i] += pr[i - 1];

				pg[i] = (double)hg[i] / nW / nH;
				if (i > 0)
					pg[i] += pg[i - 1];

				pb[i] = (double)hb[i] / nW / nH;
				if (i > 0)
					pb[i] += pb[i - 1];
			}

			unsigned pos = 0;
			for (unsigned y = 0; y < nH; y++)
			{
				unsigned pos1 = pos;
				for (unsigned x = 0; x < nW; x++)
				{
					pimg[pos1]		= (unsigned char)(255 * pr[pimg[pos1]]);
					pimg[pos1 + 1]	= (unsigned char)(255 * pg[pimg[pos1 + 1]]);
					pimg[pos1 + 2]	= (unsigned char)(255 * pb[pimg[pos1 + 2]]);
					pos1 += nC;
				}
				pos += nP;
			}

			return true;
		}

		else if (m_pixFmt == PIXEL_FORMAT_MONO8)
		{
			unsigned char *pimg = getBuffer();
			unsigned nP = getPitch();
			unsigned nH = getHeight();
			unsigned nW = getWidth();

			double pr[256];
			for (int i = 0; i < 256; i++)
			{
				pr[i] = (double)hr[i] / nW / nH;
				if (i > 0)
					pr[i] += pr[i - 1];
			}

			unsigned pos = 0;
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					pimg[pos + x] = (unsigned char)(255 * pr[pimg[pos + x]]);
				}
				pos += nP;
			}

			return true;
		}

		return false;
	}

	bool xImage::flip(xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (nullptr == pDstImg)
		{
			unsigned yc = m_nHeight / 2;
			unsigned nChannel = m_nBpp / 8;
			unsigned char *pTLine = new unsigned char[m_nPitch];

			unsigned char *pLLine = m_pBuffer;
			unsigned char *pULine = m_pBuffer + (m_nHeight - 1) * m_nPitch;
			for (unsigned y = 0; y < yc; y++)
			{
				memcpy(pTLine, pLLine, m_nPitch);
				memcpy(pLLine, pULine, m_nPitch);
				memcpy(pULine, pTLine, m_nPitch);
				pLLine += m_nPitch;
				pULine -= m_nPitch;
			}

			delete[]pTLine;

			if (m_nHeight % 2 == 0)
			{
				switch (m_byrFmt)
				{
				case BAYER_FORMAT_RGGB:
					m_byrFmt = BAYER_FORMAT_GBRG;
					break;

				case BAYER_FORMAT_GBRG:
					m_byrFmt = BAYER_FORMAT_RGGB;
					break;

				case BAYER_FORMAT_GRBG:
					m_byrFmt = BAYER_FORMAT_BGGR;
					break;

				case BAYER_FORMAT_BGGR:
					m_byrFmt = BAYER_FORMAT_GRBG;
					break;
				}
			}

			return true;
		}

		EBayerFormat dstByrFmt = m_byrFmt;

		if (m_nHeight % 2 == 0)
		{
			switch (m_byrFmt)
			{
			case BAYER_FORMAT_RGGB:
				dstByrFmt = BAYER_FORMAT_GBRG;
				break;

			case BAYER_FORMAT_GBRG:
				dstByrFmt = BAYER_FORMAT_RGGB;
				break;

			case BAYER_FORMAT_GRBG:
				dstByrFmt = BAYER_FORMAT_BGGR;
				break;

			case BAYER_FORMAT_BGGR:
				dstByrFmt = BAYER_FORMAT_GRBG;
				break;
			}
		}

		if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, m_pixFmt, dstByrFmt))
		{
			return false;
		}

		unsigned char *pBufDst = pDstImg->getBuffer();
		unsigned char *pBufSrc = m_pBuffer + (m_nHeight - 1)*m_nPitch;
		for (unsigned y = 0; y < m_nHeight; y++)
		{
			memcpy(pBufDst, pBufSrc, m_nPitch);
			pBufDst += m_nPitch;
			pBufSrc -= m_nPitch;
		}
			   
		return true;
	}

	bool xImage::mirror(xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		if (nullptr == pDstImg)
		{
			unsigned xc = m_nWidth / 2;
			unsigned nChannel = m_nBpp / 8;
			unsigned char *pTPix = new unsigned char[nChannel];

			int nPixByteWidth = nChannel * sizeof(unsigned char);

			unsigned char *pPixRow = m_pBuffer;
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pLPix = pPixRow;
				unsigned char *pRPix = pPixRow + (m_nWidth - 1) * nChannel;
				for (unsigned x = 0; x < xc; x++)
				{
					memcpy(pTPix, pLPix, nPixByteWidth);
					memcpy(pLPix, pRPix, nPixByteWidth);
					memcpy(pRPix, pTPix, nPixByteWidth);
					pLPix += nChannel;
					pRPix -= nChannel;
				}

				pPixRow += m_nPitch;
			}

			delete[]pTPix;

			if (m_nWidth % 2 == 0)
			{
				switch (m_byrFmt)
				{
				case BAYER_FORMAT_RGGB:
					m_byrFmt = BAYER_FORMAT_GRBG;
					break;

				case BAYER_FORMAT_GBRG:
					m_byrFmt = BAYER_FORMAT_BGGR;
					break;

				case BAYER_FORMAT_GRBG:
					m_byrFmt = BAYER_FORMAT_RGGB;
					break;

				case BAYER_FORMAT_BGGR:
					m_byrFmt = BAYER_FORMAT_GBRG;
					break;
				}
			}

			return true;
		}

		EBayerFormat dstByrFmt = m_byrFmt;

		if (m_nWidth % 2 == 0)
		{
			switch (m_byrFmt)
			{
			case BAYER_FORMAT_RGGB:
				dstByrFmt = BAYER_FORMAT_GRBG;
				break;

			case BAYER_FORMAT_GBRG:
				dstByrFmt = BAYER_FORMAT_BGGR;
				break;

			case BAYER_FORMAT_GRBG:
				dstByrFmt = BAYER_FORMAT_RGGB;
				break;

			case BAYER_FORMAT_BGGR:
				dstByrFmt = BAYER_FORMAT_GBRG;
				break;
			}
		}

		if (!pDstImg->create(m_nWidth, m_nHeight, m_bAligned, m_pixFmt, dstByrFmt))
		{
			return false;
		}

		unsigned nC = getChannels();

		if (nC == 1)
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pBufDst = pDstImg->getScanLine(y);

				unsigned char *pBufSrc = getScanLine(y);

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pBufDst[x] = pBufSrc[m_nWidth-1-x];
				}
			}
		}
		else
		{
			unsigned nOffset = nC * (m_nWidth - 1);
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned char *pBufDst = pDstImg->getScanLine(y);

				unsigned char *pBufSrc = getScanLine(y) + nOffset;

				for (unsigned x = 0; x < m_nWidth; x++)
				{
					memcpy(pBufDst, pBufSrc, nC);
					pBufDst += nC;
					pBufSrc -= nC;
				}
			}
		}

		return true;
	}


	bool xImage::rotate(double theta, EImageInterpolationMethod iim, xImage *pDstImg)
	{
		if (!isValid())
			return false;

		double dA = theta - round(theta / 360)*360.0;

		const double espilon = 0.001;

		if (fabs(dA) < espilon || 360 - fabs(dA) < espilon)
		{
			if (nullptr == pDstImg)\
			{
				return true;
			}
			else
			{
				return copyTo(*pDstImg);
			}
		}

		else if (fabs(fabs(dA) - 180) < espilon)
		{
			unsigned char *pOut = m_pBuffer;

			if (nullptr != pDstImg)
			{
				if (!copyTo(*pDstImg))
				{
					return false;
				}

				pOut = pDstImg->getBuffer();
			}


			int nC = getChannels();

			unsigned char *pPixel = new unsigned char[nC];
			int nBytesPerPix = nC * sizeof(unsigned char);

			unsigned char *pStride = new unsigned char[m_nPitch];
			int nStride = m_nPitch * sizeof(unsigned char);

			int nHalfH = m_nHeight / 2;
			int nHalfW = m_nWidth / 2;
			int nOffset0 = 0;
			int nOffset1 = (m_nHeight - 1) * m_nPitch;
			int nLPos = nC * (m_nWidth - 1);
			for (int y = 0; y < nHalfH; y++)
			{
				unsigned char *pL0 = pOut + nOffset0;
				unsigned char *pL1 = pOut + nOffset1;

				int pos = 0;
				for (int x = 0; x < nHalfW; x++)
				{
					unsigned char *pPxA = pL0 + pos;
					unsigned char *pPxB = pL0 + nLPos - pos;
					memcpy(pPixel, pPxA, nBytesPerPix);
					memcpy(pPxA, pPxB, nBytesPerPix);
					memcpy(pPxB, pPixel, nBytesPerPix);

					pPxA = pL1 + pos;
					pPxB = pL1 + nLPos - pos;
					memcpy(pPixel, pPxA, nBytesPerPix);
					memcpy(pPxA, pPxB, nBytesPerPix);
					memcpy(pPxB, pPixel, nBytesPerPix);

					pos += nC;
				}

				memcpy(pStride, pL0, nStride);
				memcpy(pL0, pL1, nStride);
				memcpy(pL1, pStride, nStride);

				nOffset0 += m_nPitch;
				nOffset1 -= m_nPitch;
			}

			delete[]pStride;
			delete[]pPixel;
		}

		else if (fabs(dA - 90) < espilon || fabs(dA + 270) < espilon)
		{			
			xImage imgOut;
			unsigned nPitchOut = 0;
			unsigned char *pOut = nullptr;

			if (nullptr != pDstImg)
			{
				if (!pDstImg->create(m_nHeight, m_nWidth, m_bAligned, m_pixFmt, m_byrFmt))
				{
					return false;
				}

				pOut = pDstImg->getBuffer();

				nPitchOut = pDstImg->getPitch();
			}
			else
			{
				if (!imgOut.create(m_nHeight, m_nWidth, m_bAligned, m_pixFmt, m_byrFmt))
				{
					return false;
				}

				pOut = imgOut.getBuffer();

				nPitchOut = imgOut.getPitch();
			}
			
			int nC = getChannels();

			int nBytesPerPix = nC * sizeof(unsigned char);

			int nLastPxPos = nC * (m_nWidth - 1);

			unsigned char *pIn = getBuffer();
			int nOffset = 0;
			int nOffsetOut = 0;
			for (int y = 0; y < m_nHeight; y++)
			{
				unsigned char *pInPx = m_pBuffer + nOffset + nLastPxPos;

				unsigned char *pOutPx = pOut + nOffsetOut;

				for (int x = 0; x < m_nWidth; x++)
				{
					memcpy(pOutPx, pInPx, nBytesPerPix);

					pInPx -= nC;
					pOutPx += nPitchOut;
				}

				nOffset += m_nPitch;
				nOffsetOut += nC;
			}

			if (nullptr == pDstImg)
			{
				copyFrom(imgOut);
			}
		}

		else if (fabs(dA + 90) < espilon || fabs(dA - 270) < espilon)
		{
			xImage imgOut;
			unsigned nPitchOut = 0;
			unsigned char *pOut = nullptr;

			if (nullptr != pDstImg)
			{
				if (!pDstImg->create(m_nHeight, m_nWidth, m_bAligned, m_pixFmt, m_byrFmt))
				{
					return false;
				}

				pOut = pDstImg->getBuffer();

				nPitchOut = pDstImg->getPitch();
			}
			else
			{
				if (!imgOut.create(m_nHeight, m_nWidth, m_bAligned, m_pixFmt, m_byrFmt))
				{
					return false;
				}

				pOut = imgOut.getBuffer();

				nPitchOut = imgOut.getPitch();
			}
			
			int nC = getChannels();

			int nBytesPerPix = nC * sizeof(unsigned char);

			int nLastPxPosOut = nC * (m_nHeight - 1);

			unsigned char *pIn = getBuffer();
			int nOffset = 0;
			int nOffsetOut = nLastPxPosOut;
			for (int y = 0; y < m_nHeight; y++)
			{
				unsigned char *pInPx = m_pBuffer + nOffset;

				unsigned char *pOutPx = pOut + nOffsetOut;

				for (int x = 0; x < m_nWidth; x++)
				{
					memcpy(pOutPx, pInPx, nBytesPerPix);

					pInPx += nC;
					pOutPx += nPitchOut;
				}

				nOffset += m_nPitch;
				nOffsetOut -= nC;
			}

			if (nullptr == pDstImg)
			{
				return copyFrom(imgOut);
			}
		}

		else
		{
			theta = theta * PI / 180;

			double xc = (m_nWidth - 1) / 2.0;
			double yc = (m_nHeight - 1) / 2.0;

			double x[4], y[4];
			x[0] = 0;
			y[0] = 0;
			x[1] = m_nWidth - 1;
			y[1] = 0;
			x[2] = m_nWidth - 1;
			y[2] = m_nHeight - 1;
			x[3] = 0;
			y[3] = m_nHeight - 1;

			for (int i = 0; i < 4; i++)
			{
				x[i] -= xc;
				y[i] -= yc;
			}

			double sin_theta = sin(theta);
			double cos_theta = cos(theta);

			double xx[4], yy[4];
			for (int i = 0; i < 4; i++)
			{
				xx[i] = cos_theta * x[i] + sin_theta * y[i];
				yy[i] = -sin_theta * x[i] + cos_theta * y[i];
			}

			double xmin = xx[0], ymin = yy[0];
			double xmax = xx[0], ymax = yy[0];
			for (int i = 1; i < 4; i++)
			{
				if (xx[i] < xmin)	xmin = xx[i];
				if (xx[i] > xmax)	xmax = xx[i];
				if (yy[i] < ymin)	ymin = yy[i];
				if (yy[i] > ymax)	ymax = yy[i];
			}

			int xs = round(xmin);
			int xe = round(xmax);
			int ys = round(ymin);
			int ye = round(ymax);
			int w = xe - xs + 1;
			int h = ye - ys + 1;

			xImage imgOut;

			if (!imgOut.create(w, h, m_bAligned, m_pixFmt, m_byrFmt))
			{
				return false;
			}

			if (iim == IIM_NEAREST_NEIGHBOR)
			{
				unsigned char *pImg = imgOut.getBuffer();
				unsigned nPitch = imgOut.getPitch();
				unsigned nChannel = imgOut.getBPP() / 8;
				for (int y = ys; y <= ye; y++)
				{
					for (int x = xs; x <= xe; x++)
					{
						double srcx = cos_theta * x - sin_theta * y + xc;
						double srcy = sin_theta * x + cos_theta * y + yc;

						int xp = round(srcx);
						int yp = round(srcy);

						if (xp < 0 || xp >= m_nWidth || yp < 0 || yp >= m_nHeight)
						{
							memset(pImg + (y - ys)*nPitch + (x - xs)*nChannel, 0, nChannel * sizeof(unsigned char));
						}
						else
						{
							for (unsigned c = 0; c < nChannel; c++)
							{
								pImg[(y - ys)*nPitch + (x - xs)*nChannel + c] = m_pBuffer[yp*m_nPitch + xp * nChannel + c];
							}
						}
					}
				}
			}
			else// if (iim == IIM_BILINEAR)
			{
				return false;
			}

			return copyFrom(imgOut);
		}

		return true;
	}

	bool xImage::roi(xImage& imgRoi, int xs, int ys, int w, int h)
	{
		if (!isValid())
			return false;

		if (w <= 0 || h <= 0)
			return false;

		if (!imgRoi.create(w, h, m_bAligned, m_pixFmt, m_byrFmt))
			return false;

		unsigned char *pImg = imgRoi.getBuffer();
		unsigned nPitch = imgRoi.getPitch();
		unsigned nChannel = imgRoi.getBPP() / 8;
		
		int xmin = max(xs, 0);
		int xmax = min(xs + w, m_nWidth);
		int ymin = max(ys, 0);
		int ymax = min(ys + h, m_nHeight);
		int nw = xmax - xmin;
		int nh = ymax - ymin;
		if (xmin < xmax && ymin < ymax)
		{
			unsigned char *pSrc = m_pBuffer + ymin * m_nPitch + xmin * nChannel;
			unsigned char *pDst = pImg + (ymin - ys) * nPitch + (xmin - xs) * nChannel;
			unsigned nBytes = nw * nChannel * sizeof(unsigned char);
			for (int y = ymin; y < ymax; y++)
			{
				memcpy(pDst, pSrc, nBytes);
				pSrc += m_nPitch;
				pDst += nPitch;
			}
		}

		return true;
	}


	bool xImage::windowLevelTransform(int nWinCentre, int nWindWidth, xImage *pDstImg)
	{
		// TODO: Add your command handler code here
		if (0 > nWindWidth || nWindWidth > 2 * nWinCentre || 2 * nWinCentre > (510-nWindWidth))
		{
			return false;
		}

		if (!isValid())
		{
			return false;
		}

		if (PIXEL_FORMAT_MONO8 != m_pixFmt)
		{
			return false;
		}


		unsigned char *pImg = m_pBuffer;
		unsigned int nW = m_nWidth;
		unsigned int nH = m_nHeight;

		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(nW, nH, true, PIXEL_FORMAT_MONO8))
			{
				return false;
			}

			pImg = pDstImg->getBuffer();
		}

		float f_min = (float)((2 * nWinCentre - nWindWidth) / 2.0 + 0.5);
		float f_max = (float)((2 * nWinCentre + nWindWidth) / 2.0 + 0.5);

		float dFactor;
		dFactor = (float)255 / (f_max - f_min);

		//循环变量
		long i;

		long N = nH * nW;

		for (i = 0; i < N; i++)
		{
			if (m_pBuffer[i] < f_min)
			{
				pImg[i] = 0;
			}
			else if (m_pBuffer[i] > f_max)
			{
				pImg[i] = 255;
			}
			else
			{
				pImg[i] = (unsigned char)((m_pBuffer[i] - f_min)*dFactor);
			}

			if (pImg[i] < 0)	pImg[i] = 0;
			if (pImg[i] > 255)	pImg[i] = 255;
		}

		return true;
	}


	bool convolute(double aRet[10],
		unsigned char *pImg, int nW, int nP, int nH,
		double *pKernelC, int nRadiusC,
		double *pKernelS, int nLengthS,
		int iXc, int iYc)
	{
		int nLengthC = 2 * nRadiusC + 1;

		int nC = nP / nW;

		if (nC > 10)
			return false;

		int pos = iYc * nP + iXc * nC;

		for (int c = 0; c < nC; c++)
		{
			aRet[c] = pImg[pos + c];
			//ofstream ofs("bilateralKernel.txt");
			double dG = 0.0;
			double dW = 0.0;
			for (int y = iYc - nRadiusC; y <= iYc + nRadiusC; y++)
			{
				for (int x = iXc - nRadiusC; x <= iXc + nRadiusC; x++)
				{
					double w = pKernelC[(y - (iYc - nRadiusC))*nLengthC + (x - (iXc - nRadiusC))] *
						pKernelS[abs(pImg[y*nP + x * nC + c] - pImg[pos + c])];

					dG += pImg[y*nP + x * nC + c] * w;

					dW += w;
					//ofs<<w<<endl;
				}
			}

			if (dW > 0.0)
				aRet[c] = dG / dW;
		}

		return true;
	}

	bool xImage::bilateralFilter(double dSigmaC, double dSigmaS, xImage *pDstImg)
	{
		if (!isValid())
		{
			return false;
		}

		const double dSqS2 = 2.0 * dSigmaS * dSigmaS;

		const double dSqC2 = 2.0 * dSigmaC * dSigmaC;

		//similarity weights
		const int nGrayLevel = 256;
		double *pKernelS = new double[nGrayLevel];
		for (int i = 0; i < nGrayLevel; i++)
		{
			pKernelS[i] = exp(-i * i / dSqS2);
		}

		//ofstream ofs("KernelS.txt");
		//if (ofs)
		//{
		//	for (int i=0; i<nGrayLevel; i++)
		//		ofs<<i<<"\t"<<pKernelS[i]<<endl;
		//}

				//closeness weights
		vector<double> aKernelC;
		getGaussianKernel(aKernelC, dSigmaC);

		int nRadiusC = 0;
		while ((2 * nRadiusC + 1)*(2 * nRadiusC + 1) < aKernelC.size())
		{
			nRadiusC++;
		}

		if ((2 * nRadiusC + 1)*(2 * nRadiusC + 1) != aKernelC.size())
		{
			delete[]pKernelS;
			return false;
		}

		xImage dstImg;
		if (!copyTo(dstImg))
		{
			delete[]pKernelS;
			return false;
		}

		int nC = getChannels();

		unsigned char *pDstBuffer = dstImg.getBuffer();

		if (2 * nRadiusC + 1 <= m_nWidth && 2 * nRadiusC + 1 < m_nHeight)
		{
			int xs = nRadiusC;
			int xe = m_nWidth - nRadiusC;
			int ys = nRadiusC;
			int ye = m_nHeight - nRadiusC;

			double aRet[10];

			double *pKernelC = aKernelC.data();

			for (int y = ys; y < ye; y++)
			{
				for (int x = xs; x < xe; x++)
				{
					if (convolute(aRet, m_pBuffer, m_nWidth, m_nPitch, m_nHeight, pKernelC, nRadiusC, pKernelS, nGrayLevel, x, y))
					{
						for (int c = 0; c < nC; c++)
						{
							pDstBuffer[y*m_nPitch + x * nC + c] = (unsigned char)(aRet[c] > 255.0 ? 255 : (aRet[c] < 0.0 ? 0 : aRet[c]));
						}
					}
				}
			}
		}

		if (nullptr == pDstImg)
		{
			memcpy(m_pBuffer, pDstBuffer, m_nHeight*m_nPitch * sizeof(unsigned char));
		}
		else
		{
			pDstImg->copyFrom(dstImg);
		}

		delete[]pKernelS;

		return false;
	}

	bool xImage::morph_dilate(StructuringElement se, xImage *pDstImg)
	{
		if (!isValid() || !isGrayscale() || !se.isValid())
		{
			return false;
		}

		xImage img;
		unsigned char *pImg = nullptr;
		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, true, PIXEL_FORMAT_MONO8))
			{
				return false;
			}
			pImg = pDstImg->getBuffer();
		}
		else
		{
			if (!img.create(m_nWidth, m_nHeight, true, PIXEL_FORMAT_MONO8))
			{
				return false;
			}
			pImg = img.getBuffer();
		}

		//initialize
		memcpy(pImg, m_pBuffer, m_nHeight*m_nPitch * sizeof(unsigned char));

		int nW = m_nWidth;
		int nH = m_nHeight;

		//radius in x and y
		int nRx = se.szKernel.cx / 2;
		int nRy = se.szKernel.cy / 2;

		for (int y = 0; y < nH; y++)
		{
			for (int x = 0; x < nW; x++)
			{
				int xs = max(0, x - nRx);
				int xe = min(nW - 1, x + se.szKernel.cx - nRx - 1);
				int ys = max(0, y - nRy);
				int ye = min(nH - 1, y + se.szKernel.cy - nRy - 1);

				unsigned char ucMaxVal = m_pBuffer[y*m_nPitch + x];

				for (int yp = ys; yp <= ye; yp++)
				{
					for (int xp = xs; xp <= xe; xp++)
					{
						if (se.pKernel[(yp-ys)*se.szKernel.cx + (xp-xs)] == 255)
						{
							if (ucMaxVal < m_pBuffer[yp*m_nPitch + xp])
							{
								ucMaxVal = m_pBuffer[yp*m_nPitch + xp];
							}
						}
					}
				}

				if (ucMaxVal > m_pBuffer[y*m_nPitch + x])
				{
					pImg[y*m_nPitch + x] = ucMaxVal;
				}
			}
		}

		if (nullptr == pDstImg)
		{
			memcpy(m_pBuffer, pImg, m_nHeight*m_nPitch * sizeof(unsigned char));
		}

		return true;
	}

	bool xImage::morph_erode(StructuringElement se, xImage *pDstImg)
	{
		if (!isValid() || !isGrayscale() || !se.isValid())
		{
			return false;
		}

		xImage img;
		unsigned char *pImg = nullptr;
		if (nullptr != pDstImg)
		{
			if (!pDstImg->create(m_nWidth, m_nHeight, true, PIXEL_FORMAT_MONO8))
			{
				return false;
			}
			pImg = pDstImg->getBuffer();
		}
		else
		{
			if (!img.create(m_nWidth, m_nHeight, true, PIXEL_FORMAT_MONO8))
			{
				return false;
			}
			pImg = img.getBuffer();
		}

		//initialize
		memcpy(pImg, m_pBuffer, m_nHeight*m_nPitch * sizeof(unsigned char));

		int nW = m_nWidth;
		int nH = m_nHeight;

		//radius in x and y
		int nRx = se.szKernel.cx / 2;
		int nRy = se.szKernel.cy / 2;

		for (int y = 0; y < nH; y++)
		{
			for (int x = 0; x < nW; x++)
			{
				int xs = max(0, x - nRx);
				int xe = min(nW - 1, x + se.szKernel.cx - nRx - 1);
				int ys = max(0, y - nRy);
				int ye = min(nH - 1, y + se.szKernel.cy - nRy - 1);

				unsigned char ucMinVal = m_pBuffer[y*m_nPitch + x];

				for (int yp = ys; yp <= ye; yp++)
				{
					for (int xp = xs; xp <= xe; xp++)
					{
						if (se.pKernel[(yp - ys)*se.szKernel.cx + (xp - xs)] == 255)
						{
							if (ucMinVal > m_pBuffer[yp*m_nPitch + xp])
							{
								ucMinVal = m_pBuffer[yp*m_nPitch + xp];
							}
						}
					}
				}

				if (ucMinVal < m_pBuffer[y*m_nPitch + x])
				{
					pImg[y*m_nPitch + x] = ucMinVal;
				}
			}
		}

		if (nullptr == pDstImg)
		{
			memcpy(m_pBuffer, pImg, m_nHeight*m_nPitch * sizeof(unsigned char));
		}

		return true;
	}

	bool xImage::morph_open(StructuringElement se, xImage *pDstImg)
	{
		if (nullptr == pDstImg)
		{
			if (morph_erode(se, nullptr))
			{
				return morph_dilate(se, nullptr);
			}
		}
		else
		{			
			if (morph_erode(se, pDstImg))
			{
				return pDstImg->morph_dilate(se, nullptr);
			}
		}

		return false;
	}

	bool xImage::morph_close(StructuringElement se, xImage *pDstImg)
	{
		if (nullptr == pDstImg)
		{
			if (morph_dilate(se, nullptr))
			{
				return morph_erode(se, nullptr);
			}
		}
		else
		{
			if (morph_dilate(se, pDstImg))
			{
				return pDstImg->morph_erode(se, nullptr);
			}
		}

		return false;
	}

	bool xImage::morph_tophat(StructuringElement se, xImage *pDstImg)
	{
		xImage imgO;
		if (!morph_open(se, &imgO))
		{
			return false;
		}	
			
		if (nullptr == pDstImg)
		{
			*this -= imgO;
		}
		else
		{
			*pDstImg = *this - imgO;
		}

		return true;
	}

	bool xImage::morph_bottomhat(StructuringElement se, xImage *pDstImg)
	{
		xImage imgC;
		if (!morph_close(se, &imgC))
		{
			return false;
		}
			
		if (nullptr == pDstImg)
		{
			*this = imgC - *this;
		}
		else
		{
			*pDstImg = imgC - *this;
		}

		return true;
	}


	bool xImage::morphology(StructuringElement se, EMorphType eType, xImage *pDstImg)
	{
		switch (eType)
		{
		case MORPH_TYPE_DILATE:
			return morph_dilate(se, pDstImg);

		case MORPH_TYPE_ERODE:
			return morph_erode(se, pDstImg);

		case MORPH_TYPE_OPEN:
			return morph_open(se, pDstImg);

		case MORPH_TYPE_CLOSE:
			return morph_close(se, pDstImg);

		case MORPH_TYPE_TOPHAT:
			return morph_tophat(se, pDstImg);

		case MORPH_TYPE_BOTTOMHAT:
			return morph_bottomhat(se, pDstImg);

		default:
			break;
		}

		return false;
	}


	bool xImage::filter2D(vector<double> &aKernel, xImage *pDstImg)
	{
		int nRadius = 0;
		while ((2 * nRadius + 1)*(2 * nRadius + 1) < aKernel.size())
		{
			nRadius++;
		}

		if ((2 * nRadius + 1)*(2 * nRadius + 1) != aKernel.size())
			return false;

		return filter2D(aKernel.data(), nRadius, pDstImg);
	}

	bool convolute(double aRet[10], unsigned char *pImg, int nW, int nP, int nH, double *pKernel, int nRadius, int iXc, int iYc)
	{
		int nLength = 2 * nRadius + 1;

		int nC = nP / nW;

		if (nC > 10)
			return false;

		for (int c = 0; c < nC; c++)
		{
			double dSum = 0.0;
			for (int y = iYc - nRadius; y <= iYc + nRadius; y++)
				for (int x = iXc - nRadius; x <= iXc + nRadius; x++)
				{
					dSum += pImg[y*nP + x * nC + c] * pKernel[(y - (iYc - nRadius))*nLength + (x - (iXc - nRadius))];
				}

			aRet[c] = dSum;
		}

		return true;
	}

	bool xImage::filter2D(double *pKernel, int nRadius, xImage *pDstImg)
	{
		if (!isValid())
			return false;

		if (pKernel == nullptr || nRadius < 0)
			return false;

		xImage dstImg;

		if (!copyTo(dstImg))
			return false;

		int nC = getChannels();

		unsigned char *pDstBuffer = dstImg.getBuffer();

		if (2 * nRadius + 1 <= m_nWidth && 2 * nRadius + 1 < m_nHeight)
		{
			int xs = nRadius;
			int xe = m_nWidth - nRadius;
			int ys = nRadius;
			int ye = m_nHeight - nRadius;

			double aRet[10];

			for (int y = ys; y < ye; y++)
			{
				for (int x = xs; x < xe; x++)
				{
					if (convolute(aRet, m_pBuffer, m_nWidth, m_nPitch, m_nHeight, pKernel, nRadius, x, y))
					{
						for (int c = 0; c < nC; c++)
						{
							pDstBuffer[y*m_nPitch + x * nC + c] = (unsigned char)(aRet[c] > 255.0 ? 255 : (aRet[c] < 0.0 ? 0 : aRet[c]));
						}
					}
				}
			}
		}

		if (nullptr == pDstImg)
		{
			memcpy(m_pBuffer, pDstBuffer, m_nHeight*m_nPitch * sizeof(unsigned char));
		}
		else
		{
			pDstImg->copyFrom(dstImg);
		}

		return true;
	}

	bool xImage::smoothGaussian3()
	{
		return gaussianSmooth3(m_pBuffer, m_nWidth, m_nPitch, m_nHeight);
	}

	bool xImage::smoothGaussian5()
	{
		return gaussianSmooth5(m_pBuffer, m_nWidth, m_nPitch, m_nHeight);
	}

	bool xImage::smoothGaussian(double dSigma, xImage *pDstImg)
	{
		vector<double> aK;
		if (getGaussianKernel(aK, dSigma))
		{
			return filter2D(aK, pDstImg);
		}

		return false;
	}

	template<class T>
	T compare(const void *a, const void *b)
	{
		return *(T*)a - *(T*)b;
	}

	template<class T>
	T Median(T *pArray, int begin, int end)
	{
		T *pA = new T[end - begin + 1];
		memcpy(pA, pArray + begin, (end - begin + 1) * sizeof(T));
		qsort(pA, (end - begin + 1), sizeof(T), compare);
		T m = *(pA + (end - begin + 1) / 2);
		delete[]pA;

		return m;
	}

	bool xImage::medianFilter(int nRadius, xImage *pDstImg)
	{
		if (!isValid())
			return false;

		if (nRadius < 0)
			return false;

		xImage dstImg;
		if (!copyTo(dstImg))
			return false;

		int nC = getChannels();

		unsigned char *pBuf = dstImg.getBuffer();

		//对图像中的矩形区域进行中值滤波
		for (int y = nRadius; y < m_nHeight - nRadius; y++)
		{
			for (int x = nRadius; x < m_nWidth - nRadius; x++)
			{
				int ys = max(0, y - nRadius);
				int ye = min(m_nHeight, y + nRadius);
				int xs = max(0, x - nRadius);
				int xe = min(m_nWidth, x + nRadius);

				int w = xe - xs + 1;
				int h = ye - ys + 1;
				int *pImg = new int[w * h];
				for (int c = 0; c < nC; c++)
				{
					for (int i = ys; i <= ye; i++)
						for (int j = xs; j <= xe; j++)
							pImg[(i - ys)*w + (j - xs)] = m_pBuffer[i*m_nPitch + j * nC + c];

					pBuf[y*m_nPitch + x * nC + c] = (unsigned char)Median(pImg, 0, w*h - 1);
				}

				delete pImg;
			}
		}

		if (nullptr == pDstImg)
		{
			memcpy(m_pBuffer, pBuf, m_nHeight*m_nPitch * sizeof(unsigned char));
		}
		else
		{
			pDstImg->copyFrom(dstImg);
		}

		return true;
	}

	bool xImage::enhanceLog(ImageRect *roi)
	{
		if (!isValid())
			return false;

		int xs, xe, ys, ye;
		if (roi == nullptr)
		{
			xs = 0;
			xe = m_nWidth - 1;
			ys = 0;
			ye = m_nHeight - 1;
		}
		else
		{
			xs = roi->xs;
			xe = roi->xe;
			ys = roi->ys;
			ye = roi->ye;
		}

		if (xs < 0 || xs > xe || xe >= m_nWidth ||
			ys < 0 || ys > ye || ye >= m_nHeight)
		{
			return false;
		}


		unsigned char lut[256] = { 0 };

		double temp = 255 / log(256.0);

		for (int i = 0; i < 256; i++)
		{
			lut[i] = (unsigned char)(temp * log(i + 1.0) + 0.5);
		}

		int nC = getChannels();

		for (int c = 0; c < nC; c++)
		{
			unsigned char *pImg = m_pBuffer + ys * m_nPitch + nC * xs;

			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					pImg[pos + c] = lut[pImg[pos + c]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}

		return true;
	}

	bool xImage::enhanceExp(ImageRect *roi)
	{
		if (!isValid())
			return false;

		int xs, xe, ys, ye;
		if (roi == nullptr)
		{
			xs = 0;
			xe = m_nWidth - 1;
			ys = 0;
			ye = m_nHeight - 1;
		}
		else
		{
			xs = roi->xs;
			xe = roi->xe;
			ys = roi->ys;
			ye = roi->ye;
		}

		if (xs < 0 || xs > xe || xe >= m_nWidth ||
			ys < 0 || ys > ye || ye >= m_nHeight)
		{
			return false;
		}

		unsigned char lut[256] = { 0 };

		double temp = 1 / log(255.0);

		for (int i = 0; i < 256; i++)
		{
			float t = temp * i * i + 0.5;
			if (t < 0)
			{
				t = 0;
			}
			else if (t > 255)
			{
				t = 255;
			}

			lut[i] = (unsigned char)(t);
		}

		int nC = getChannels();

		for (int c = 0; c < nC; c++)
		{
			unsigned char *pImg = m_pBuffer + ys * m_nPitch + nC * xs;

			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					pImg[pos + c] = lut[pImg[pos + c]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}

		return true;
	}

	bool xImage::calcWhiteBalanceGW(float &dRGain, float &dGGain, float &dBGain, int nMaxGray, ImageRect *roi)
	{
		if (!isValid())
			return false;

		if (m_nBpp < 24)
			return false;

		dRGain = dGGain = dBGain = 1.0;

		int xs, xe, ys, ye;
		if (roi == nullptr)
		{
			xs = 0;
			xe = m_nWidth - 1;
			ys = 0;
			ye = m_nHeight - 1;
		}
		else
		{
			xs = roi->xs;
			xe = roi->xe;
			ys = roi->ys;
			ye = roi->ye;
		}

		int pixel_cnt = (xe - xs + 1) * (ye - ys + 1);

		int h = m_nHeight;
		int w = m_nWidth;
		int p = m_nPitch;
		int c = p / w;

		if (xs < 0 || xs > xe || xe >= w ||
			ys < 0 || ys > ye || ye >= h)
		{
			return false;
		}

		unsigned char *img = m_pBuffer + ys * p + c * xs;

		int ave_r = 0, ave_g = 0, ave_b = 0;

		if (isBGR())
		{
			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					ave_b += img[pos + 0];
					ave_g += img[pos + 1];
					ave_r += img[pos + 2];
					pos += c;
				}
				img += p;
			}
		}
		else
		{
			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					ave_r += img[pos + 0];
					ave_g += img[pos + 1];
					ave_b += img[pos + 2];
					pos += c;
				}
				img += p;
			}
		}

		float max = ave_r;
		if (max < ave_g)
			max = ave_g;
		if (max < ave_b)
			max = ave_b;

		if (nMaxGray != -1)
		{
			max = nMaxGray * pixel_cnt;
		}

		if (ave_b != 0)
		{
			dBGain = max / ave_b;
		}
		if (ave_g != 0)
		{
			dGGain = max / ave_g;
		}
		if (ave_r != 0)
		{
			dRGain = max / ave_r;
		}


		return true;
	}

	bool xImage::calcWhiteBalancePR(float &dRGain, float &dGGain, float &dBGain, int nMaxGray, double dRatio, ImageRect *roi)
	{
		if (!isValid())
			return false;

		if (m_nBpp < 24)
			return false;

		if (dRatio < 0.0 || dRatio > 1.0)
			return false;

		dRGain = dGGain = dBGain = 1.0;

		int xs, xe, ys, ye;
		if (roi == nullptr)
		{
			xs = 0;
			xe = m_nWidth - 1;
			ys = 0;
			ye = m_nHeight - 1;
		}
		else
		{
			xs = roi->xs;
			xe = roi->xe;
			ys = roi->ys;
			ye = roi->ye;
		}

		int pixel_cnt = (xe - xs) * (ye - ys);

		int w = m_nWidth;
		int h = m_nHeight;
		int p = m_nPitch;
		int c = p / w;

		if (xs < 0 || xs > xe || xe >= w ||
			ys < 0 || ys > ye || ye >= h)
		{
			return false;
		}

		unsigned char *img = m_pBuffer + ys * p + c * xs;

		int ave_r = 0, ave_g = 0, ave_b = 0;

		int COLOR_R, COLOR_G, COLOR_B;
		if (isBGR())
		{
			COLOR_R = 2;
			COLOR_G = 1;
			COLOR_B = 0;
		}
		else
		{
			COLOR_R = 0;
			COLOR_G = 1;
			COLOR_B = 2;
		}

		const int nL = 768;
		long histRGB[nL];
		memset(histRGB, 0, nL * sizeof(long));

		for (int y = ys; y <= ye; y++)
		{
			int pos = 0;
			for (int x = xs; x <= xe; x++)
			{
				int sum = img[pos + 0] + img[pos + 1] + img[pos + 2];
				histRGB[sum]++;
				pos += c;
			}
			img += p;
		}

		int nT = -1;
		double dThNum = pixel_cnt * dRatio;
		double dSum = 0.0;
		for (int k = 767; k >= 0; k--)
		{
			dSum += histRGB[k];
			if (dSum > dThNum)
			{
				nT = k;
				break;
			}
		}

		img = m_pBuffer + ys * p + c * xs;

		int nCnt = 0;
		for (int y = ys; y <= ye; y++)
		{
			int pos = 0;
			for (int x = xs; x <= xe; x++)
			{
				if (img[pos] + img[pos + 1] + img[pos + 2] > nT)
				{
					ave_r += img[pos + COLOR_R];
					ave_g += img[pos + COLOR_G];
					ave_b += img[pos + COLOR_B];

					nCnt++;
				}
				pos += c;
			}
			img += p;
		}

		float max = ave_r;
		if (max < ave_g)
			max = ave_g;
		if (max < ave_b)
			max = ave_b;

		if (nMaxGray != -1)
		{
			max = nMaxGray * nCnt;
		}

		if (ave_b != 0)
		{
			dBGain = max / ave_b;
		}
		if (ave_g != 0)
		{
			dGGain = max / ave_g;
		}
		if (ave_r != 0)
		{
			dRGain = max / ave_r;
		}

		return true;
	}

	bool xImage::calcWhiteBalance(float &dRGain, float &dGGain, float &dBGain, WBParam *pWBParam, ImageRect *aoi)
	{
		WBParam param;

		if (nullptr != pWBParam)
		{
			param = *pWBParam;
		}

		switch (param.method)
		{
		case WB_GW:
			return calcWhiteBalanceGW(dRGain, dGGain, dBGain, param.nMaxGray, aoi);

		case WB_PR:
			return calcWhiteBalancePR(dRGain, dGGain, dBGain, param.nMaxGray, param.dRatio, aoi);

		default:
			break;
		}

		return false;
	}

	bool xImage::calcLut(Lut<unsigned char> &lut, float dRGain, float dGGain, float dBGain)
	{
		if (!lut.reset(256, 3) || lut.empty())
		{
			return false;
		}

		for (int i = 0; i < 256; i++)
		{
			int b = dBGain * i;
			int g = dGGain * i;
			int r = dRGain * i;
			lut.m_rTable[i] = (r < 0 ? 0 : (r > 255 ? 255 : (unsigned char)(r)));
			lut.m_gTable[i] = (g < 0 ? 0 : (g > 255 ? 255 : (unsigned char)(g)));
			lut.m_bTable[i] = (b < 0 ? 0 : (b > 255 ? 255 : (unsigned char)(b)));
		}

		return true;
	}

	bool xImage::whiteBalance(Lut<unsigned char> &lut, ImageRect *roi)
	{
		if (!isValid())
			return false;

		if (m_nBpp < 24)
			return false;

		if (lut.empty())
		{
			return false;
		}

		int xs, xe, ys, ye;
		if (roi == nullptr)
		{
			xs = 0;
			xe = m_nWidth-1;
			ys = 0;
			ye = m_nHeight-1;
		}
		else
		{
			xs = roi->xs;
			xe = roi->xe;
			ys = roi->ys;
			ye = roi->ye;
		}

		if (0 > xs || xs > xe || xe >= m_nWidth ||
			0 > ys || ys > ye || ye >= m_nHeight)
		{
			return false;
		}

		int w = m_nWidth;
		int p = m_nPitch;
		int c = p / w;

		unsigned char *img = m_pBuffer + ys * p + c * xs;

		if (isBGR())
		{
			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					img[pos + 0] = lut.m_bTable[img[pos + 0]];
					img[pos + 1] = lut.m_gTable[img[pos + 1]];
					img[pos + 2] = lut.m_rTable[img[pos + 2]];
					pos += c;
				}
				img += p;
			}
		}
		else
		{
			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					img[pos + 0] = lut.m_rTable[img[pos + 0]];
					img[pos + 1] = lut.m_gTable[img[pos + 1]];
					img[pos + 2] = lut.m_bTable[img[pos + 2]];
					pos += c;
				}
				img += p;
			}
		}

		return true;
	}

	bool xImage::whiteBalance(float dRGain, float dGGain, float dBGain, ImageRect *roi)
	{
		if (!isValid())
			return false;

		if (m_nBpp < 24)
			return false;


		int xs, xe, ys, ye;
		if (roi == nullptr)
		{
			xs = 0;
			xe = m_nWidth - 1;
			ys = 0;
			ye = m_nHeight - 1;
		}
		else
		{
			xs = roi->xs;
			xe = roi->xe;
			ys = roi->ys;
			ye = roi->ye;
		}

		if (0 > xs || xs > xe || xe >= m_nWidth ||
			0 > ys || ys > ye || ye >= m_nHeight)
		{
			return false;
		}

		Lut<unsigned char> lut;
		if (!calcLut(lut, dRGain, dGGain, dBGain))
		{
			return false;
		}
		

		int w = m_nWidth;
		int p = m_nPitch;
		int c = p / w;

		unsigned char *img = m_pBuffer + ys * p + c * xs;

		if (isBGR())
		{
			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					img[pos + 0] = lut.m_bTable[img[pos + 0]];
					img[pos + 1] = lut.m_gTable[img[pos + 1]];
					img[pos + 2] = lut.m_rTable[img[pos + 2]];
					pos += c;
				}
				img += p;
			}
		}
		else
		{
			for (int y = ys; y <= ye; y++)
			{
				int pos = 0;
				for (int x = xs; x <= xe; x++)
				{
					img[pos + 0] = lut.m_rTable[img[pos + 0]];
					img[pos + 1] = lut.m_gTable[img[pos + 1]];
					img[pos + 2] = lut.m_bTable[img[pos + 2]];
					pos += c;
				}
				img += p;
			}
		}

		return true;
	}

	bool xImage::whiteBalance(WBParam *pWBParam, ImageRect *roi)
	{
		float dRGain, dGGain, dBGain;
		if (!calcWhiteBalance(dRGain, dGGain, dBGain, pWBParam, roi))
		{
			return false;
		}

		Lut<unsigned char> lut;
		if (!calcLut(lut, dRGain, dGGain, dBGain))
		{
			return false;
		}

		if (!whiteBalance(lut))
		{
			return false;
		}

		return true;
	}




	bool xImage::saturate(unsigned char ucSatuVal)
	{
		if (!isValid())
		{
			return false;
		}

		unsigned nC = getChannels();

		unsigned char nMaxVal = 0;

		unsigned char *pImg = m_pBuffer;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned pos = 0;
			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					if (pImg[pos + c] > nMaxVal)
					{
						nMaxVal = pImg[pos + c];
					}
				}

				pos += nC;
			}

			pImg += m_nPitch;
		}

		if (nMaxVal >= ucSatuVal)
		{
			return true;
		}

		int nOffset = ucSatuVal - nMaxVal;

		pImg = m_pBuffer;

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned pos = 0;
			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					pImg[pos + c] += nOffset;
				}

				pos += nC;
			}

			pImg += m_nPitch;
		}

		return true;
	}



	inline int checkValue(int value)
	{
		return (value & ~0xff) == 0 ? value : value > 255 ? 255 : 0;
	}

	bool xImage::adjustGain(float fRGain, float fGGain, float fBGain)
	{
		if (!isValid())
			return false;

		if (fRGain < 0.0 || fRGain > 10.0 ||
			fGGain < 0.0 || fGGain > 10.0 ||
			fBGain < 0.0 || fBGain > 10.0)
		{
			return false;
		}

		unsigned char lut_r[256], lut_g[256], lut_b[256];
		for (int i = 0; i < 256; i++)
		{
			float b = fBGain * i;
			float g = fGGain * i;
			float r = fRGain * i;
			lut_r[i] = (r < 0.0 ? 0 : (r > 255 ? 255 : (unsigned char)(r)));
			lut_g[i] = (g < 0.0 ? 0 : (g > 255 ? 255 : (unsigned char)(g)));
			lut_b[i] = (b < 0.0 ? 0 : (b > 255 ? 255 : (unsigned char)(b)));
		}

		int h = m_nHeight;
		int w = m_nWidth;
		int p = m_nPitch;
		int c = p / w;

		if (c >= 3)
		{
			unsigned char *img = m_pBuffer;

			if (isBGR())
			{
				for (int y = 0; y < h; y++)
				{
					int pos = 0;
					for (int x = 0; x < w; x++)
					{
						img[pos + 0] = lut_b[img[pos + 0]];
						img[pos + 1] = lut_g[img[pos + 1]];
						img[pos + 2] = lut_r[img[pos + 2]];
						pos += c;
					}
					img += p;
				}
			}
			else
			{
				for (int y = 0; y < h; y++)
				{
					int pos = 0;
					for (int x = 0; x < w; x++)
					{
						img[pos + 0] = lut_r[img[pos + 0]];
						img[pos + 1] = lut_g[img[pos + 1]];
						img[pos + 2] = lut_b[img[pos + 2]];
						pos += c;
					}
					img += p;
				}
			}

			return true;
		}

		return false;
	}


	bool xImage::adjustBrightnessAndContrast(int brightnessOffset, int contrastLevel, unsigned char threshold)
	{
		if (!isValid())
			return false;

		if (brightnessOffset == 0 && contrastLevel == 0)
			return true;

		float cv = (contrastLevel <= -255) ? -1.0f : contrastLevel / 255.0f;
		if (contrastLevel > 0 && contrastLevel < 255)
			cv = 1.0f / (1.0f - cv) - 1.0f;

		unsigned char lut[256] = { 0 };

		for (int i = 0; i < 256; i++)
		{
			int v = contrastLevel > 0 ? checkValue(i + brightnessOffset) : i;
			if (contrastLevel >= 255)
				v = v >= threshold ? 255 : 0;
			else
				v = checkValue(v + (int)((v - threshold) * cv + 0.5f));
			lut[i] = contrastLevel <= 0 ? checkValue(v + brightnessOffset) : v;
		}

		unsigned char *pImg = m_pBuffer;

		unsigned nC = getChannels();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned pos = 0;
			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					pImg[pos + c] = lut[pImg[pos + c]];
				}
				pos += nC;
			}
			pImg += m_nPitch;
		}

		return true;
	}

	bool xImage::adjustBrightness(int brightnessOffset)
	{
		if (!isValid())
			return false;

		if (brightnessOffset < -255)
			brightnessOffset = -255;
		else if (brightnessOffset > 255)
			brightnessOffset = 255;

		unsigned char lut[256] = { 0 };

		for (int i = 0; i < 256; i++)
		{
			int g = brightnessOffset + i;
			if (g < 0)
				lut[i] = 0;
			else if (g > 255)
				lut[i] = 255;
			else
				lut[i] = g;
		}


		unsigned char *pImg = m_pBuffer;

		unsigned nC = getChannels();

		if (nC < 3)
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pImg[pos + 0] = lut[pImg[pos + 0]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}
		else
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pImg[pos + 0] = lut[pImg[pos + 0]];
					pImg[pos + 1] = lut[pImg[pos + 1]];
					pImg[pos + 2] = lut[pImg[pos + 2]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}

		return true;
	}

	bool xImage::adjustContrast(int contrastLevel)
	{
		if (!isValid())
			return false;

		if (contrastLevel < -255)
			contrastLevel = -255;
		else if (contrastLevel > 255)
			contrastLevel = 255;

		double f = 259.0 * (contrastLevel + 255.0) / 255.0 / (259.0 - contrastLevel);

		unsigned char lut[256] = { 0 };

		for (int i = 0; i < 256; i++)
		{
			double g = f * (i - 128) + 128;
			if (g < 0)
				lut[i] = 0;
			else if (g > 255)
				lut[i] = 255;
			else
				lut[i] = round(g);
		}


		unsigned char *pImg = m_pBuffer;

		unsigned nC = getChannels();

		if (nC < 3)
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pImg[pos + 0] = lut[pImg[pos + 0]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}
		else
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pImg[pos + 0] = lut[pImg[pos + 0]];
					pImg[pos + 1] = lut[pImg[pos + 1]];
					pImg[pos + 2] = lut[pImg[pos + 2]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}

		return true;
	}

	bool xImage::adjustGamma(double dGamma)
	{
		if (!isValid())
			return false;

		dGamma = 1.0 / dGamma;

		unsigned char lut[256] = { 0 };

		for (int i = 0; i < 256; i++)
		{
			lut[i] = (unsigned char)(255 * pow(i / 255.0, dGamma));
		}

		unsigned char *pImg = m_pBuffer;

		unsigned nC = getChannels();

		if (nC < 3)
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pImg[pos + 0] = lut[pImg[pos + 0]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}
		else
		{
			for (unsigned y = 0; y < m_nHeight; y++)
			{
				unsigned pos = 0;
				for (unsigned x = 0; x < m_nWidth; x++)
				{
					pImg[pos + 0] = lut[pImg[pos + 0]];
					pImg[pos + 1] = lut[pImg[pos + 1]];
					pImg[pos + 2] = lut[pImg[pos + 2]];
					pos += nC;
				}
				pImg += m_nPitch;
			}
		}

		return true;
	}

	bool xImage::inverse()
	{
		if (!isValid())
			return false;

		unsigned char *pImg = m_pBuffer;

		unsigned nC = getChannels();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned pos = 0;
			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					pImg[pos + c] = 255 - pImg[pos + c];
				}
				pos += nC;
			}
			pImg += m_nPitch;
		}

		return true;
	}

	bool xImage::solarise(unsigned char threshold)
	{
		if (!isValid())
			return false;

		unsigned char *pImg = m_pBuffer;

		unsigned nC = getChannels();

		for (unsigned y = 0; y < m_nHeight; y++)
		{
			unsigned pos = 0;
			for (unsigned x = 0; x < m_nWidth; x++)
			{
				for (unsigned c = 0; c < nC; c++)
				{
					if (pImg[pos + c] >= threshold)
						pImg[pos + c] = threshold;
					//pImg[pos+c] = 255 - pImg[pos+c];
				}
				pos += nC;
			}
			pImg += m_nPitch;
		}

		return true;
	}

	bool xImage::resizeNNI(int nNewW, int nNewH, xImage *pDesImg)
	{
		if (nNewW <= 0 || nNewH <= 0)
		{
			return false;
		}

		if (!isValid())
		{
			return false;
		}

		int w0 = getWidth();
		int h0 = getHeight();
		int pitch0 = getPitch();

		xImage desImg;
		if (!desImg.create(nNewW, nNewH, m_bAligned, m_pixFmt, m_byrFmt))
		{
			return false;
		}

		int w1 = desImg.getWidth();
		int h1 = desImg.getHeight();
		int pitch1 = desImg.getPitch();

		int nC = pitch1 / w1;

		float fw = float(w0) / w1;
		float fh = float(h0) / h1;

		int *arr_x = new int[w1];
		int *arr_y = new int[h1];
		for (int y = 0; y < h1; y++)
		{
			arr_y[y] = int(y*fh);
		}
		for (int x = 0; x < w1; x++)
		{
			arr_x[x] = int(x*fw);
		}

		unsigned char* pSrc = (unsigned char*)getBuffer();
		unsigned char* pDst = (unsigned char*)desImg.getBuffer();
		unsigned char* p0, *p1;
		for (int y = 0; y < h1; y++)
		{
			p0 = pSrc + pitch0 * arr_y[y];
			p1 = pDst + pitch1 * y;
			for (int x = 0; x < w1; x++)
			{
				memcpy(p1 + nC * x, p0 + arr_x[x] * nC, nC);
			}
		}

		delete[]arr_x;
		delete[]arr_y;

		if (nullptr == pDesImg)
		{
			copyFrom(desImg);
		}
		else
		{
			pDesImg->copyFrom(desImg);
		}

		return true;
	}

	bool xImage::resizeMA(int nNewW, int nNewH, xImage *pDstImg)
	{
		if (nNewW <= 0 || nNewH <= 0)
		{
			return false;
		}

		if (!isValid())
			return false;

		int w0 = getWidth();
		int h0 = getHeight();
		int p0 = getPitch();
		int nC = getChannels();
		unsigned char *pImg0 = getBuffer();

		xImage dstImg;
		if (!dstImg.create(nNewW, nNewH, m_bAligned, m_pixFmt, m_byrFmt))
		{
			return false;
		}

		int w1 = dstImg.getWidth();
		int h1 = dstImg.getHeight();
		int p1 = dstImg.getPitch();
		unsigned char *pImg1 = dstImg.getBuffer();


		float fw = float(w0) / w1;
		float fh = float(h0) / h1;

		int dx = (int)(fw);
		int dy = (int)(fh);

		int *arr_x = new int[w1];
		int *arr_y = new int[h1];
		for (int y = 0; y < h1; y++)
		{
			arr_y[y] = (int)(y*fh);
		}
		for (int x = 0; x < w1; x++)
		{
			arr_x[x] = (int)(x*fw);
		}

		if (nC == 1)
		{
			int nCnt = w0 * h0;
			int *pSum0 = new int[nCnt];
			int pos0 = 0;
			int pos2 = 0;
			for (int y = 0; y < h0; y++)
			{
				int pos1 = pos0;
				for (int x = 0; x < w0; x++)
				{
					int pos3 = pos2 + x;

					if (x > 0)
					{
						if (y > 0)
						{
							pSum0[pos3] = pSum0[pos3 - 1] + pSum0[pos3 - w0] - pSum0[pos3 - w0 - 1] + pImg0[pos1];
						}
						else
						{
							pSum0[pos3] = pSum0[pos3 - 1] + pImg0[pos1];
						}
					}
					else
					{
						if (y > 0)
						{
							pSum0[pos3] = pSum0[pos3 - w0] + pImg0[pos1];
						}
						else
						{
							pSum0[pos3] = pImg0[pos1];
						}
					}

					pos1 += nC;
				}
				pos0 += p0;
				pos2 += w0;
			}

			for (int y = 0; y < h1; y++)
			{
				int ys = arr_y[y] - dy;
				if (ys < 0)
					ys = 0;
				int ye = arr_y[y] + dy;
				if (ye >= h0)
					ye = h0 - 1;

				for (int x = 0; x < w1; x++)
				{
					int xs = arr_x[x] - dx;
					if (xs < 0)
						xs = 0;
					int xe = arr_x[x] + dx;
					if (xe >= w0)
						xe = w0 - 1;

					if (ys == ye || xs == xe)
					{
						pImg1[y*h1 + x] = pImg0[ye*p0 + xe];
					}
					else
					{
						pImg1[y*h1 + x] = (pSum0[ye*w0 + xe] - pSum0[ye*w0 + xs] - pSum0[ys*w0 + xe] + pSum0[ys*w0 + xs]) / (xe - xs + 1) / (ye - ys + 1);
					}
				}
			}

			delete[]pSum0;
		}
		else if (nC >= 3)
		{
			int nCnt = w0 * h0;
			int *pSum0 = new int[nCnt];
			int *pSum1 = new int[nCnt];
			int *pSum2 = new int[nCnt];
			int pos0 = 0;
			int pos2 = 0;
			for (int y = 0; y < h0; y++)
			{
				int pos1 = pos0;
				for (int x = 0; x < w0; x++)
				{
					int pos3 = pos2 + x;

					if (x > 0)
					{
						if (y > 0)
						{
							pSum0[pos3] = pSum0[pos3 - 1] + pSum0[pos3 - w0] - pSum0[pos3 - w0 - 1] + pImg0[pos1];
							pSum1[pos3] = pSum1[pos3 - 1] + pSum1[pos3 - w0] - pSum1[pos3 - w0 - 1] + pImg0[pos1 + 1];
							pSum2[pos3] = pSum2[pos3 - 1] + pSum2[pos3 - w0] - pSum2[pos3 - w0 - 1] + pImg0[pos1 + 2];
						}
						else
						{
							pSum0[pos3] = pSum0[pos3 - 1] + pImg0[pos1];
							pSum1[pos3] = pSum1[pos3 - 1] + pImg0[pos1 + 1];
							pSum2[pos3] = pSum2[pos3 - 1] + pImg0[pos1 + 2];
						}
					}
					else
					{
						if (y > 0)
						{
							pSum0[pos3] = pSum0[pos3 - w0] + pImg0[pos1];
							pSum1[pos3] = pSum1[pos3 - w0] + pImg0[pos1 + 1];
							pSum2[pos3] = pSum2[pos3 - w0] + pImg0[pos1 + 2];
						}
						else
						{
							pSum0[pos3] = pImg0[pos1];
							pSum1[pos3] = pImg0[pos1 + 1];
							pSum2[pos3] = pImg0[pos1 + 2];
						}
					}

					pos1 += nC;
				}
				pos0 += p0;
				pos2 += w0;
			}

			for (int y = 0; y < h1; y++)
			{
				int ys = arr_y[y] - dy;
				if (ys < 0)
					ys = 0;
				int ye = arr_y[y] + dy;
				if (ye >= h0)
					ye = h0 - 1;

				for (int x = 0; x < w1; x++)
				{
					int xs = arr_x[x] - dx;
					if (xs < 0)
						xs = 0;
					int xe = arr_x[x] + dx;
					if (xe >= w0)
						xe = w0 - 1;

					if (ys == ye || xs == xe)
					{
						pImg1[y*p1 + x * nC] = pImg0[ye*p0 + xe * nC];
						pImg1[y*p1 + x * nC + 1] = pImg0[ye*p0 + xe * nC + 1];
						pImg1[y*p1 + x * nC + 2] = pImg0[ye*p0 + xe * nC + 2];
					}
					else
					{
						int g0 = (pSum0[ye*w0 + xe] - pSum0[ye*w0 + xs] - pSum0[ys*w0 + xe] + pSum0[ys*w0 + xs]) / (xe - xs + 1) / (ye - ys + 1);
						int g1 = (pSum1[ye*w0 + xe] - pSum1[ye*w0 + xs] - pSum1[ys*w0 + xe] + pSum1[ys*w0 + xs]) / (xe - xs + 1) / (ye - ys + 1);
						int g2 = (pSum2[ye*w0 + xe] - pSum2[ye*w0 + xs] - pSum2[ys*w0 + xe] + pSum2[ys*w0 + xs]) / (xe - xs + 1) / (ye - ys + 1);

						pImg1[y*p1 + x * nC] = g0;
						pImg1[y*p1 + x * nC + 1] = g1;
						pImg1[y*p1 + x * nC + 2] = g2;
					}
				}
			}

			delete[]pSum0;
			delete[]pSum1;
			delete[]pSum2;
		}

		delete[]arr_x;
		delete[]arr_y;

		if (nullptr == pDstImg)
		{
			copyFrom(dstImg);
		}
		else
		{
			pDstImg->copyFrom(dstImg);
		}

		return true;
	}

	bool xImage::resizeBI(int nNewW, int nNewH, xImage *pDstImg)
	{
		if (nNewW <= 0 || nNewH <= 0)
		{
			return false;
		}

		if (!isValid())
			return false;


		int w0 = getWidth();
		int h0 = getHeight();
		int p0 = getPitch();

		int nC = getChannels();

		xImage dstImg;
		if (!dstImg.create(nNewW, nNewH, m_bAligned, m_pixFmt, m_byrFmt))
		{
			return false;
		}

		int w1 = dstImg.getWidth();
		int h1 = dstImg.getHeight();
		int p1 = dstImg.getPitch();

		float fw = float(w0) / w1;
		float fh = float(h0) / h1;

		float *arr_x = new float[w1];
		float *arr_y = new float[h1];
		for (int y = 0; y < h1; y++)
		{
			arr_y[y] = y * fh;
		}
		for (int x = 0; x < w1; x++)
		{
			arr_x[x] = x * fw;
		}

		unsigned char *pSrc = getBuffer();
		unsigned char *pDst = dstImg.getBuffer();

		bool bRet = true;

		if (nC == 1)
		{
			for (int y = 0; y < h1; y++)
			{
				int ySrc = (int)(arr_y[y]);
				float v = arr_y[y] - (int)(arr_y[y]);

				for (int x = 0; x < w1; x++)
				{
					int xSrc = (int)(arr_x[x]);

					float u = arr_x[x] - (int)(arr_x[x]);

					//coefficients
					float c11 = u * v;
					float c10 = v - c11;
					float c01 = u - c11;
					float c00 = 1 - u - v + c11;

					int pos = ySrc * p0 + xSrc * nC;
					unsigned char g = pSrc[pos];
					if (xSrc < w0 - 1)
					{
						if (ySrc < h0 - 1)
						{
							g = (unsigned char)(c00*pSrc[pos] + c01 * pSrc[pos + nC] + c10 * pSrc[pos + p0] + c11 * pSrc[pos + p0 + nC]);
						}
						else
						{
							g = (unsigned char)((1 - u)*pSrc[pos] + u * pSrc[pos + nC]);
						}
					}
					else
					{
						if (ySrc < h0 - 1)
						{
							g = (unsigned char)((1 - v)*pSrc[pos] + v * pSrc[pos + p0]);
						}
						else
						{
							g = pSrc[pos];
						}
					}

					pDst[y*p1 + x * nC] = g;
				}
			}
		}
		else if (nC >= 3)
		{
			for (int y = 0; y < h1; y++)
			{
				int ySrc = (int)(arr_y[y]);
				float v = arr_y[y] - (int)(arr_y[y]);

				for (int x = 0; x < w1; x++)
				{
					int xSrc = (int)(arr_x[x]);

					float u = arr_x[x] - (int)(arr_x[x]);

					//coefficients
					float c11 = u * v;
					float c10 = v - c11;
					float c01 = u - c11;
					float c00 = 1 - u - v + c11;

					int pos = ySrc * p0 + xSrc * nC;
					unsigned char g0 = pSrc[pos];
					unsigned char g1 = pSrc[pos + 1];
					unsigned char g2 = pSrc[pos + 2];

					if (xSrc < w0 - 1)
					{
						if (ySrc < h0 - 1)
						{
							g0 = (unsigned char)(c00*pSrc[pos] + c01 * pSrc[pos + nC] + c10 * pSrc[pos + p0] + c11 * pSrc[pos + p0 + nC]);
							g1 = (unsigned char)(c00*pSrc[pos + 1] + c01 * pSrc[pos + nC + 1] + c10 * pSrc[pos + p0 + 1] + c11 * pSrc[pos + p0 + nC + 1]);
							g2 = (unsigned char)(c00*pSrc[pos + 2] + c01 * pSrc[pos + nC + 2] + c10 * pSrc[pos + p0 + 2] + c11 * pSrc[pos + p0 + nC + 2]);
						}
						else
						{
							g0 = (unsigned char)((1 - u)*pSrc[pos] + u * pSrc[pos + nC]);
							g1 = (unsigned char)((1 - u)*pSrc[pos + 1] + u * pSrc[pos + nC + 1]);
							g2 = (unsigned char)((1 - u)*pSrc[pos + 2] + u * pSrc[pos + nC + 2]);
						}
					}
					else
					{
						if (ySrc < h0 - 1)
						{
							g0 = (unsigned char)((1 - v)*pSrc[pos] + v * pSrc[pos + p0]);
							g1 = (unsigned char)((1 - v)*pSrc[pos + 1] + v * pSrc[pos + p0 + 1]);
							g2 = (unsigned char)((1 - v)*pSrc[pos + 2] + v * pSrc[pos + p0 + 2]);
						}
						else
						{
							g0 = pSrc[pos];
							g1 = pSrc[pos + 1];
							g2 = pSrc[pos + 2];
						}
					}

					pDst[y*p1 + x * nC] = g0;
					pDst[y*p1 + x * nC + 1] = g1;
					pDst[y*p1 + x * nC + 2] = g2;
				}
			}
		}
		else
		{
			bRet = false;
		}

		delete[]arr_x;
		delete[]arr_y;

		if (nullptr == pDstImg)
		{
			copyFrom(dstImg);
		}
		else
		{
			pDstImg->copyFrom(dstImg);
		}

		return bRet;
	}

	bool xImage::resizeCI(int nNewW, int nNewH, xImage *pDesImg)
	{
		return false;
	}

	bool xImage::resize(int nNewW, int nNewH, EImageInterpolationMethod iim, xImage *pDstImg)
	{
		switch (iim)
		{
		case IIM_NEAREST_NEIGHBOR:
			return resizeNNI(nNewW, nNewH, pDstImg);

		case IIM_MA:
			return resizeMA(nNewW, nNewH, pDstImg);

		case IIM_BILINEAR:
			return resizeBI(nNewW, nNewH, pDstImg);

		case IIM_BICUBIC:
			return resizeCI(nNewW, nNewH, pDstImg);

		default:
			return false;
		}

		return false;
	}

	bool xImage::YCbCr2RGB(xImage &dstImg)
	{
		if (!isValid())
			return false;

		int nC = getChannels();
		if (nC < 3)
			return false;

		const float RGBRYF = 1.00000F;            // YCbCr转RGB的系数(浮点类型）
		const float RGBRCbF = 0.0000F;
		const float RGBRCrF = 1.40200F;
		const float RGBGYF = 1.00000F;
		const float RGBGCbF = -0.34414F;
		const float RGBGCrF = -0.71414F;
		const float RGBBYF = 1.00000F;
		const float RGBBCbF = 1.77200F;
		const float RGBBCrF = 0.00000F;

		const int Shift = 20;
		const int HalfShiftValue = 1 << (Shift - 1);

		const int RGBRYI = (int)(RGBRYF  * (1 << Shift) + 0.5);              // YCbCr转RGB的系数(整数类型）
		const int RGBRCbI = (int)(RGBRCbF * (1 << Shift) + 0.5);
		const int RGBRCrI = (int)(RGBRCrF * (1 << Shift) + 0.5);
		const int RGBGYI = (int)(RGBGYF  * (1 << Shift) + 0.5);
		const int RGBGCbI = (int)(RGBGCbF * (1 << Shift) + 0.5);
		const int RGBGCrI = (int)(RGBGCrF * (1 << Shift) + 0.5);
		const int RGBBYI = (int)(RGBBYF  * (1 << Shift) + 0.5);
		const int RGBBCbI = (int)(RGBBCbF * (1 << Shift) + 0.5);
		const int RGBBCrI = (int)(RGBBCrF * (1 << Shift) + 0.5);

		if (!dstImg.create(m_nWidth, m_nHeight, m_bAligned, m_pixFmt, m_byrFmt))
		{
			return false;
		}

		unsigned char *pSrc = m_pBuffer;
		unsigned char *pDst = dstImg.getBuffer();


		int Red, Green, Blue;
		int Y, Cb, Cr;
		for (unsigned y = 0; y < m_nHeight; y++)
		{
			Y = *pSrc;
			Cb = *(pSrc + 1) - 128;
			Cr = *(pSrc + 2) - 128;

			Red = Y + ((RGBRCrI * Cr + HalfShiftValue) >> Shift);
			Green = Y + ((RGBGCbI * Cb + RGBGCrI * Cr + HalfShiftValue) >> Shift);
			Blue = Y + ((RGBBCbI * Cb + HalfShiftValue) >> Shift);
			if (Red > 255)
				Red = 255;
			else if (Red < 0)
				Red = 0;
			if (Green > 255)
				Green = 255;
			else if (Green < 0)
				Green = 0;    // 编译后应该比三目运算符的效率高
			if (Blue > 255)
				Blue = 255;
			else if (Blue < 0)
				Blue = 0;
			*pDst = (unsigned char)Blue;  // 由于不是一一对应的，需要判断是否越界
			*(pDst + 1) = (unsigned char)Green;
			*(pDst + 2) = (unsigned char)Red;

			pSrc += m_nPitch;
			pDst += m_nPitch;
		}

		return true;
	}

	bool xImage::RGB2YCbCr(xImage &dstImg)
	{
		if (!isValid())
			return false;

		int nC = getChannels();
		if (nC < 3)
			return false;

		const float YCbCrYRF = 0.299F;              // RGB转YCbCr的系数(浮点类型）
		const float YCbCrYGF = 0.587F;
		const float YCbCrYBF = 0.114F;
		const float YCbCrCbRF = -0.168736F;
		const float YCbCrCbGF = -0.331264F;
		const float YCbCrCbBF = 0.500000F;
		const float YCbCrCrRF = 0.500000F;
		const float YCbCrCrGF = -0.418688F;
		const float YCbCrCrBF = -0.081312F;

		const int Shift = 20;
		const int HalfShiftValue = 1 << (Shift - 1);

		const int YCbCrYRI = (int)(YCbCrYRF  * (1 << Shift) + 0.5);         // RGB转YCbCr的系数(整数类型）
		const int YCbCrYGI = (int)(YCbCrYGF  * (1 << Shift) + 0.5);
		const int YCbCrYBI = (int)(YCbCrYBF  * (1 << Shift) + 0.5);
		const int YCbCrCbRI = (int)(YCbCrCbRF * (1 << Shift) + 0.5);
		const int YCbCrCbGI = (int)(YCbCrCbGF * (1 << Shift) + 0.5);
		const int YCbCrCbBI = (int)(YCbCrCbBF * (1 << Shift) + 0.5);
		const int YCbCrCrRI = (int)(YCbCrCrRF * (1 << Shift) + 0.5);
		const int YCbCrCrGI = (int)(YCbCrCrGF * (1 << Shift) + 0.5);
		const int YCbCrCrBI = (int)(YCbCrCrBF * (1 << Shift) + 0.5);

		if (!dstImg.create(m_nWidth, m_nHeight, m_bAligned, m_pixFmt, m_byrFmt))
		{
			return false;
		}

		unsigned char *pSrc = m_pBuffer;
		unsigned char *pDst = dstImg.getBuffer();


		int Red, Green, Blue;
		// int Y, Cb, Cr;
		for (unsigned y = 0; y < m_nHeight; y++)
		{
			Blue = *pSrc;
			Green = *(pSrc + 1);
			Red = *(pSrc + 2);
			// 无需判断是否存在溢出，因为测试过整个RGB空间的所有颜色值，无颜色存在溢出
			*pDst = (unsigned char)((YCbCrYRI  * Red + YCbCrYGI * Green + YCbCrYBI * Blue + HalfShiftValue) >> Shift);
			*(pDst + 1) = (unsigned char)(((YCbCrCbRI * Red + YCbCrCbGI * Green + YCbCrCbBI * Blue + HalfShiftValue) >> Shift) + 128);
			*(pDst + 2) = (unsigned char)(((YCbCrCrRI * Red + YCbCrCrGI * Green + YCbCrCrBI * Blue + HalfShiftValue) >> Shift) + 128);
			// *To = (byte)Y;          // 不要把直接计算的代码放在这里，会降低速度，
			//*(To + 1) = (byte)Cb;
			//*(To + 2) = (byte)Cr;
			pSrc += m_nPitch;
			pDst += m_nPitch;
		}

		return true;
	}

	bool xImage::threshold(int nT, xImage *pDstBinaryImage)
	{
		if (!isValid())
		{
			return false;
		}

		vector<ImageRect> aAOI(1, ImageRect(0, m_nWidth - 1, 0, m_nHeight - 1));

		if (nullptr == pDstBinaryImage)
		{
			return binarization(m_pBuffer, m_nWidth, m_nHeight, m_nPitch, aAOI, nT);
		}
		else
		{
			if (convert(PIXEL_FORMAT_MONO8, pDstBinaryImage))
			{
				return binarization(pDstBinaryImage->getBuffer(),
					pDstBinaryImage->getWidth(),
					pDstBinaryImage->getHeight(),
					pDstBinaryImage->getPitch(),
					aAOI,
					nT);
			}
		}

		return false;
	}

	bool xImage::getIntensity(unsigned char g[3])
	{
		if (!isValid())
		{
			return false;
		}

		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		if (nC == 1)
		{
			double dG = 0.0;
			for (int y = 0; y < nH; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (int x = 0; x < nW; x++)
				{
					dG += pBuf[x];
				}
			}

			g[0] = (unsigned char)(dG / nW / nH);
		}
		else if (nC >= 3)
		{
			double dG[3] = { 0.0 };
			for (int y = 0; y < nH; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (int x = 0; x < nW; x++)
				{
					dG[0] += pBuf[nC*x];
					dG[1] += pBuf[nC*x + 1];
					dG[2] += pBuf[nC*x + 2];
				}
			}

			g[0] = (unsigned char)(dG[0] / nW / nH);
			g[1] = (unsigned char)(dG[1] / nW / nH);
			g[2] = (unsigned char)(dG[2] / nW / nH);
		}
		else
		{
			return false;
		}

		return true;
	}




	bool xImage::getIntensity(unsigned char g[3], vector<ImageRect> &aAOI)
	{
		if (!isValid() || aAOI.empty())
		{
			return false;
		}

		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		if (nC == 1)
		{
			double dG = 0.0;

			int nCnt = 0;
			for (int n = 0; n != aAOI.size(); ++n)
			{
				for (int y = aAOI[n].ys; y <= aAOI[n].ye; y++)
				{
					unsigned char *pBuf = getScanLine(y);

					for (int x = aAOI[n].xs; x <= aAOI[n].xe; x++)
					{
						dG += pBuf[x];
					}
				}

				nCnt += (aAOI[n].xe - aAOI[n].xs + 1)*(aAOI[n].ye - aAOI[n].ys + 1);
			}

			g[0] = (unsigned char)(dG / nCnt);
		}
		else if (nC >= 3)
		{
			double dG[3] = { 0.0 };
			int nCnt = 0;
			for (int n = 0; n != aAOI.size(); ++n)
			{
				for (int y = aAOI[n].ys; y <= aAOI[n].ye; y++)
				{
					unsigned char *pBuf = getScanLine(y);

					for (int x = aAOI[n].xs; x <= aAOI[n].xe; x++)
					{
						dG[0] += pBuf[nC * x];
						dG[1] += pBuf[nC * x + 1];
						dG[2] += pBuf[nC * x + 2];
					}
				}

				nCnt += (aAOI[n].xe - aAOI[n].xs + 1)*(aAOI[n].ye - aAOI[n].ys + 1);
			}

			g[0] = (unsigned char)(dG[0] / nCnt);
			g[1] = (unsigned char)(dG[1] / nCnt);
			g[2] = (unsigned char)(dG[2] / nCnt);
		}
		else
		{
			return false;
		}

		return true;
	}


	bool xImage::getMask(Mask2D &mask, unsigned char ucThr)
	{
		if (!isValid())
		{
			return false;
		}

		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		mask.create(nW, nH);
		memset(mask.pData, 0, nW*nH * sizeof(unsigned char));

		if (nC >= 1)
		{
			xImage gImg;
			if (!getGChannel(gImg))
			{
				return false;
			}

			for (int y = 0; y < nH; y++)
			{
				unsigned char *pBuf = gImg.getScanLine(y);

				for (int x = 0; x < nW; x++)
				{
					if (pBuf[x] >= ucThr)
					{
						mask.pData[y*nW + x] = 255;
					}
				}
			}
		}
		else if (nC == 1)
		{
			for (int y = 0; y < nH; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (int x = 0; x < nW; x++)
				{
					if (pBuf[x] >= ucThr)
					{
						mask.pData[y*nW + x] = 255;
					}
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	bool xImage::setColor(ImageRect r, unsigned char red, unsigned char green, unsigned char blue)
	{
		if (!isValid())
		{
			return false;
		}

		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();
		int nC = getChannels();
		unsigned char *pImg = getBuffer();

		if (nC < 3)
		{
			return false;
		}

		int xs = r.xs < 0 ? 0 : (r.xs > (nW - 1) ? (nW - 1) : r.xs);
		int xe = r.xe < 0 ? 0 : (r.xe > (nW - 1) ? (nW - 1) : r.xe);
		int ys = r.ys < 0 ? 0 : (r.ys > (nH - 1) ? (nH - 1) : r.ys);
		int ye = r.ye < 0 ? 0 : (r.ye > (nH - 1) ? (nH - 1) : r.ye);

		if (isBGR())
		{
			for (int y = ys; y <= ye; y++)
				for (int x = xs; x <= xe; x++)
				{
					pImg[y*nP + x * nC] = blue;
					pImg[y*nP + x * nC + 1] = green;
					pImg[y*nP + x * nC + 2] = red;
				}
		}
		else
		{
			for (int y = ys; y <= ye; y++)
				for (int x = xs; x <= xe; x++)
				{
					pImg[y*nP + x * nC] = red;
					pImg[y*nP + x * nC + 1] = green;
					pImg[y*nP + x * nC + 2] = blue;
				}
		}

		return true;
	}

	bool xImage::setColor(Mask2D &mask, unsigned char color[3])
	{
		if (!isValid() || mask.empty() || mask.w != getWidth() || mask.h != getHeight())
		{
			return false;
		}

		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();
		int nC = getChannels();
		unsigned char *pImg = getBuffer();

		if (nC < 3)
		{
			return false;
		}

		for (int y = 0; y < nH; y++)
			for (int x = 0; x < nW; x++)
			{
				if (mask.pData[y*nW + x] == 255)
				{
					pImg[y*nP + x * nC] = color[0];
					pImg[y*nP + x * nC + 1] = color[1];
					pImg[y*nP + x * nC + 2] = color[2];
				}
			}

		return true;
	}

	bool xImage::getIntensity(unsigned char &g, Mask2D &mask)
	{
		if (!isValid() || mask.empty() || mask.w != getWidth() || mask.h != getHeight())
		{
			return false;
		}

		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		if (nC == 1)
		{
			double dG = 0.0;
			size_t nCnt = 0;
			for (int y = 0; y < nH; y++)
			{
				unsigned char *pBuf = getScanLine(y);

				for (int x = 0; x < nW; x++)
				{
					if (mask.pData[y*nW + x] == 255)
					{
						dG += pBuf[x];

						nCnt++;
					}
				}
			}

			g = (unsigned char)(dG / nCnt);
		}
		else
		{
			xImage gImg;
			if (!getGChannel(gImg))
			{
				return false;
			}

			double dG = 0.0;
			size_t nCnt = 0;
			for (int y = 0; y < nH; y++)
			{
				unsigned char *pBuf = gImg.getScanLine(y);

				for (int x = 0; x < nW; x++)
				{
					if (mask.pData[y*nW + x] == 255)
					{
						dG += pBuf[x];

						nCnt++;
					}
				}
			}

			g = (unsigned char)(dG / nCnt);
		}

		return true;
	}

	bool xImage::getIntensityCV(double &dCV, double &dStd, double &dMean, 
		int nBlkWidth, int nBlkHeight, xImage *pIntensityImage)
	{
		if (!isValid() || 0 >= nBlkWidth || 0 >= nBlkHeight)
		{
			return false;
		}

		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		int nRow = nH / nBlkHeight;
		if (nRow == 0 || nH % nBlkHeight != 0)
		{
			nRow++;
		}

		int nCol = nW / nBlkWidth;
		if (nCol == 0 || nW % nBlkWidth != 0)
		{
			nCol++;
		}

		unsigned char *pOutBuf = nullptr;
		if (nullptr != pIntensityImage)
		{
			if (!pIntensityImage->create(nCol, nRow, false, PIXEL_FORMAT_MONO8))
			{
				return false;
			}
			pOutBuf = pIntensityImage->getBuffer();
		}

		Histogram h(256);
		int *pHist = h.ptr();

		if (nC == 1)
		{
			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkHeight;
				int ye = (ys + nBlkHeight) > nH ? nH : (ys + nBlkHeight);
				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkWidth;
					int xe = (xs + nBlkWidth) > nW ? nW : (xs + nBlkWidth);
					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += m_pBuffer[y*m_nPitch + x];
						}

					nMean /= (xe - xs)*(ye - ys);

					pHist[nMean]++;

					if (nullptr != pOutBuf)
					{
						pOutBuf[r*nCol + c] = nMean;
					}
				}
			}
		}
		else if (nC >= 3)
		{
			xImage grayImg;
			if (!convert(PIXEL_FORMAT_MONO8, &grayImg))
			{
				return false;
			}

			unsigned char *pImg = grayImg.getBuffer();
			unsigned nP = grayImg.getPitch();

			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkHeight;
				int ye = (ys + nBlkHeight) > nH ? nH : (ys + nBlkHeight);
				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkWidth;
					int xe = (xs + nBlkWidth) > nW ? nW : (xs + nBlkWidth);
					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += pImg[y*nP + x];
						}

					nMean /= (xe - xs)*(ye - ys);

					pHist[nMean]++;

					if (nullptr != pOutBuf)
					{
						pOutBuf[r*nCol + c] = nMean;
					}
				}
			}
		}
		else
		{
			return false;
		}

		HistogramResult hr;
		h.getResult(hr);
		dCV = hr.cv;
		dStd = hr.std;
		dMean = hr.mean;

		return true;
	}

	bool xImage::getIntensityCV(double &dCV, double &dStd, double &dMean, 
		int nRow, int nCol, EColorChannel chn, xImage *pIntensityImage)
	{
		if (!isValid() || 0 >= nRow || 0 >= nCol)
		{
			return false;
		}

		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		int nBlkH = nH / nRow;

		int nBlkW = nW / nCol;

		unsigned char *pOutBuf = nullptr;
		if (nullptr != pIntensityImage)
		{
			if (!pIntensityImage->create(nCol, nRow, false, PIXEL_FORMAT_MONO8))
			{
				return false;
			}
			pOutBuf = pIntensityImage->getBuffer();
		}

		Histogram h(256);
		int *pHist = h.ptr();

		if (nC == 1)
		{
			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkH;
				int ye = (r < nRow - 1) ? (ys + nBlkH) : nH;

				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkW;
					int xe = (c < nCol - 1) ? (xs + nBlkW) : nW;

					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += m_pBuffer[y*m_nPitch + x];
						}

					if (xe > xs && ye > ys)
					{
						nMean /= (xe - xs)*(ye - ys);
					}

					pHist[nMean]++;

					if (nullptr != pOutBuf)
					{
						pOutBuf[r*nCol + c] = nMean;
					}
				}
			}
		}
		else if (nC >= 3)
		{
			xImage grayImg;
			if (chn == COLOR_CHANNEL_R)
			{
				if (!getRChannel(grayImg))
				{
					return false;
				}
			}
			else if (chn == COLOR_CHANNEL_G)
			{
				if (!getGChannel(grayImg))
				{
					return false;
				}
			}
			else if (chn == COLOR_CHANNEL_B)
			{
				if (!getBChannel(grayImg))
				{
					return false;
				}
			}
			else 
			{ 
				if (!convert(PIXEL_FORMAT_MONO8, &grayImg))
				{
					return false;
				}
			}

			unsigned char *pImg = grayImg.getBuffer();
			unsigned nP = grayImg.getPitch();

			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkH;
				int ye = (r < nRow - 1) ? (ys + nBlkH) : nH;
				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkW;
					int xe = (c < nCol - 1) ? (xs + nBlkW) : nW;

					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += pImg[y*nP + x];
						}

					if (xe > xs && ye > ys)
					{
						nMean /= (xe - xs)*(ye - ys);
					}

					pHist[nMean]++;

					if (nullptr != pOutBuf)
					{
						pOutBuf[r*nCol + c] = nMean;
					}
				}
			}
		}
		else
		{
			return false;
		}

		HistogramResult hr;
		h.getResult(hr);
		dCV = hr.cv;
		dStd = hr.std;
		dMean = hr.mean;

		return true;
	}	
	
	bool xImage::getIntensityHeatMap(xImage &heatImage, double &dCV, double &dStd, double &dMean,
		int nBlkWidth, int nBlkHeight, bool bAbsMode)
	{
		if (!isValid() || 0 >= nBlkWidth || 0 >= nBlkHeight)
		{
			return false;
		}

		int nPix = nBlkHeight * nBlkWidth;
		
		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();

		int nRow = nH / nBlkHeight;
		int nCol = nW / nBlkWidth;

		if (nRow == 0 || nH % nBlkHeight != 0)
		{
			nRow++;
		}
		if (nCol == 0 || nW % nBlkWidth != 0)
		{
			nCol++;
		}


		Histogram h(256);
		int *pHist = h.ptr();

		unsigned char *pIntensity = new unsigned char[nRow*nCol];

		if (nC == 1)
		{
			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkHeight;
				int ye = (ys + nBlkHeight) > nH ? nH : (ys + nBlkHeight);
				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkWidth;
					int xe = (xs + nBlkWidth) > nW ? nW : (xs + nBlkWidth);
					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += m_pBuffer[y*m_nPitch + x];
						}

					nMean /= (xe - xs)*(ye - ys);

					pHist[nMean]++;

					pIntensity[r*nCol + c] = nMean;
				}
			}
		}
		else if (nC >= 3)
		{
			xImage grayImg;
			if (!convert(PIXEL_FORMAT_MONO8, &grayImg))
			{
				delete[]pIntensity;

				return false;
			}

			unsigned char *pImg = grayImg.getBuffer();
			unsigned nP = grayImg.getPitch();

			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkHeight;
				int ye = (ys + nBlkHeight) > nH ? nH : (ys + nBlkHeight);
				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkWidth;
					int xe = (xs + nBlkWidth) > nW ? nW : (xs + nBlkWidth);
					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += pImg[y*nP + x];
						}

					nMean /= (xe - xs)*(ye - ys);

					pHist[nMean]++;
					
					pIntensity[r*nCol + c] = nMean;
				}
			}
		}
		else
		{
			delete[]pIntensity;

			return false;
		}

		int iMinVal = 255;
		for (int k = 0; k < 255; k++)
		{
			if (pHist[k] > 0)
			{
				iMinVal = k;
				break;
			}
		}

		int iMaxVal = 0;
		for (int k = 255; k >= 0; k--)
		{
			if (pHist[k] > 0)
			{
				iMaxVal = k;
				break;
			}
		}
		
		float fRange = 1.0;
		if (iMaxVal > iMinVal)
		{
			fRange = iMaxVal - iMinVal;
		}
			   
		if (!heatImage.create(nW, nH))
		{
			delete[]pIntensity;

			return false;
		}

		for (int r = 0; r < nRow; r++)
		{
			int ys = r * nBlkHeight;
			int ye = (ys + nBlkHeight) > nH ? nH : (ys + nBlkHeight);

			for (int c = 0; c < nCol; c++)
			{
				int xs = c * nBlkWidth;
				int xe = (xs + nBlkWidth) > nW ? nW : (xs + nBlkWidth);

				float v;
				if (bAbsMode)
				{
					v = (float)(pIntensity[r*nCol + c]) / 255.0;
				}
				else
				{
					v = (float)(pIntensity[r*nCol + c]-iMinVal) / fRange;
				}


				float red, green, blue;
				ColorGradient::getHeatMapColor(v, &red, &green, &blue);

				ImageRect rect(xs, xe-1, ys, ye-1);
				heatImage.setColor(rect, (unsigned char)(red * 255), (unsigned char)(green * 255), (unsigned char)(blue * 255));
			}
		}

		HistogramResult hr;
		h.getResult(hr);
		dCV = hr.cv;
		dStd = hr.std;
		dMean = hr.mean;

		delete[]pIntensity;

		return true;
	}

	bool xImage::getIntensityHeatMap(xImage &heatImage, double &dCV, double &dStd, double &dMean,
									int nRow, int nCol,
									EColorChannel chn,
									bool bAbsMode)
	{
		if (!isValid() || 0 >= nRow || 0 >= nCol)
		{
			return false;
		}
		
		int nC = getChannels();
		int nW = getWidth();
		int nH = getHeight();
		int nP = getPitch();


		int nBlkWidth = nW / nCol;

		int  nBlkHeight = nH / nRow;


		Histogram h(256);
		int *pHist = h.ptr();

		unsigned char *pIntensity = new unsigned char[nRow*nCol];

		if (nC == 1)
		{
			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkHeight;
				int ye = (r < nRow - 1) ? (ys + nBlkHeight) : nH;

				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkWidth;
					int xe = (c < nCol - 1) ? (xs + nBlkWidth) : nW;

					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += m_pBuffer[y*m_nPitch + x];
						}

					if (xe > xs && ye > ys)
					{
						nMean /= (xe - xs)*(ye - ys);
					}

					pHist[nMean]++;

					pIntensity[r*nCol + c] = nMean;
				}
			}
		}
		else if (nC >= 3)
		{
			xImage grayImg;
			if (chn == COLOR_CHANNEL_R)
			{
				if (!getRChannel(grayImg))
				{
					return false;
				}
			}
			else if (chn == COLOR_CHANNEL_G)
			{
				if (!getGChannel(grayImg))
				{
					return false;
				}
			}
			else if (chn == COLOR_CHANNEL_B)
			{
				if (!getBChannel(grayImg))
				{
					return false;
				}
			}
			else
			{
				if (!convert(PIXEL_FORMAT_MONO8, &grayImg))
				{
					return false;
				}
			}

			unsigned char *pImg = grayImg.getBuffer();
			unsigned nP = grayImg.getPitch();

			for (int r = 0; r < nRow; r++)
			{
				int ys = r * nBlkHeight;
				int ye = (r < nRow - 1) ? (ys + nBlkHeight) : nH;

				for (int c = 0; c < nCol; c++)
				{
					int xs = c * nBlkWidth;
					int xe = (c < nCol - 1) ? (xs + nBlkWidth) : nW;

					int nMean = 0;
					for (int y = ys; y < ye; y++)
						for (int x = xs; x < xe; x++)
						{
							nMean += pImg[y*nP + x];
						}

					if (xe > xs && ye > ys)
					{
						nMean /= (xe - xs)*(ye - ys);
					}

					pHist[nMean]++;
					
					pIntensity[r*nCol + c] = nMean;
				}
			}
		}
		else
		{
			delete[]pIntensity;

			return false;
		}

		int iMinVal = 255;
		for (int k = 0; k < 255; k++)
		{
			if (pHist[k] > 0)
			{
				iMinVal = k;
				break;
			}
		}

		int iMaxVal = 0;
		for (int k = 255; k >= 0; k--)
		{
			if (pHist[k] > 0)
			{
				iMaxVal = k;
				break;
			}
		}
		
		float fRange = 1.0;
		if (iMaxVal > iMinVal)
		{
			fRange = iMaxVal - iMinVal;
		}
			   
		if (!heatImage.create(nW, nH))
		{
			delete[]pIntensity;

			return false;
		}

		for (int r = 0; r < nRow; r++)
		{
			int ys = r * nBlkHeight;
			int ye = (ys + nBlkHeight) > nH ? nH : (ys + nBlkHeight);

			for (int c = 0; c < nCol; c++)
			{
				int xs = c * nBlkWidth;
				int xe = (xs + nBlkWidth) > nW ? nW : (xs + nBlkWidth);

				float v;
				if (bAbsMode)
				{
					v = (float)(pIntensity[r*nCol + c]) / 255.0;
				}
				else
				{
					v = (float)(pIntensity[r*nCol + c]-iMinVal) / fRange;
				}


				float red, green, blue;
				ColorGradient::getHeatMapColor(v, &red, &green, &blue);

				ImageRect rect(xs, xe-1, ys, ye-1);
				heatImage.setColor(rect, (unsigned char)(red * 255), (unsigned char)(green * 255), (unsigned char)(blue * 255));
			}
		}

		HistogramResult hr;
		h.getResult(hr);
		dCV = hr.cv;
		dStd = hr.std;
		dMean = hr.mean;

		delete[]pIntensity;

		return true;
	}

	bool xImage::match(Offset2I &offset, const xImage &imgRef, const ImageRect *pRectRef, const ImageRect *pRect)
	{
		return false;
	}

	bool xImage::merge(const xImage &imgRef, const Offset2I &offset, xImage *pDstImg)
	{
		if (!isValid() || !imgRef.isValid())
		{
			return false;
		}

		int nObjW = m_nWidth;
		int nObjH = m_nHeight;

		int nRefW = imgRef.getWidth();
		int nRefH = imgRef.getHeight();

		ImageRect refRect(0, nRefW - 1, 0, nRefH - 1);
		ImageRect rectObj(offset.dx, offset.dx + nObjW, offset.dy, offset.dy + nObjH);
		ImageRect rectOvlp = refRect.overlap(rectObj);
		if (!rectOvlp.semi_positive())
		{
			//no overlapping area
			return false;
		}

		return false;
	}


#if XIMAGE_SUPPORT_DISTORTION_CORRECTION
	bool xImage::undistort(division_model dm, unsigned nCropLength, double dUndistRadius, xImage *pDstImg)
	{
		unsigned char *pImgU = nullptr;
		unsigned nWu = 0, nPu = 0, nHu = 0;
		bool bOK = undistortion(pImgU, nWu, nPu, nHu, dm, m_pBuffer, m_nWidth, m_nPitch, m_nHeight, nCropLength, dUndistRadius);

		if (bOK)
		{
			if (nullptr == pDstImg)
			{
				bOK = create(pImgU, nWu, nHu);
			}
			else
			{
				bOK = pDstImg->create(pImgU, nWu, nHu, m_bAligned, m_pixFmt, m_byrFmt);
			}
		}

		delete[]pImgU;

		return bOK;
	}
#endif // XMAGE_SUPPORT_DISTORTION_CORRECTION



	bool xImage::executeProcChain(const ImgProcChainSetting &ipChainSetting, xImage *pDstImg)
	{
		xImage img;

		copyTo(img);

		if (ipChainSetting.byrEnhEnabled)
		{
		}
		if (ipChainSetting.dbyrEnabled)
		{
			debayer(ipChainSetting.dbyrPara.eDstPixFmt, ipChainSetting.dbyrPara.eDByrMethod, &img);
		}
		if (ipChainSetting.bbEnabled)
		{
			BackgroundBalance bkgBalance;
			if (!bkgBalance.isReady())
			{
				if ((strcmp(ipChainSetting.bbFileName.c_str(), ("")) != 0))
				{
					xImage imgBkg(ipChainSetting.bbFileName.c_str());

					if (imgBkg.isValid())
					{
						if (bkgBalance.setBkgImage(imgBkg))
						{
							if (bkgBalance.calcBalanceBK())
							{
								bkgBalance.execute(img);
							}
						}
					}
				}
			}
		}
		if (ipChainSetting.wbEnabled)
		{
			float rgain, ggain, bgain;
			if (ipChainSetting.calcWBEnabled)
			{
				WhiteBalanceParam wbPara = ipChainSetting.wbPara;
				ImageRect wbROI = ipChainSetting.wbROI;
				if (ipChainSetting.useWBROIEnabled)
					img.calcWhiteBalance(rgain, ggain, bgain, &wbPara, &wbROI);
				else
					img.calcWhiteBalance(rgain, ggain, bgain, &wbPara);

				img.whiteBalance(rgain, ggain, bgain);
			}
			else
			{
				rgain = ipChainSetting.ptGain.x;
				ggain = ipChainSetting.ptGain.y;
				bgain = ipChainSetting.ptGain.z;
				img.adjustGain(rgain, ggain, bgain);
			}
		}
		if (ipChainSetting.brightEnhEnabled)
		{
			img.adjustBrightness(ipChainSetting.brightEnhValue);
		}
		if (ipChainSetting.contraEnhEnabled)
		{
			img.adjustContrast(ipChainSetting.contraEnhValue);
		}
		if (ipChainSetting.gammaEnhEnabled)
		{
			img.adjustGamma(ipChainSetting.gammaEnhValue);
		}
		if (ipChainSetting.histEnhEnabled)
		{
			img.equalizeHistogram();
		}
		if (ipChainSetting.rgbEnhEnabled)
		{
		}
		if (ipChainSetting.shpnessEnhEnabled)
		{
			double kernel[] = { 0,-1,0,-1,5,-1,0,-1,0 };
			img.filter2D(kernel, 1, pDstImg);
			pDstImg->copyTo(img);
		}
		if (ipChainSetting.colorEnhEnabled)
		{
			ColorCorrection cc;
			cc.calcColorMatrix(5);
			cc.apply(img);
		}
		img.copyTo(*pDstImg);

		return true;
	}

	bool xImage::toBase64(char *base64, int &size)
	{
		//if (isValid())
		//{
		//	size = base64_encode(base64, m_pBuffer, m_nImgSize, 0);
		//	return true;
		//}

		return false;
	}

	/////////////////////////////////////////////////////////////////////////////////
	//End of implementation of xImage class
	/////////////////////////////////////////////////////////////////////////////////





	/////////////////////////////////////////////////////////////////////////////////
	//Begin of implementation of BackgroundBalance class
	/////////////////////////////////////////////////////////////////////////////////
	//background balance
	BackgroundBalance::BackgroundBalance()
		:m_bReady(false)
		, m_bROISet(false)
	{
	}

	BackgroundBalance::BackgroundBalance(const xImage &img)
		: m_bReady(false)
		, m_bROISet(false)
	{
		m_bkgImg.copyFrom(img);
	}

	BackgroundBalance::~BackgroundBalance()
	{
	}

	void BackgroundBalance::setROI(ImageRect imgROI)
	{
		if (!m_imgROI.equalTo(imgROI))
		{
			m_imgROI = imgROI;
			m_bReady = false;
		}

		m_bROISet = true;

		return;
	}

	inline bool BackgroundBalance::isROISet()
	{
		return m_bROISet;
	}

	bool BackgroundBalance::setBkgImage(const xImage &bkgImg)
	{
		//identity test
		if (m_bkgImg.getBuffer() == bkgImg.getBuffer())
		{
			return true;
		}

		if (m_bkgImg.copyFrom(bkgImg))
		{
			m_bReady = false;
			m_bROISet = false;

			return true;
		}

		return false;
	}

	bool BackgroundBalance::calcBalanceBK()
	{
		if (!m_bkgImg.isValid())
		{
			return false;
		}

		int xs, xe, ys, ye;
		if (!m_bROISet)
		{
			xs = 0;
			xe = m_bkgImg.getWidth() - 1;
			ys = 0;
			ye = m_bkgImg.getHeight() - 1;
		}
		else
		{
			xs = m_imgROI.xs;
			xe = m_imgROI.xe;
			ys = m_imgROI.ys;
			ye = m_imgROI.ye;

			if (0 > xs || xs > xe || xe >= m_bkgImg.getWidth() ||
				0 > ys || ys > ye || ye >= m_bkgImg.getHeight())
			{
				return false;
			}
		}

		int z = 0;
		int t = 0;
		int Rav = 0;
		int Gav = 0;
		int Bav = 0;

		unsigned char *data = m_bkgImg.getBuffer();
		int pitch = m_bkgImg.getPitch();
		int nc = m_bkgImg.getBPP() / 8;

		if (nc == 1)//monochromatic image
		{
			for (int y = ys; y <= ye; y++)
			{
				for (int x = xs; x <= xe; x++)
				{
					Rav = Rav + data[y * pitch + x];
					t++;
				}
			}

			if (t == 0)
				t = 1;
			Rav /= t;

			if (m_lut.empty())
			{
				m_lut.reset(65536, 1);
			}

			// fill in lut
			int itemp, i, j, i1, j1;
			if (Rav == 0)
			{
				for (i = 0; i < 256; i++)
				{
					for (j = 0; j < 256; j++)
					{
						m_lut.m_rTable[i * 256 + j] = 0;
					}
				}
			}
			else
			{
				for (i = 0; i < 256; i++)
				{
					for (j = 0; j < 256; j++)
					{
						if (i == 0)
							i1 = 1;
						else
							i1 = i;

						if (j == 0)
							j1 = 1;
						else
							j1 = j;

						itemp = i1 * Rav / j1;
						if (itemp > 255)
							itemp = 255;
						m_lut.m_rTable[i * 256 + j] = (unsigned char)itemp;
					}
				}
			}

			m_bReady = true;
		}
		else if (nc >= 3)//RGB image
		{
			//calculate the average value for each channel
			if (m_bkgImg.isRGB())
			{
				for (int y = ys; y <= ye; y++)
				{
					for (int x = xs; x <= xe; x++)
					{
						z = y * pitch + x * nc;
						Rav = Rav + data[z];
						Gav = Gav + data[z + 1];
						Bav = Bav + data[z + 2];
						t++;
					}
				}
			}
			else
			{
				for (int y = ys; y <= ye; y++)
				{
					for (int x = xs; x <= xe; x++)
					{
						z = y * pitch + x * nc;
						Rav = Rav + data[z + 2];
						Gav = Gav + data[z + 1];
						Bav = Bav + data[z];
						t++;
					}
				}
			}

			if (t == 0)
				t = 1;
			Rav /= t;
			Gav /= t;
			Bav /= t;

			if (m_lut.empty())
			{
				m_lut.reset(65536, 3);
			}

			// fill in lut
			int itemp, i, j, i1, j1;
			int p = 0;
			for (i = 0; i < 256; i++)
			{
				for (j = 0; j < 256; j++)
				{
					if (i == 0)
						i1 = 1;
					else
						i1 = i;

					if (j == 0)
						j1 = 1;
					else
						j1 = j;

					itemp = i1 * Rav / j1;
					if (itemp > 255)
						itemp = 255;
					m_lut.m_rTable[p] = (unsigned char)itemp;

					itemp = i1 * Gav / j1;
					if (itemp > 255)
						itemp = 255;
					m_lut.m_gTable[p] = (unsigned char)itemp;

					itemp = i1 * Bav / j1;
					if (itemp > 255)
						itemp = 255;
					m_lut.m_bTable[p] = (unsigned char)itemp;

					p++;
				}
			}

			m_bReady = true;
		}
		else
		{
			m_bReady = false;

			return false;
		}

		return true;
	}

	inline bool BackgroundBalance::isReady()
	{
		return m_bReady;
	}
	
	bool BackgroundBalance::execute(xImage &fgImg)
	{
		if (!isReady())
		{
			if (!calcBalanceBK())
			{
				return false;
			}
		}

		unsigned char* lp = fgImg.getBuffer();	 //source image
		unsigned char* lpbak = m_bkgImg.getBuffer(); //background image 
		if (lpbak == 0 || lp == 0 ||
			m_bkgImg.getWidth() != fgImg.getWidth() ||
			m_bkgImg.getHeight() != fgImg.getHeight() ||
			m_bkgImg.getBPP() != fgImg.getBPP())
		{
			return false;
		}

		int xs, xe, ys, ye;
		if (!m_bROISet)
		{
			xs = 0;
			xe = m_bkgImg.getWidth() - 1;
			ys = 0;
			ye = m_bkgImg.getHeight() - 1;
		}
		else
		{
			xs = m_imgROI.xs;
			xe = m_imgROI.xe;
			ys = m_imgROI.ys;
			ye = m_imgROI.ye;
		}

		int nc = m_bkgImg.getBPP() / 8;

		int pitch = fgImg.getPitch();

		int i3 = ys * pitch + xs * nc;

		if (nc == 1)
		{
			for (int i = ys; i <= ye; i++)
			{
				int idx = i3;
				for (int j = xs; j <= xe; j++)
				{
					lp[idx] = m_lut.m_rTable[lp[idx] * 256 + lpbak[idx]];
					++idx;
				}
				i3 += pitch;
			}
		}
		else if (nc >= 3)
		{
			if (fgImg.isRGB())
			{
				for (int i = ys; i <= ye; i++)
				{
					int idx = i3;
					for (int j = xs; j <= xe; j++)
					{
						lp[idx] = m_lut.m_rTable[lp[idx] * 256 + lpbak[idx]];
						++idx;
						lp[idx] = m_lut.m_gTable[lp[idx] * 256 + lpbak[idx]];
						++idx;
						lp[idx] = m_lut.m_bTable[lp[idx] * 256 + lpbak[idx]];
						++idx;
					}
					i3 += pitch;
				}
			}
			else
			{
				for (int i = ys; i <= ye; i++)
				{
					int idx = i3;
					for (int j = xs; j <= xe; j++)
					{
						lp[idx] = m_lut.m_bTable[lp[idx] * 256 + lpbak[idx]];
						++idx;
						lp[idx] = m_lut.m_gTable[lp[idx] * 256 + lpbak[idx]];
						++idx;
						lp[idx] = m_lut.m_rTable[lp[idx] * 256 + lpbak[idx]];
						++idx;
					}
					i3 += pitch;
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}
	/////////////////////////////////////////////////////////////////////////////////
	//End of implementation of BackgroundBalance class
	/////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////
	//Begin of ColorCorrection class
	/////////////////////////////////////////////////////////////////////////////////
	//Color Correction
	ColorCorrection::ColorCorrection()
		: m_cc(0)
		, m_bfactor(true)
		, m_ct_r(100)
		, m_ct_g(100)
		, m_ct_b(100)
	{
		memset(m_matrix, 0, 9 * sizeof(int));
		memset(m_lut, 0, 9 * 256 * sizeof(int));
	}

	ColorCorrection::~ColorCorrection()
	{
	}

	void ColorCorrection::calcColorMatrix(int iCC)
	{
		/////////// rewrite color correction algorithm to increase fps. JC 2008-01-30
		if (iCC == 0)
		{
			m_cc = 0;
			return;
		}

		if (iCC != m_cc)
		{
			m_cc = iCC;
			float K = (float)iCC;

			if (K < -10.0f) K = -10;
			if (K > 10.0f) K = 10;

			int i, j;

			// Calculate matrix
			if (K < 0) K = (K + 10) / 10;
			if (K < 1) // reduce color
			{
				m_matrix[1] = int(1024 * (0.587*(1 - K)));
				m_matrix[2] = int(1024 * (0.114*(1 - K)));
				m_matrix[3] = int(1024 * (0.299*(1 - K)));
				m_matrix[5] = int(1024 * (0.114*(1 - K)));
				m_matrix[6] = int(1024 * (0.299*(1 - K)));
				m_matrix[7] = int(1024 * (0.587*(1 - K)));
				m_matrix[0] = int(1024 * (0.299 + 0.701*K));
				m_matrix[4] = int(1024 * (0.587 + 0.413*K));
				m_matrix[8] = int(1024 * (0.114 + 0.866*K));
			}
			else // enhance color
			{
				if (!m_bfactor)
				{
					m_matrix[1] = int(1024 * ((-K) / 20));
					m_matrix[2] = int(1024 * ((-K) / 20));
					m_matrix[3] = int(1024 * ((-K) / 20));
					m_matrix[5] = int(1024 * ((-K) / 20));
					m_matrix[6] = int(1024 * ((-K) / 20));
					m_matrix[7] = int(1024 * ((-K) / 20));
					m_matrix[0] = int(1024 - m_matrix[1] * 2);
					m_matrix[4] = int(1024 - m_matrix[1] * 2);
					m_matrix[8] = int(1024 - m_matrix[1] * 2);
				}
				else
				{
					m_matrix[1] = int((1024 * ((-K) / 10)*m_ct_b / 100.0)); // simulate mciron matrix
					m_matrix[2] = int((1024 * ((-K) / 50)*m_ct_b / 100.0));
					m_matrix[3] = int((1024 * ((-K) / 50)*m_ct_g / 100.0));
					m_matrix[5] = int((1024 * ((-K) / 20)*m_ct_g / 100.0));
					m_matrix[6] = int((1024 * ((-K) / 50)*m_ct_r / 100.0));
					m_matrix[7] = int((1024 * ((-K) / 50)*m_ct_r / 100.0));
					m_matrix[0] = int((1024 - m_matrix[1] - m_matrix[2]));
					m_matrix[4] = int((1024 - m_matrix[3] - m_matrix[5]));
					m_matrix[8] = int((1024 - m_matrix[6] - m_matrix[7]));
				}
			}

			// Calculate hash table
			for (j = 0; j < 9; j++)
			{
				for (i = 0; i < 256; i++)
				{
					m_lut[j * 256 + i] = m_matrix[j] * i;
				}
			}
		}

		return;
	}

	bool ColorCorrection::apply(xImage &img)
	{
		if (m_cc == 0)
		{
			return true;
		}

		if (!img.isValid() || img.getChannels() < 3)
		{
			return false;
		}

		unsigned char *pimg = img.getBuffer();
		int nh = img.getHeight();
		int nw = img.getWidth();
		int np = img.getPitch();
		int nc = img.getChannels();

		int r, g, b;
		int r1, g1, b1;
		int t0, t1, t2, t3, t4, t5, t6, t7, t8;
		t0 = 0; t1 = 256; t2 = 512; t3 = 768; t4 = 1024; t5 = 1280; t6 = 1536; t7 = 1792; t8 = 2048;

		int COLOR_R, COLOR_G, COLOR_B;
		if (img.isBGR())
		{
			COLOR_R = 2;
			COLOR_G = 1;
			COLOR_B = 0;
		}
		else if (img.isRGB())
		{
			COLOR_R = 0;
			COLOR_G = 1;
			COLOR_B = 2;
		}

		for (int y = 0; y < nh; ++y)
		{
			unsigned char* lpTmp = pimg + y * np;

			for (int x = 0; x < nw; ++x)
			{
				r1 = lpTmp[COLOR_R];
				g1 = lpTmp[COLOR_G];
				b1 = lpTmp[COLOR_B];
				r = (m_lut[t0 + r1] + m_lut[t1 + g1] + m_lut[t2 + b1]);
				g = (m_lut[t3 + r1] + m_lut[t4 + g1] + m_lut[t5 + b1]);
				b = (m_lut[t6 + r1] + m_lut[t7 + g1] + m_lut[t8 + b1]);
				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;
				r = r >> 10;
				g = g >> 10;
				b = b >> 10;
				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

				lpTmp[COLOR_R] = (unsigned char)r;
				lpTmp[COLOR_G] = (unsigned char)g;
				lpTmp[COLOR_B] = (unsigned char)b;

				lpTmp += nc;
			}
		}

		return true;
	}
	/////////////////////////////////////////////////////////////////////////////////
	//End of implementation of ColorCorrection class
	/////////////////////////////////////////////////////////////////////////////////


}


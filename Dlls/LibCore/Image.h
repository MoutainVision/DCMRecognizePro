#pragma once


#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include "ImageDef.h"
#include "CameraDef.h"
#include "CommonDef.h"
#include "Mask2D.h"

#include "xiofile.h"

#include<string>
#include<vector>

using std::vector;
using std::string;

#if XIMAGE_SUPPORT_DISTORTION_CORRECTION
#include "..\LibDistortionCorrection\LibDistortionCorrection.h"
#endif // XIMAGE_SUPPORT_DISTORTION_CORRECTION

#if XIMAGE_SUPPORT_SETTING_IO_XML
#include "..\LibTinyXML\LibTinyXML.h"
#endif // XIMAGE_SUPPORT_SETTING_IO_XML



namespace avs
{
#ifndef _LUT_
#define _LUT_
	/**
	* @brief 查找表模板类
	*
	*/
	template <class T>
	class LIBCORE_API Lut
	{
	public:
		T*	m_rTable;
		T*	m_gTable;
		T*	m_bTable;
		int m_nSize;
		int m_nChannel;
		bool m_bDirty;

	private:
		T* m_pData;

	public:
		Lut()
			: m_rTable(nullptr)
			, m_gTable(nullptr)
			, m_bTable(nullptr)
			, m_nSize(0)
			, m_nChannel(0)
			, m_bDirty(false)
			, m_pData(nullptr)
		{
		}

		~Lut()
		{
			if (m_pData)
			{
				delete[] m_pData;
			}
		}

		bool empty()
		{
			return (nullptr == m_pData);
		}

		bool reset(int sz, int c = 3)
		{
			if (sz < 0 || c < 0)
			{
				return false;
			}

			if (sz != m_nSize || m_nChannel != c)
			{
				if (nullptr != m_pData)
				{
					delete[]m_pData;
					m_pData = nullptr;
					m_rTable = m_gTable = m_bTable = nullptr;
				}

				m_nSize = sz;
				m_nChannel = c;

				if (m_nSize > 0 && m_nChannel > 0)
				{
					if (nullptr == (m_pData = new T[m_nSize*m_nChannel]))
					{
						return false;
					}

					m_rTable = m_pData;
					if (m_nChannel == 3)
					{
						m_gTable = m_rTable + m_nSize;
						m_bTable = m_gTable + m_nSize;
					}

					if (m_nSize <= (1 << (sizeof(T) * 8)))
					{
						for (int i = 0; i < m_nSize; ++i)
						{
							m_rTable[i] = (T)i;
							if (m_nChannel == 3)
							{
								m_gTable[i] = (T)i;
								m_bTable[i] = (T)i;
							}
						}
					}
				}
			}

			m_bDirty = false;

			return true;
		}
	};
#endif

	/**
	* @brief Bayer转换参数
	*
	*/
	struct LIBCORE_API DebayerParam
	{
		/**
		* @brief Bayer转换的目标像素格式
		*
		*/
		EPixelFormat eDstPixFmt;

		/**
		* @brief Bayer转换所使用的方法
		*
		*/
		EDebayerMethod eDByrMethod;
	};


	/**
	* @brief 图像处理链条配置。链条的每个环节对应一个算法，由一个开关和若干参数（若需要的话）组成
	*
	*/
	typedef struct LIBCORE_API ImageProcessinChainSetting
	{
		/**
		* @brief Bayer增强开关
		*
		*/
		bool byrEnhEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief Bayer转换开关
		*
		*/
		bool dbyrEnabled;	

		/**
		* @brief Bayer转换参数
		*
		*/
		DebayerParam dbyrPara;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 背景平衡开关
		*
		*/
		bool bbEnabled;	
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 背景图片名
		*
		*/
		string bbFileName;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 白平衡开关
		*
		*/
		bool wbEnabled;

		/**
		* @brief 白平衡参数
		*
		*/
		WhiteBalanceParam wbPara;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 重新计算白平衡开关
		*
		*/
		bool calcWBEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 使用白平衡ROI开关
		*
		*/
		bool useWBROIEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 白平衡ROI值
		*
		*/
		ImageRect wbROI;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 白平衡固定值
		*
		*/
		Point3F ptGain;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 亮度增强开关
		*
		*/
		bool brightEnhEnabled;

		/**
		* @brief 亮度增强值
		*
		*/
		int brightEnhValue;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 对比度增强开关
		*
		*/
		bool contraEnhEnabled;

		/**
		* @brief 对比度增强值
		*
		*/
		int contraEnhValue;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief Gamma增强开关
		*
		*/
		bool gammaEnhEnabled;

		/**
		* @brief Gamma增强值
		*
		*/
		double gammaEnhValue;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 直方图增强开关
		*
		*/
		bool histEnhEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief RGB增强开关
		*
		*/
		bool rgbEnhEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 锐度增强开关
		*
		*/
		bool shpnessEnhEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		/**
		* @brief 色彩增强开关
		*
		*/
		bool colorEnhEnabled;
		//////////////////////////////////////////////////////////////////////////////////

		ImageProcessinChainSetting()
			: byrEnhEnabled(false)
			, dbyrEnabled(false)
			, bbEnabled(false)
			, bbFileName("")
			, wbEnabled(false)
			, calcWBEnabled(true)
			, useWBROIEnabled(true)
			, brightEnhEnabled(false)
			, contraEnhEnabled(false)
			, gammaEnhEnabled(false)
			, histEnhEnabled(false)
			, rgbEnhEnabled(false)
			, shpnessEnhEnabled(false)
			, colorEnhEnabled(false)
		{
		}

		void setSetting(ImageProcessinChainSetting setting);

		void settingToParamAtt(std::vector<ParamInfo> &vctPAttri);
		void paramAttToSetting(std::vector<ParamInfo> vctPAttri);

		/**
		* @brief load controller parameters such as serial, axis, illuminator, magazine, stage, slideloader...etc.
		*
		* @param szSettingFile	[in] filename
		*
		* @note filename without the path.
		*
		* @return false--to deal with failure;to deal with success;
		*
		* @see saveSetting
		*/
		bool load(const char *szSettingFile, std::string strTypeName = "Item");
		/**
		* @brief save controller parameters such as serial, axis, illuminator, magazine, stage, slideloader...etc.
		*
		* @param szSettingFile	[in] filename
		*
		* @note filename without the path.
		*
		* @return false--to deal with failure;to deal with success;
		*
		* @see loadSetting
		*/
		bool save(const char *szSettingFile, std::string strTypeName = "Item");
	}ImgProcChainSetting;


#ifndef _XIMAGE_
#define _XIMAGE_
	/**
	* @brief 图像类。此为AVS平台的核心类，实现了关于图像的一些基本功能，包括：
	*		1. 图像文件读写，支持的图像格式可以通过静态函数getSupportedFileFormates进行查询。
	*		   目前支持BMP,JPG和PNG等三种格式。
	*		2. 图像的创建和生成。用户可以通过构造函数或create函数创建指定像素格式和Bayer格式的图像
	*		3. 图像处理功能，包括
	*			3.1 各种颜色处理，例如调节图像亮度，对比度，伽马，直方图增强，颜色空间转换
	*			3.2 各种几何变换，例如图像缩放（Resize)，翻转，镜像，提取ROI
	*			3.3 各种代数运算，例如图像加、减、乘、除
	*			3.4 常用图像处理，例如二值化，图像形态学、窗宽窗位，滤波，白平衡，畸变校正
	*
	*/
	class LIBCORE_API xImage
	{
		//extensible information collector
		typedef struct tagxImageInfo
		{
			uint32_t	dwEffWidth;			///< uint32_t aligned scan line width
			uint8_t*	pImage;				///< THE IMAGE BITS
			xImage*		pGhost;				///< if this is a ghost, pGhost points to the body
			xImage*		pParent;			///< if this is a layer, pParent points to the body
			uint32_t	dwType;				///< original image format
			char		szLastError[256];	///< debugging
			int32_t		nProgress;			///< monitor
			int32_t		nEscape;			///< escape
			int32_t		nBkgndIndex;		///< used for GIF, PNG, MNG
			RGBQUAD		nBkgndColor;		///< used for RGB transparency
			float		fQuality;			///< used for JPEG, JPEG2000 (0.0f ... 100.0f)
			uint8_t		nJpegScale;			///< used for JPEG [ignacio]
			int32_t		nFrame;				///< used for TIF, GIF, MNG : actual frame
			int32_t		nNumFrames;			///< used for TIF, GIF, MNG : total number of frames
			uint32_t	dwFrameDelay;		///< used for GIF, MNG
			int32_t		xDPI;				///< horizontal resolution
			int32_t		yDPI;				///< vertical resolution
			ImageRect	rSelectionBox;		///< bounding rectangle
			uint8_t		nAlphaMax;			///< max opacity (fade)
			bool		bAlphaPaletteEnabled; ///< true if alpha values in the palette are enabled.
			bool		bEnabled;			///< enables the painting functions
			int32_t		xOffset;
			int32_t		yOffset;
			uint32_t	dwCodecOpt[MAX_IMAGE_FORMATS];	///< for GIF, TIF : 0=def.1=unc,2=fax3,3=fax4,4=pack,5=jpg
			RGBQUAD		last_c;				///< for GetNearestIndex optimization
			uint8_t		last_c_index;
			bool		last_c_isvalid;
			int32_t		nNumLayers;
			uint32_t	dwFlags;			///< 0x??00000 = reserved, 0x00??0000 = blend mode, 0x0000???? = layer id - user flags
			uint8_t		dispmeth;
			bool		bGetAllFrames;
			bool		bLittleEndianHost;

#if XIMAGE_SUPPORT_EXIF
			EXIFINFO ExifInfo;
#endif

		} XIMAGEINFO;

	public:
		static string getSupportedFileFormats();

	public:
		//public structures
		struct rgb_color { uint8_t r, g, b; };

#if XIMAGE_SUPPORT_WINDOWS
	public:
		// <VATI> text placement data
		// members must be initialized with the InitTextInfo(&this) function.
		typedef struct tagCxTextInfo
		{
#if defined (_WIN32_WCE)
			TCHAR    text[256];  ///< text for windows CE
#else
			TCHAR    text[4096]; ///< text (char -> TCHAR for UNICODE [Cesar M])
#endif
			LOGFONT		lfont;      ///< font and codepage data
			COLORREF	fcolor;     ///< foreground color
			int32_t		align;      ///< DT_CENTER, DT_RIGHT, DT_LEFT aligment for multiline text
			uint8_t     smooth;     ///< text smoothing option. Default is false.
			uint8_t     opaque;     ///< text has background or hasn't. Default is true.
									///< data for background (ignored if .opaque==FALSE) 
			COLORREF	bcolor;     ///< background color
			float		b_opacity;  ///< opacity value for background between 0.0-1.0 Default is 0. (opaque)
			uint8_t     b_outline;  ///< outline width for background (zero: no outline)
			uint8_t     b_round;    ///< rounding radius for background rectangle. % of the height, between 0-50. Default is 10.
									///< (backgr. always has a frame: width = 3 pixel + 10% of height by default.)
		} CXTEXTINFO;


		static bool showImage(unsigned char *pImage, int nWidth, int nHeight, int nBitsPerPixel,
			HWND hDisplayWnd,
			EDisplayMode dm = DM_FIT_TO_WINDOW,
			int nDispOffsetX = 0,
			int nDispOffsetY = 0);

		void display(HWND hWnd, EDisplayMode eDispMode=DM_FIT_TO_WINDOW, int nDispOffX=0, int nDispOffY=0);

#endif

	protected:
		unsigned char *m_pBuffer;
		unsigned	   m_nWidth;
		unsigned	   m_nHeight;
		unsigned	   m_nBpp;
		unsigned	   m_nPitch;
		unsigned       m_nImgSize;
		EPixelFormat   m_pixFmt;
		EBayerFormat   m_byrFmt;

		bool		   m_bAligned;

		BITMAPINFOHEADER    m_bmpHead; //standard header
		XIMAGEINFO		m_extInfo; //extended information

		RGBQUAD			*m_pPalette;
		unsigned		m_nPalSize;

		unsigned char  *m_pAlpha;

	public:
		static unsigned calcBPP(EPixelFormat pixFmt);

		static unsigned calcImagePitch(unsigned nW, unsigned nBpp, bool bAligned=true);

		static EImageFormat getImageFormat(const int index);
		static EImageFormat getImageFormat(const string &strFileFullName);
		static int getImageFormatIndex(EImageFormat fmt);

#if XIMAGE_SUPPORT_ALPHA
		/** \addtogroup Alpha */ //@{
		void alphaClear();
		bool alphaCreate();
		void alphaDelete();
		void alphaInvert();
		bool alphaMirror();
		bool alphaFlip();
		bool alphaCopy(const xImage &from);
		bool alphaSplit(xImage *dest);
		void alphaStrip();
		void alphaSet(uint8_t level);
		bool alphaSet(xImage &from);
		bool alphaSet(const int32_t x, const int32_t y, const uint8_t level);
		uint8_t alphaGet(const int32_t x, const int32_t y);
		uint8_t alphaGetMax() const;
		void alphaSetMax(uint8_t nAlphaMax);
		bool alphaIsValid();
		uint8_t* alphaGetPointer(const int32_t x = 0, const int32_t y = 0);
		bool alphaFromTransparency();

		void alphaPaletteClear();
		void alphaPaletteEnable(bool enable = true);
		bool alphaPaletteIsEnabled();
		bool alphaPaletteIsValid();
		bool alphaPaletteSplit(xImage *dest);

		unsigned char* getAlpha() const;
		//@}

	protected:
		/** \addtogroup Protected */ //@{
		unsigned char blindAlphaGet(const int x, const int y);
	//@}
#endif //XIMAGE_SUPPORT_ALPHA

#if XIMAGE_SUPPORT_DECODE
	public:
		bool load(const char *szImgFile);
		bool decode(FILE *hFile, EImageFormat fmt);
		bool decode(xFile *hFile, EImageFormat fmt);
#endif

#if XIMAGE_SUPPORT_ENCODE
	protected:
		/** \addtogroup Protected */ //@{
		bool safeForEncode(xFile *hFile);
		//@}
	public:
		bool save(const char *szImgFile);
		bool encode(FILE *hFile, EImageFormat fmt);
		bool encode(xFile *hFile, EImageFormat fmt);
#endif
		////////////////////////////////////////////////////////////////////////////////
		/**
		 * \sa SetCodecOption
		 */
		unsigned getCodecOption(EImageFormat fmt);
		////////////////////////////////////////////////////////////////////////////////
		/**
		 * Encode option for GIF, TIF, JPG, PNG and RAW
		 * - GIF : 0 = LZW (default), 1 = none, 2 = RLE.
		 * - TIF : 0 = automatic (default), or a valid compression code as defined in "tiff.h" (COMPRESSION_NONE = 1, COMPRESSION_CCITTRLE = 2, ...)
		 * - JPG : valid values stored in enum CODEC_OPTION ( ENCODE_BASELINE = 0x01, ENCODE_PROGRESSIVE = 0x10, ...)
		 * - PNG : combination of interlace option and compression option
		 *         interlace option :  1 = interlace, 0 = no interlace
		 *         compression option : 2 = no compression, 4 = best speed, 6 = best compression, 8 = default compression
		 *         default is no interlace and default compression
		 *         example : 5 = 1+4 = interlace + best speed
		 * - RAW : valid values stored in enum CODEC_OPTION ( DECODE_QUALITY_LIN = 0x00, DECODE_QUALITY_VNG = 0x01, ...)
		 *
		 * \return true if everything is ok
		 */
		bool setCodecOption(unsigned opt, EImageFormat fmt);

		void initialize();

	public:
		xImage(void);

		xImage(EImageFormat fmt);

		xImage(const char *szImgFile);

		xImage(const xImage &img);

		//xImage(unsigned nW, unsigned nH, unsigned nBpp, bool bAligned=true);

		xImage(unsigned nW, unsigned nH, 
			bool bAligned = true, 
			EPixelFormat pixFmt = PIXEL_FORMAT_BGR, 
			EBayerFormat bayFmt = BAYER_FORMAT_NONE,
			unsigned char ucInitVal = 0);
		
		//note: the input buffer pBuf should be 4-bytes aligned
		xImage(const unsigned char *pBuf, unsigned nW, unsigned nH, 
			bool bAligned = true, 
			EPixelFormat pixFmt = PIXEL_FORMAT_BGR, 
			EBayerFormat bayFmt = BAYER_FORMAT_NONE);

		void release();

		virtual ~xImage(); 

		bool create(unsigned nW, unsigned nH, 
			bool bAligned = true, 
			EPixelFormat pixFmt = PIXEL_FORMAT_BGR, 
			EBayerFormat bayFmt = BAYER_FORMAT_NONE,
			unsigned char ucInitVal = 0);
		
		//note: the input buffer pBuf should be 4-bytes aligned
		bool create(const unsigned char *pBuf, unsigned nW, unsigned nH, 
			bool bAligned = true, 
			EPixelFormat pixFmt = PIXEL_FORMAT_BGR, 
			EBayerFormat bayFmt = BAYER_FORMAT_NONE);

		////////////////////////////////////////////////////////////////////////////////
		/**
		 * Initializes or rebuilds the image.
		 * \param dwWidth: width
		 * \param dwHeight: height
		 * \param wBpp: bit per pixel, can be 1, 4, 8, 24
		 * \param imagetype: (optional) set the image format, see ENUM_CXIMAGE_FORMATS
		 * \return pointer to the internal pDib object; NULL if an error occurs.
		 */
		bool create(unsigned dwWidth, unsigned dwHeight, unsigned wBpp, EImageFormat fmt = XIMAGE_FORMAT_BMP);
					   		 	  
		void destroy();

		bool transfer(xImage &from, bool bTransferFrames = true);

	public:
		uint8_t	getJpegQuality() const;
		void	setJpegQuality(uint8_t q);
		float	getJpegQualityF() const;
		void	setJpegQualityF(float q);

		uint8_t	getJpegScale() const;
		void	setJpegScale(uint8_t q);


	public:
		int	getXDPI() const;
		int	getYDPI() const;
		void setXDPI(int dpi);
		void setYDPI(int dpi);

		unsigned getColorCount() const;

		/**
		 * \sa SetClrImportant
		 */
		unsigned getClrImportant() const;

		/**
		 * sets the maximum number of colors that some functions like
		 * DecreaseBpp() or GetNearestIndex() will use on indexed images
		 * \param nColors should be less than 2^bpp,
		 * or 0 if all the colors are important.
		 */
		void setClrImportant(unsigned nColors = 0);

		int		getTransIndex() const;
		RGBQUAD	getTransColor();
		void	setTransIndex(int idx);
		void	setTransColor(RGBQUAD rgb);
		bool	isTransparent() const;

	public:
		/** \addtogroup Palette
		 * These functions have no effects on RGB images and in this case the returned value is always 0.
		 * @{ */
		/**
		 * create a palette with given number of colors
		*/
		bool createPalette(unsigned char nColors);
		
		/**
		 * delete the palette 
		*/
		void deletePalette();
		
	
		/**
		 * returns the pointer to the first palette index
		*/
		RGBQUAD* getPalette() const;
		
		/**
		 * returns the palette color item
		 */
		unsigned getPaletteItemCount() const;
		
		/**
		 * returns the palette dimension in byte
		 */
		unsigned getPaletteSize() const;
		
		/**
		 * check if the image has a palette
		 */
		bool hasPalette() const;

		/**
		 * copy the palette from another image
		 */
		bool copyPalette(const xImage &from);

		/**
		* Returns true if the image has 256 colors and a linear grey scale palette.
		*/
		bool	isGrayScale();

		/**
		 * Returns true if the image has 256 colors or less.
		 */
		bool	isIndexed() const;

		//bool	IsSamePalette(CxImage &img, bool bCheckAlpha = true);

		/**
		 * Returns the color of the specified index.
		 */
		RGBQUAD getPaletteColor(unsigned char idx);

		/**
		 * Returns the color of the specified index.
		 * \param i = palette index
		 * \param r, g, b = output color channels
		 */
		bool	getPaletteColor(unsigned char i, unsigned char* r, unsigned char* g, unsigned char* b);
		//uint8_t	GetNearestIndex(RGBQUAD c);
		//void	BlendPalette(COLORREF cr, int32_t perc);
		
		/**
		 * Sets (or replaces) the palette to gray scale palette.
		 * The function doesn't change the pixels; for standard
		 * gray scale conversion use GrayScale().
		 */
		bool	setGrayPalette();
		
		void	setPalette(uint32_t n, uint8_t *r, uint8_t *g, uint8_t *b);
		//void	SetPalette(RGBQUAD* pPal, uint32_t nColors = 256);
		bool	setPalette(rgb_color *rgb, unsigned nColors = 256);
		bool	setPaletteColor(unsigned char idx, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 0);
		bool	setPaletteColor(unsigned char idx, RGBQUAD c);
		bool	setPaletteColor(unsigned char, COLORREF cr);
		
		/**
		 * swap two indexes in the image and their colors in the palette
		 */
		bool	swapIndex(unsigned char idx1, unsigned char idx2);
		
		/**
		 * swap Red and Blue colors
		 */
		bool	swapRGB2BGR();

		//void	SetStdPalette();
		//@}

protected:
		/** \addtogroup Protected */ //@{
		unsigned char blindGetPixelIndex(const int x, const int y);
		RGBQUAD blindGetPixelColor(const int x, const int y, bool bGetAlpha = true);
		void *blindGetPixelPointer(const int x, const  int y);
		void blindSetPixelColor(int x, int y, RGBQUAD c, bool bSetAlpha = false);
		void blindSetPixelIndex(int x, int y, unsigned char i);
		//@}

		/**
		 * swaps the blue and red components (for RGB images)
		 * \param buffer : pointer to the pixels
		 * \param length : number of bytes to swap. lenght may not exceed the scan line.
		 */
		bool RGBtoBGR(unsigned char *buffer, unsigned length);

	public:

		bool copyData(const unsigned char *pBuf, unsigned nBufSize);

		bool copyData(int xdst, int ydst, xImage &srcImg, int xsrc, int ysrc, int cx, int cy);
		bool copyData(int xdst, int ydst, xImage &srcImg, const ImageRect &r);

		bool isValid();
		const bool isValid() const;

		unsigned char* getBuffer();
		unsigned char* getScanLine(unsigned y);
		unsigned getWidth();
		unsigned getHeight();
		unsigned getBPP();
		unsigned getChannels();
		unsigned getPitch();
		unsigned getImageSize();
		EPixelFormat getPixelFormat();
		EBayerFormat getBayerFormat();
		bool getAlignment();

		const unsigned char* getBuffer() const;
		const unsigned char* getScanLine(unsigned y) const;
		const unsigned getWidth() const;
		const unsigned getHeight() const;
		const unsigned getBPP() const;
		const unsigned getChannels() const;
		const unsigned getPitch() const;
		const unsigned getImageSize() const;
		const EPixelFormat getPixelFormat() const;
		const EBayerFormat getBayerFormat() const;
		const bool getAlignment() const;

		bool isGrayscale();

		bool isBGR();
		bool isRGB();
		const bool isBGR() const;
		const bool isRGB() const;

		bool isInside(int x, int y);
		bool isTransparent(int x, int y);
		unsigned char getPixelIndex(int x, int y);
		RGBQUAD getPixelColor(int x, int y, bool bGetAlpha = true);
		unsigned char getNearestIndex(RGBQUAD c);

		bool copyFrom(const xImage &srcImg);
		bool copyTo(xImage &desImg);

		//color transformations
		//exchange the R and B channel
		bool swap(xImage *pDstImg=nullptr);

		//exchange the R and B channel and add a U channel
		bool swapUG(xImage *pDstImg = nullptr);

		//exchange the R and B channel and remove the U channel
		bool swapDG(xImage *pDstImg = nullptr);

		bool rgb24To32(xImage *pDstImg = nullptr);
		bool rgb32To24(xImage *pDstImg = nullptr);
		
		//operators
		xImage& operator=(const xImage &rhs);
		xImage operator+(const xImage &rhs);
		xImage operator-(const xImage &rhs);

		xImage operator+(int nOffset);
		xImage operator-(int nOffset);
		xImage operator*(float fScale);
		xImage operator/(float fScale);
		
		xImage& operator+=(const xImage &rhs);
		xImage& operator-=(const xImage &rhs);
		
		xImage& operator+=(int nOffset);
		xImage& operator-=(int nOffset);
		xImage& operator*=(float fScale);
		xImage& operator/=(float fScale);


		bool debayer(EPixelFormat desPxFmt = PIXEL_FORMAT_BGR, 
					 EDebayerMethod dm = DEBAYER_AVERAGE,
					 xImage *pDesImg=nullptr);
		bool debayerGRBG(xImage &dstImg, EPixelFormat pxFmt = PIXEL_FORMAT_BGR, EDebayerMethod dm = DEBAYER_AVERAGE);

		bool debayerRGGB(xImage &dstImg, EPixelFormat pxFmt = PIXEL_FORMAT_BGR, EDebayerMethod dm = DEBAYER_AVERAGE);

		bool debayerGBRG(xImage &desImg, EPixelFormat pxFmt = PIXEL_FORMAT_BGR, EDebayerMethod dm = DEBAYER_AVERAGE);

		bool debayerBGGR(xImage &dstImg, EPixelFormat pxFmt = PIXEL_FORMAT_BGR, EDebayerMethod dm = DEBAYER_AVERAGE);

		//RGGB (RedX, RedY)(0,0)
		//GRBG (RedX, RedY)(1,0)
		//GBRG (RedX, RedY)(0,1)
		//BGGR (RedX, RedY)(1,1)
		bool debayerHQLinear(xImage& desImg, int RedX, int RedY, EPixelFormat pixFormat);

		bool convert(EPixelFormat dstPixFmt = PIXEL_FORMAT_MONO8, xImage *pDstImg = nullptr);

		bool grayscale(xImage *pDstImg = nullptr);

		bool monoToRGB(EPixelFormat dstPixFmt = PIXEL_FORMAT_BGR, xImage *pDstImg = nullptr);

		bool getRChannel(xImage &rImg);
		bool getGChannel(xImage &gImg);
		bool getBChannel(xImage &bImg);


		///////////////////////////////////////////////////////////////////////////////
		//geometric transformations
		/**
		*@brief 水平翻转。
		*
		* Flip horizontally
		*
		*@param pDstImg	[out] 指向目标图像的指针
		* Pointer to the destination image
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool mirror(xImage *pDstImg=nullptr);

		/**
		*@brief 垂直翻转。
		*
		* Flip vertically
		*
		*@param pDstImg	[out] 指向目标图像的指针
		* Pointer to the destination image
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool flip(xImage *pDstImg=nullptr);

		/**
		*@brief 旋转图像。
		*
		* rotate the image
		*
		*@param pDstImg	[out] 指向目标图像的指针
		* Pointer to the destination image
		*
		*@param dTheta	[in] 旋转角度，以度为单位
		* the rotation angle in degree
		*
		*@param iim	[in] 图像插值方法
		* the image interpolation method
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool rotate(double dTheta, EImageInterpolationMethod iim = IIM_NEAREST_NEIGHBOR, xImage *pDstImg=nullptr);

		bool resize(int nNewW, int nNewH, EImageInterpolationMethod iim = IIM_NEAREST_NEIGHBOR, xImage *pDesImg = nullptr);
		bool resizeNNI(int nNewW, int nNewH, xImage *pDesImg = nullptr);
		bool resizeMA(int nNewW, int nNewH, xImage *pDstImg = nullptr);
		bool resizeBI(int nNewW, int nNewH, xImage *pDesImg = nullptr);
		bool resizeCI(int nNewW, int nNewH, xImage *pDesImg = nullptr);
		///////////////////////////////////////////////////////////////////////////////


		//R-G-B to Y-Cb-Cr
		bool RGB2YCbCr(xImage &dstImg);

		//R-G-B to Y-Cb-Cr
		bool YCbCr2RGB(xImage &dstImg);

		//histogram processing
		//note: only for RGB, BGR or Mono xImage
		bool getHistogram(int histR[256], int histG[256], int histB[256]);

		/**
		*@brief 直方图均衡化
		*
		* Histogram equalization
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool equalizeHistogram();

		/**
		*@brief 获得图像的指定AOI
		*
		* Get the specified AOI 
		*
		*@param imgRoi	[out] 待返回的图像AOI
		* image AOI to be returned
		*
		*@param xs	[in] AOI起始x位置
		* starting x pos of AOI
		*
		*@param ys	[in] AOI起始y位置
		* starting y pos of AOI
		*
		*@param w	[in] AOI宽度
		* width of AOI
		*
		*@param h	[in] AOI高度
		* height of AOI
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool roi(xImage &imgRoi, int xs, int ys, int w, int h);

		/**
		*@brief 窗宽窗位变换。源自CT图像
		*
		* Window width and level transform
		*
		*@param pDstImg	[out] 指向目标图像的指针
		* Pointer to the destination image
		*
		*@param nWinCentre	[in] 窗位
		* level of window
		*
		*@param nWinWidth	[in] 窗宽
		* width of window
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool windowLevelTransform(int nWinCentre, int nWindWidth, xImage *pDstImg=nullptr);


		/**
		*@brief 数学形态学变换
		*
		* Mathematical Morphological Transform
		*
		*@param pDstImg	[out] 指向目标图像的指针
		* Pointer to the destination image
		*
		*@param se	[in] 结构元素
		* structuring element
		*
		*@param eType	[in] 形态学算子类型
		* type of morphological operator
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool morphology(StructuringElement se, EMorphType eType,  xImage *pDstImg=nullptr);
		bool morph_dilate(StructuringElement se, xImage *pDstImg = nullptr);
		bool morph_erode(StructuringElement se, xImage *pDstImg = nullptr);
		bool morph_open(StructuringElement se, xImage *pDstImg = nullptr);
		bool morph_close(StructuringElement se, xImage *pDstImg = nullptr);
		bool morph_tophat(StructuringElement se, xImage *pDstImg = nullptr);
		bool morph_bottomhat(StructuringElement se, xImage *pDstImg = nullptr);

		bool filter2D(vector<double> &aKernel, xImage *pDstImg = nullptr);
		//sharpening: pKernel={0,-1,0,-1,5,-1,0,-1,0}, pKernel={-1,-1,-1,-1,9,-1,-1,-1,-1}
		//edge detection: pKernel={0,-1,0,-1,4,-1,0,-1,0}, pKernel={-1,-1,-1,-1,8,-1,-1,-1,-1}
		//smoothing: pKernel={1,1,1,1,1,1,1,1,1}/9, pKernel={1,2,1,2,4,2,1,2,1}/16
		bool filter2D(double *pKernel, int nKernelRadius, xImage *pDstImg = nullptr);

		bool bilateralFilter(double dSigmaC = 3.0, double dSigmaS = 10, xImage *pDstImg = nullptr);

		bool smoothGaussian3();
		bool smoothGaussian5();
		bool smoothGaussian(double dSigma = 3.0, xImage *pDstImg = nullptr);

		bool medianFilter(int nFilterRadius = 1, xImage *pDstImg = nullptr);

		bool enhanceLog(ImageRect *roi = nullptr);
		bool enhanceExp(ImageRect *roi = nullptr);

		bool saturate(unsigned char ucSatuVal = 255);

		bool adjustGain(float fRGain = 1.0f, float fGGain = 1.0f, float fBGain = 1.0f);//range: [0.0,10.0]

		bool adjustContrast(int contrastLevel = 0);		//range: [-255,255]

		bool adjustBrightness(int brightnessOffset = 0);	//range: [-255, 255]

		bool adjustBrightnessAndContrast(int brightnessOffset = 0, int contrastLevel = 0, unsigned char threshold = 128);//based on PS formula

		bool adjustGamma(double dGamma = 1.0);

		bool inverse();

		bool solarise(unsigned char threshold = 255);

		bool threshold(int nT = -1, xImage *pDstBinaryImage = nullptr);

		//Gray World Algorithm
		bool calcWhiteBalanceGW(float &dRGain, float &dGGain, float &dBGain, int nMaxGray = -1, ImageRect *roi = nullptr);
		
		//Perfect Reflection Algorithm
		bool calcWhiteBalancePR(float &dRGain, float &dGGain, float &dBGain, int nMaxGray = -1, double dRatio = 0.1, ImageRect *roi = nullptr);
		
		bool calcWhiteBalance(float &dRGain, float &dGGain, float &dBGain, WBParam *pWBParam = nullptr, ImageRect *aoi = nullptr);

		static bool calcLut(Lut<unsigned char> &lut, float dRGain, float dGGain, float dBGain);

		bool whiteBalance(Lut<unsigned char> &lut, ImageRect *roi = nullptr);

		bool whiteBalance(float dRGain, float dGGain, float dBGain, ImageRect *roi = nullptr);

		bool whiteBalance(WBParam *wbParam=nullptr, ImageRect *roi = nullptr);

		bool getIntensity(unsigned char g[3]);

		//get the average intensity of each channel on the predefined regions
		bool getIntensity(unsigned char g[3], vector<ImageRect> &aAOI);

		//get the mask where the intensity or the green channel of pixel is bigger than the threshold
		bool getMask(Mask2D &mask, unsigned char ucThr = 0);

		//get the average intensity based on the mask
		bool getIntensity(unsigned char &g, Mask2D &mask);

		//get the coefficient of variation of intensity, where pIntensityImage returns the intensity of each block
		bool getIntensityCV(double &dCV, double &dStd, double &dMean, 
							int nBlkWidth = 32, int nBlkHeight = 32, 
							xImage *pIntensityImage=nullptr);

		//get the coefficient of variation of intensity, where pIntensityImage returns the intensity of each block
		bool getIntensityCV(double &dCV, double &dStd, double &dMean, 
							int nRow = 10, int nCol = 14, 
							EColorChannel chn=COLOR_CHANNEL_G, 
							xImage *pIntensityImage=nullptr);
	
		//get the heat map by intensity
		bool getIntensityHeatMap(xImage &heatImage, double &dCV, double &dStd, double &dMean, 
								int nBlkWidth = 32, int nBlkHeight = 32, bool bAbsMode=false);
		
		//get the heat map by intensity
		bool getIntensityHeatMap(xImage &heatImage, double &dCV, double &dStd, double &dMean, 
								int nRow = 10, int nCol = 14,
								EColorChannel chn = COLOR_CHANNEL_G,
								bool bAbsMode=false);

		//set color for specified region
		bool setColor(ImageRect rect, unsigned char r, unsigned char g, unsigned char b);
		//set color for pixels specified by a mask
		bool setColor(Mask2D &mask, unsigned char color[3]);

		/**
		*@brief 图像匹配（只考虑平移）
		*
		* Image matching
		*
		*@param imgRef [in] 参考图像
		* reference image
		*
		*@param pRectRef [in] 参考图像中的匹配范围
		* matching range in reference image
		*
		*@param pRect [in] 本图像中的匹配范围
		* matching range in current image
		*
		*@param offset	[out] 当前图像对参考图像的偏移
		* offset to the reference image
		*
		*@return -成功则返回true，否则返回false
		* -return true if succeed, else return false
		*
		*@note -
		*
		*@remarks -
		*/
		bool match(Offset2I &offset, const xImage &imgRef, const ImageRect *pRectRef=nullptr, const ImageRect *pRect=nullptr);

		bool merge(const xImage &imgRef, const Offset2I &offset, xImage *pDstImg = nullptr);

#if XIMAGE_SUPPORT_DISTORTION_CORRECTION
		bool undistort(division_model dm, unsigned nCropLength = 0, double dUndistRadius = 0.0, xImage *pDstImg = nullptr);
#endif // XMAGE_SUPPORT_DISTORTION_CORRECTION


		/**
		*@brief 执行图像处理链条
		*
		*@param ipcSetting [in] 链条设置
		*
		*@param pDstImg [in/out] 目的图像。若为空（nullptr），则以自身为目的图像
		*
		*@return -成功则返回true，否则返回false
		*
		*@note -
		*
		*@remarks -
		*/
		bool executeProcChain(const ImgProcChainSetting &ipcSetting, xImage *pDstImg=nullptr);

		/**
		*@brief 将图像输出为Base64字节流
		*
		*@param base64 [in/out] 待输出base64字节流指针
		*
		*@param size [out] 待输出的base64字节流长度
		*
		*@return -成功则返回true，否则返回false
		*
		*@note -
		*
		*@remarks -
		*/
		bool toBase64(char *base64, int &size);
	};
#endif


#ifndef _BACKGROUND_BALANCE_
#define _BACKGROUND_BALANCE_
	class LIBCORE_API BackgroundBalance
	{

		//calling example:
		//
		//method 1:
		//CvmxImage bkgimg, fgimg;
		//BackgroundBalance bb(bkgimg);
		////bb.CalcBalanceBK();
		//bb.Execute(fgImg);

		//method 2:
		//CvmxImage bkgimg, fgimg;
		//BackgroundBalance bb;
		//bb.setBkgImage(bkgimg);
		////bb.CalcBalanceBK();
		//bb.Execute(fgImg);

	public:
		BackgroundBalance();

		BackgroundBalance(const xImage &bkgImg);

		virtual ~BackgroundBalance();

		bool setBkgImage(const xImage &bkgImg);

		bool calcBalanceBK();

		bool execute(xImage &fgImg);

		bool isReady();

		void setROI(ImageRect imgROI);

		bool isROISet();
	private:
		xImage			m_bkgImg;
		Lut<unsigned char>	m_lut;
		bool				m_bReady;
		ImageRect			m_imgROI;//Image ROI for background balance
		bool				m_bROISet;
	};
#endif

#ifndef _COLOR_CORRECTION_
#define _COLOR_CORRECTION_
	class LIBCORE_API ColorCorrection
	{
	public:
		ColorCorrection();
		~ColorCorrection();
		void calcColorMatrix(int iCC);
		bool apply(xImage &img);

	private:
		int	 m_cc;
		bool m_bfactor;

		//color temperature
		int m_ct_r;
		int m_ct_g;
		int m_ct_b;

		//color matrix
		int  m_matrix[9];

		//look-up table
		int	m_lut[9 * 256];
	};
#endif

}


#pragma once

#if defined(_WIN32) || defined(_WIN32_WCE)
#include <windows.h>
#include <tchar.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CxImage supported features
#define XIMAGE_SUPPORT_ALPHA          1
#define XIMAGE_SUPPORT_SELECTION      1
#define XIMAGE_SUPPORT_TRANSFORMATION 1
#define XIMAGE_SUPPORT_DSP            1
#define XIMAGE_SUPPORT_LAYERS		   1
#define XIMAGE_SUPPORT_INTERPOLATION  1

#define XIMAGE_SUPPORT_DECODE	1
#define XIMAGE_SUPPORT_ENCODE	1		//<vho><T.Peck>
#define	XIMAGE_SUPPORT_WINDOWS 1
#define	XIMAGE_SUPPORT_EXIF    1


#define XIMAGE_SUPPORT_DISTORTION_CORRECTION 1
#define XIMAGE_SUPPORT_SETTING_IO_XML 1

// xImage supported formats
#define XIMAGE_SUPPORT_BMP 1
#define XIMAGE_SUPPORT_GIF 0
#define XIMAGE_SUPPORT_JPG 1
#define XIMAGE_SUPPORT_PNG 1
#define XIMAGE_SUPPORT_ICO 0
#define XIMAGE_SUPPORT_TIF 0
#define XIMAGE_SUPPORT_TGA 0
#define XIMAGE_SUPPORT_PCX 0
#define XIMAGE_SUPPORT_WBMP 0
#define XIMAGE_SUPPORT_WMF 0

#define XIMAGE_SUPPORT_JP2 0
#define XIMAGE_SUPPORT_JPC 0
#define XIMAGE_SUPPORT_PGX 0
#define XIMAGE_SUPPORT_PNM 0
#define XIMAGE_SUPPORT_RAS 0

#define XIMAGE_SUPPORT_JBG 0		// GPL'd see ../jbig/copying.txt & ../jbig/patents.htm

#define XIMAGE_SUPPORT_MNG 0
#define XIMAGE_SUPPORT_SKA 0
#define XIMAGE_SUPPORT_RAW 0
#define XIMAGE_SUPPORT_PSD 0


#define XIMAGE_DEFAULT_DPI 96


namespace avs
{

#ifndef _COLOR_CHANNEL_
#define _COLOR_CHANNEL_
	enum EColorChannel
	{
		COLOR_CHANNEL_R = 0,
		COLOR_CHANNEL_G,
		COLOR_CHANNEL_B,
		COLOR_CHANNEL_ALL
	};
#endif

#ifndef _PIXEL_FORMAT_
#define _PIXEL_FORMAT_
	enum EPixelFormat
	{
		PIXEL_FORMAT_MONO8			= 0x80000000,		/**< 8 bits of mono information. */
		PIXEL_FORMAT_MONO12			= 0x00100000,		/**< 12 bits of mono information. */
		PIXEL_FORMAT_MONO16			= 0x04000000,		/**< 16 bits of mono information. */
		PIXEL_FORMAT_S_MONO16		= 0x01000000,		/**< 16 bits of signed mono information. */
		PIXEL_FORMAT_RAW8			= 0x00400000,		/**< 8 bit raw data output of sensor. */
		PIXEL_FORMAT_RAW12			= 0x00080000,		/**< 12 bit raw data output of sensor. */
		PIXEL_FORMAT_RAW16			= 0x00200000,		/**< 16 bit raw data output of sensor. */
		PIXEL_FORMAT_BAYER8			= PIXEL_FORMAT_RAW8,
		PIXEL_FORMAT_BAYER12		= PIXEL_FORMAT_RAW12,
		PIXEL_FORMAT_BAYER16		= PIXEL_FORMAT_RAW16,
		PIXEL_FORMAT_444YUV8		= 0x10000000,		/**< YUV 4:4:4. */
		PIXEL_FORMAT_422YUV8		= 0x20000000,		/**< YUV 4:2:2. */
		PIXEL_FORMAT_422YUV8_JPEG	= 0x40000001,		/**< JPEG compressed stream. */
		PIXEL_FORMAT_411YUV8		= 0x40000000,		/**< YUV 4:1:1. */
		PIXEL_FORMAT_RGB8			= 0x08000000,		/**< R = G = B = 8 bits. */
		PIXEL_FORMAT_RGB			= PIXEL_FORMAT_RGB8,/**< 24 bit RGB. */
		PIXEL_FORMAT_RGB16			= 0x02000000,		/**< R = G = B = 16 bits. */
		PIXEL_FORMAT_S_RGB16		= 0x00800000,		/**< R = G = B = 16 bits signed. */
		PIXEL_FORMAT_RGBU			= 0x40000002,		/**< 32 bit RGBU. */
		PIXEL_FORMAT_BGR			= 0x80000008,		/**< 24 bit BGR. */
		PIXEL_FORMAT_BGR16			= 0x02000001,		/**< R = G = B = 16 bits. */
		PIXEL_FORMAT_BGRU			= 0x40000008,		/**< 32 bit BGRU. */
		PIXEL_FORMAT_BGRU16			= 0x02000002,		/**< 64 bit BGRU. */
		PIXEL_FORMAT_INDEXED_1		= 0x00040000,		/**< 1 bit indexed image. */
		PIXEL_FORMAT_INDEXED_2		= 0x00040001,		/**< 2 bit indexed image. */
		PIXEL_FORMAT_INDEXED_4		= 0x00020000,		/**< 4 bit indexed image. */
		PIXEL_FORMAT_INDEXED_8		= 0x00020001,		/**< 8 bit indexed image. */
		NUM_PIXEL_FORMATS = 27,							/**< Number of pixel formats. */
		UNSPECIFIED_PIXEL_FORMAT = 0					/**< Unspecified pixel format. */
	};
#endif

#ifndef _IMG_INTERPOLATION_METHOD_
#define _IMG_INTERPOLATION_METHOD_
	enum EImageInterpolationMethod
	{
		IIM_NEAREST_NEIGHBOR = 0,
		IIM_BILINEAR,
		IIM_BICUBIC,
		IIM_MA
	};
#endif


#ifndef _DEBAYER_METHOD_
#define _DEBAYER_METHOD_
	enum EDebayerMethod
	{
		DEBAYER_AVERAGE = 0,
		DEBAYER_BILINEAR,
		DEBAYER_HQLI,
		DEBAYER_BINNING
	};
#endif

#ifndef _E_IMAGE_FORMAT_
#define _E_IMAGE_FORMAT_
	// xImage formats enumerator
	enum EImageFormat
	{
		XIMAGE_FORMAT_UNKNOWN = 0,
#if XIMAGE_SUPPORT_BMP
		XIMAGE_FORMAT_BMP = 1,
#endif
#if XIMAGE_SUPPORT_GIF
		XIMAGE_FORMAT_GIF = 2,
#endif
#if XIMAGE_SUPPORT_JPG
		XIMAGE_FORMAT_JPG = 3,
#endif
#if XIMAGE_SUPPORT_PNG
		XIMAGE_FORMAT_PNG = 4,
#endif
#if XIMAGE_SUPPORT_ICO
		XIMAGE_FORMAT_ICO = 5,
#endif
#if XIMAGE_SUPPORT_TIF
		XIMAGE_FORMAT_TIF = 6,
#endif
#if XIMAGE_SUPPORT_TGA
		XIMAGE_FORMAT_TGA = 7,
#endif
#if XIMAGE_SUPPORT_PCX
		XIMAGE_FORMAT_PCX = 8,
#endif
#if XIMAGE_SUPPORT_WBMP
		XIMAGE_FORMAT_WBMP = 9,
#endif
#if XIMAGE_SUPPORT_WMF
		XIMAGE_FORMAT_WMF = 10,
#endif
#if XIMAGE_SUPPORT_JP2
		XIMAGE_FORMAT_JP2 = 11,
#endif
#if XIMAGE_SUPPORT_JPC
		XIMAGE_FORMAT_JPC = 12,
#endif
#if XIMAGE_SUPPORT_PGX
		XIMAGE_FORMAT_PGX = 13,
#endif
#if XIMAGE_SUPPORT_PNM
		XIMAGE_FORMAT_PNM = 14,
#endif
#if XIMAGE_SUPPORT_RAS
		XIMAGE_FORMAT_RAS = 15,
#endif
#if XIMAGE_SUPPORT_JBG
		XIMAGE_FORMAT_JBG = 16,
#endif
#if XIMAGE_SUPPORT_MNG
		XIMAGE_FORMAT_MNG = 17,
#endif
#if XIMAGE_SUPPORT_SKA
		XIMAGE_FORMAT_SKA = 18,
#endif
#if XIMAGE_SUPPORT_RAW
		XIMAGE_FORMAT_RAW = 19,
#endif
#if XIMAGE_SUPPORT_PSD
		XIMAGE_FORMAT_PSD = 20,
#endif
		MAX_IMAGE_FORMATS =   XIMAGE_SUPPORT_BMP + XIMAGE_SUPPORT_GIF + XIMAGE_SUPPORT_JPG +
		XIMAGE_SUPPORT_PNG +  XIMAGE_SUPPORT_MNG + XIMAGE_SUPPORT_ICO +
		XIMAGE_SUPPORT_TIF +  XIMAGE_SUPPORT_TGA + XIMAGE_SUPPORT_PCX +
		XIMAGE_SUPPORT_WBMP + XIMAGE_SUPPORT_WMF +
		XIMAGE_SUPPORT_JBG +  XIMAGE_SUPPORT_JP2 + XIMAGE_SUPPORT_JPC +
		XIMAGE_SUPPORT_PGX +  XIMAGE_SUPPORT_PNM + XIMAGE_SUPPORT_RAS +
		XIMAGE_SUPPORT_SKA +  XIMAGE_SUPPORT_RAW + XIMAGE_SUPPORT_PSD + 1
	};

#endif


#if XIMAGE_SUPPORT_EXIF
#define MAX_COMMENT 255
#define MAX_SECTIONS 20
	typedef struct tag_ExifInfo {
		char  Version[5];
		char  CameraMake[32];
		char  CameraModel[40];
		char  DateTime[20];
		int   Height, Width;
		int   Orientation;
		int   IsColor;
		int   Process;
		int   FlashUsed;
		float FocalLength;
		float ExposureTime;
		float ApertureFNumber;
		float Distance;
		float CCDWidth;
		float ExposureBias;
		int   Whitebalance;
		int   MeteringMode;
		int   ExposureProgram;
		int   ISOequivalent;
		int   CompressionLevel;
		float FocalplaneXRes;
		float FocalplaneYRes;
		float FocalplaneUnits;
		float Xresolution;
		float Yresolution;
		float ResolutionUnit;
		float Brightness;
		char  Comments[MAX_COMMENT + 1];

		unsigned char * ThumbnailPointer;  /* Pointer at the thumbnail */
		unsigned ThumbnailSize;     /* Size of thumbnail. */

		bool  IsExif;
	} EXIFINFO;
#endif //XIMAGE_SUPPORT_EXIF

	typedef unsigned long DWORD;

	typedef long LONG;

	typedef unsigned short WORD;

	typedef unsigned short UINT16;
	
	typedef DWORD   COLORREF;

//#define GetRValue(rgb)      (LOBYTE(rgb))
//#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
//

#pragma pack(1)
#ifndef _WIN32
	typedef struct tagBITMAPINFOHEADER
	{
		DWORD      biSize;
		LONG       biWidth;
		LONG       biHeight;
		WORD       biPlanes;
		WORD       biBitCount;
		DWORD      biCompression;
		DWORD      biSizeImage;
		LONG       biXPelsPerMeter;
		LONG       biYPelsPerMeter;
		DWORD      biClrUsed;
		DWORD      biClrImportant;
	} BITMAPINFOHEADER;// , FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
#endif // !_WIN32
#pragma pack()


#ifndef _WB_METHOD_
#define _WB_METHOD_
	enum EWBMethod
	{
		WB_GW,//gray world algorithm
		WB_PR,//perfect reflector algorithm
		WB_DT //dynamic threshold algorithm
	};
#endif

#ifndef _WB_PARAM_
#define _WB_PARAM_
	typedef struct WhiteBalanceParam
	{
		EWBMethod method;
		int nMaxGray;
		double dRatio;

		WhiteBalanceParam()
		{
			method		= WB_GW;
			nMaxGray	= 240;
			dRatio		= 0.1;
		}
	}WBParam;
#endif

#pragma pack(1)
#ifndef _WIN32
#ifndef _RGB_QUAD_
#define _RGB_QUAD_
	typedef struct tagRGBQUAD {
		unsigned char    rgbBlue;
		unsigned char    rgbGreen;
		unsigned char    rgbRed;
		unsigned char    rgbReserved;
	} RGBQUAD;
#endif
#endif // !WIN32
#pragma pack()

#ifndef _E_DISPLAY_MODE_
#define _E_DISPLAY_MODE_
	enum LIBCORE_API EDisplayMode
	{
		DM_FULL_WINDOW = 0,
		DM_FIT_TO_WINDOW,
		DM_ACTUAL_SIZE,
		DM_FULL_SCREEN
	};
#endif

}
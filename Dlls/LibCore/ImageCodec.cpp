#include "Image.h"

#include<string>
#include<algorithm>
#include<cctype>

#if XIMAGE_SUPPORT_BMP
#include "ximagebmp.h"
#endif

#if XIMAGE_SUPPORT_PNG
#include "ximagepng.h"
#endif

#if XIMAGE_SUPPORT_JPG
#include "ximagejpg.h"
#endif


using std::string;

namespace avs
{
	////////////////////////////////////////////////////////////////////////////////
	EImageFormat xImage::getImageFormat(const int index)
	{
		int n;

		n = 0; if (index == n) return XIMAGE_FORMAT_UNKNOWN;

#if XIMAGE_SUPPORT_BMP
		n++; if (index == n) return XIMAGE_FORMAT_BMP;
#endif

#if XIMAGE_SUPPORT_GIF
		n++; if (index == n) return XIMAGE_FORMAT_GIF;
#endif

#if XIMAGE_SUPPORT_JPG
		n++; if (index == n) return XIMAGE_FORMAT_JPG;
#endif

#if XIMAGE_SUPPORT_PNG
		n++; if (index == n) return XIMAGE_FORMAT_PNG;
#endif

#if XIMAGE_SUPPORT_ICO
		n++; if (index == n) return XIMAGE_FORMAT_ICO;
#endif
#if XIMAGE_SUPPORT_TIF
		n++; if (index == n) return XIMAGE_FORMAT_TIF;
#endif
#if XIMAGE_SUPPORT_TGA
		n++; if (index == n) return XIMAGE_FORMAT_TGA;
#endif
#if XIMAGE_SUPPORT_PCX
		n++; if (index == n) return XIMAGE_FORMAT_PCX;
#endif
#if XIMAGE_SUPPORT_WBMP
		n++; if (index == n) return XIMAGE_FORMAT_WBMP;
#endif
#if XIMAGE_SUPPORT_WMF
		n++; if (index == n) return XIMAGE_FORMAT_WMF;
#endif
#if XIMAGE_SUPPORT_JP2
		n++; if (index == n) return XIMAGE_FORMAT_JP2;
#endif
#if XIMAGE_SUPPORT_JPC
		n++; if (index == n) return XIMAGE_FORMAT_JPC;
#endif
#if XIMAGE_SUPPORT_PGX
		n++; if (index == n) return XIMAGE_FORMAT_PGX;
#endif
#if XIMAGE_SUPPORT_PNM
		n++; if (index == n) return XIMAGE_FORMAT_PNM;
#endif
#if XIMAGE_SUPPORT_RAS
		n++; if (index == n) return XIMAGE_FORMAT_RAS;
#endif
#if XIMAGE_SUPPORT_JBG
		n++; if (index == n) return XIMAGE_FORMAT_JBG;
#endif
#if XIMAGE_SUPPORT_MNG
		n++; if (index == n) return XIMAGE_FORMAT_MNG;
#endif
#if XIMAGE_SUPPORT_SKA
		n++; if (index == n) return XIMAGE_FORMAT_SKA;
#endif
#if XIMAGE_SUPPORT_RAW
		n++; if (index == n) return XIMAGE_FORMAT_RAW;
#endif
#if XIMAGE_SUPPORT_PSD
		n++; if (index == n) return XIMAGE_FORMAT_PSD;
#endif

		return XIMAGE_FORMAT_UNKNOWN;
	}


	////////////////////////////////////////////////////////////////////////////////
	int xImage::getImageFormatIndex(EImageFormat fmt)
	{
		int n;

		n = 0; if (fmt == XIMAGE_FORMAT_UNKNOWN) return n;
#if XIMAGE_SUPPORT_BMP
		n++; if (fmt == XIMAGE_FORMAT_BMP) return n;
#endif
#if XIMAGE_SUPPORT_GIF
		n++; if (fmt == XIMAGE_FORMAT_GIF) return n;
#endif
#if XIMAGE_SUPPORT_JPG
		n++; if (fmt == XIMAGE_FORMAT_JPG) return n;
#endif
#if XIMAGE_SUPPORT_PNG
		n++; if (fmt == XIMAGE_FORMAT_PNG) return n;
#endif
#if XIMAGE_SUPPORT_ICO
		n++; if (fmt == XIMAGE_FORMAT_ICO) return n;
#endif
#if XIMAGE_SUPPORT_TIF
		n++; if (fmt == XIMAGE_FORMAT_TIF) return n;
#endif
#if XIMAGE_SUPPORT_TGA
		n++; if (fmt == XIMAGE_FORMAT_TGA) return n;
#endif
#if XIMAGE_SUPPORT_PCX
		n++; if (fmt == XIMAGE_FORMAT_PCX) return n;
#endif
#if XIMAGE_SUPPORT_WBMP
		n++; if (fmt == XIMAGE_FORMAT_WBMP) return n;
#endif
#if XIMAGE_SUPPORT_WMF
		n++; if (fmt == XIMAGE_FORMAT_WMF) return n;
#endif
#if XIMAGE_SUPPORT_JP2
		n++; if (fmt == XIMAGE_FORMAT_JP2) return n;
#endif
#if XIMAGE_SUPPORT_JPC
		n++; if (fmt == XIMAGE_FORMAT_JPC) return n;
#endif
#if XIMAGE_SUPPORT_PGX
		n++; if (fmt == XIMAGE_FORMAT_PGX) return n;
#endif
#if XIMAGE_SUPPORT_PNM
		n++; if (fmt == XIMAGE_FORMAT_PNM) return n;
#endif
#if XIMAGE_SUPPORT_RAS
		n++; if (fmt == XIMAGE_FORMAT_RAS) return n;
#endif
#if XIMAGE_SUPPORT_JBG
		n++; if (fmt == XIMAGE_FORMAT_JBG) return n;
#endif
#if XIMAGE_SUPPORT_MNG
		n++; if (fmt == XIMAGE_FORMAT_MNG) return n;
#endif
#if XIMAGE_SUPPORT_SKA
		n++; if (fmt == XIMAGE_FORMAT_SKA) return n;
#endif
#if XIMAGE_SUPPORT_RAW
		n++; if (fmt == XIMAGE_FORMAT_RAW) return n;
#endif
#if XIMAGE_SUPPORT_PSD
		n++; if (fmt == XIMAGE_FORMAT_PSD) return n;
#endif

		return 0;
	}


	EImageFormat xImage::getImageFormat(const string &strFileFullName)
	{
		size_t pos = strFileFullName.rfind('.');
		string strExt = strFileFullName.substr(pos+1);
		std::transform(strExt.begin(), strExt.end(), strExt.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (strExt == "bmp")
		{
#if XIMAGE_SUPPORT_BMP
			return XIMAGE_FORMAT_BMP;
#endif
		}

		if (strExt == "gif")
		{
#if XIMAGE_SUPPORT_GIF
			return XIMAGE_FORMAT_GIF;
#endif
		}

		if (strExt == "jpg")
		{
#if XIMAGE_SUPPORT_JPG
			return XIMAGE_FORMAT_JPG;
#endif
		}

		if (strExt == "png")
		{
#if XIMAGE_SUPPORT_PNG
			return XIMAGE_FORMAT_PNG;
#endif
		}

		if (strExt == "ico")
		{
#if XIMAGE_SUPPORT_ICO
		return XIMAGE_FORMAT_ICO;
#endif
		}

		if (strExt == "tif")
		{
#if XIMAGE_SUPPORT_TIF
			return XIMAGE_FORMAT_TIF;
#endif
		}

		if (strExt == "tga")
		{
#if XIMAGE_SUPPORT_TGA
			return XIMAGE_FORMAT_TGA;
#endif
		}

		if (strExt == "pcx")
		{
#if XIMAGE_SUPPORT_PCX
			return XIMAGE_FORMAT_PCX;
#endif
		}

		if (strExt == "wbmp")
		{
#if XIMAGE_SUPPORT_WBMP
			return XIMAGE_FORMAT_WBMP;
#endif
		}

		if (strExt == "wmf")
		{
#if XIMAGE_SUPPORT_WMF
			return XIMAGE_FORMAT_WMF;
#endif
		}

		if (strExt == "jp2")
		{
#if XIMAGE_SUPPORT_JP2
			return XIMAGE_FORMAT_JP2;
#endif
		}

		if (strExt == "jpc")
		{
#if XIMAGE_SUPPORT_JPC
			return XIMAGE_FORMAT_JPC;
#endif
		}

		if (strExt == "pgx")
		{
#if XIMAGE_SUPPORT_PGX
			return XIMAGE_FORMAT_PGX;
#endif	
		}

		if (strExt == "pnm")
		{
#if XIMAGE_SUPPORT_PNM
			return XIMAGE_FORMAT_PNM;
#endif
		}

		if (strExt == "ras")
		{
#if XIMAGE_SUPPORT_RAS
			return XIMAGE_FORMAT_RAS;
#endif
		}

		if (strExt == "jbg")
		{
#if XIMAGE_SUPPORT_JBG
			return XIMAGE_FORMAT_JBG;
#endif	
		}

		if (strExt == "mng")
		{
#if XIMAGE_SUPPORT_MNG
			return XIMAGE_FORMAT_MNG;
#endif
		}

		if (strExt == "ska")
		{
#if XIMAGE_SUPPORT_SKA
			return XIMAGE_FORMAT_SKA;
#endif
		}

		if (strExt == "raw")
		{
#if XIMAGE_SUPPORT_RAW
			return XIMAGE_FORMAT_RAW;
#endif
		}

		if (strExt == "psd")
		{
#if XIMAGE_SUPPORT_PSD
			return XIMAGE_FORMAT_PSD;
#endif
		}

		return XIMAGE_FORMAT_UNKNOWN;
	}

	//////////////////////////////////////////////////////////////////////////////////////////
#if XIMAGE_SUPPORT_DECODE
	////////////////////////////////////////////////////////////////////////////////
	bool xImage::decode(FILE *hFile, EImageFormat fmt)
	{
		xIOFile file(hFile);
		return decode(&file, fmt);
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::decode(xFile *hFile, EImageFormat fmt)
	{
		if (hFile == nullptr) 
		{		
			return false;
		}

#if XIMAGE_SUPPORT_BMP
		if (XIMAGE_FORMAT_UNKNOWN == fmt || XIMAGE_FORMAT_BMP == fmt) 
		{
			xImageBMP bmpImg;
			if (bmpImg.decode(hFile))
			{
				copyFrom(bmpImg);

				return true;
			}
		}
#endif// XIMAGE_SUPPORT_BMP

#if XIMAGE_SUPPORT_PNG
		if (XIMAGE_FORMAT_UNKNOWN == fmt || XIMAGE_FORMAT_PNG == fmt) 
		{
			xImagePNG img;
			if (img.decode(hFile))
			{
				copyFrom(img);

				return true;
			}
		}
#endif// XIMAGE_SUPPORT_PNG

#if XIMAGE_SUPPORT_JPG
		if (XIMAGE_FORMAT_UNKNOWN == fmt || XIMAGE_FORMAT_JPG == fmt) 
		{
			xImageJPG img;
			if (img.decode(hFile))
			{
				copyFrom(img);

				return true;
			}
		}
#endif// XIMAGE_SUPPORT_JPG

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::load(const char *szImgFile)
	{
		bool bOK = false;

		FILE* hFile = nullptr;	//file handle to read the image
		if ((0 != fopen_s(&hFile, szImgFile, "rb")) || hFile == nullptr)
		{
			return false;
		}

		EImageFormat fmt = getImageFormat(szImgFile);

		bOK = decode(hFile, fmt);

		fclose(hFile);

		return bOK;
	}

#endif // XIMAGE_SUPPORT_DECODE
	//////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////
#if XIMAGE_SUPPORT_ENCODE
	////////////////////////////////////////////////////////////////////////////////
	bool xImage::safeForEncode(xFile *hFile)
	{
		if (nullptr == hFile) 
		{
			//strcpy(info.szLastError, CXIMAGE_ERR_NOFILE);
			return false;
		}

		if (nullptr == m_pBuffer) 
		{
			//strcpy(info.szLastError, CXIMAGE_ERR_NOIMAGE);
			return false;
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::encode(FILE *hFile, EImageFormat fmt)
	{
		xIOFile file(hFile);
		return encode(&file, fmt);
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::encode(xFile *hFile, EImageFormat fmt)
	{
		if (hFile == nullptr)
		{
			return false;
		}

#if XIMAGE_SUPPORT_BMP
		if (XIMAGE_FORMAT_UNKNOWN == fmt || XIMAGE_FORMAT_BMP == fmt)
		{
			xImageBMP bmpImg;
			copyTo(bmpImg);
			if (bmpImg.encode(hFile))
			{
				return true;
			}
		}
#endif

#if XIMAGE_SUPPORT_PNG
		if (XIMAGE_FORMAT_UNKNOWN == fmt || XIMAGE_FORMAT_PNG == fmt)
		{
			xImagePNG img;
			copyTo(img);
			if (img.encode(hFile))
			{
				return true;
			}
		}
#endif

#if XIMAGE_SUPPORT_JPG
		if (XIMAGE_FORMAT_UNKNOWN == fmt || XIMAGE_FORMAT_JPG == fmt)
		{
			xImageJPG img;
			copyTo(img);
			if (img.encode(hFile))
			{
				return true;
			}
		}
#endif

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::save(const char *szImgFile)
	{
		bool bOK = false;

		FILE* hFile = nullptr;	//file handle to read the image
		if ((0 != fopen_s(&hFile, szImgFile, "wb")) || hFile == nullptr)
		{
			return false;
		}

		EImageFormat fmt = getImageFormat(szImgFile);

		bOK = encode(hFile, fmt);

		fclose(hFile);

		return bOK;
	}

#endif // XIMAGE_SUPPORT_ENCODE
	//////////////////////////////////////////////////////////////////////////////////////////


}
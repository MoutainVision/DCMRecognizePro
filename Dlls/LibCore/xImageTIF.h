/*
 * File:	ximatif.h
 * Purpose:	TIFF Image Class Loader and Writer
 */
/* ==========================================================
 * CxImageTIF (c) 07/Aug/2001 Davide Pizzolato - www.xdp.it
 * For conditions of distribution and use, see copyright notice in ximage.h
 *
 * Special thanks to Troels Knakkergaard for new features, enhancements and bugfixes
 *
 * Special thanks to Abe <God(dot)bless(at)marihuana(dot)com> for MultiPageTIFF code.
 *
 * LibTIFF is:
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 * ==========================================================
 */

#if !defined(__ximatif_h)
#define __ximatif_h

#include "image.h"

#if XIMAGE_SUPPORT_TIF

#include "tiff/tiffio.h"

namespace avs
{
	class xImageTIF : public xImage
	{
	public:
		xImageTIF() : xImage(XIMAGE_FORMAT_TIF) 
		{
			m_tif2 = NULL; m_multipage = false; m_pages = 0; 
		}
		~xImageTIF();

		TIFF* tiffOpenEx(xFile * hFile);
		void  tiffCloseEx(TIFF* tif);

		//	bool Load(const TCHAR * imageFileName){ return CxImage::Load(imageFileName,CXIMAGE_FORMAT_TIF);}
		//	bool Save(const TCHAR * imageFileName){ return CxImage::Save(imageFileName,CXIMAGE_FORMAT_TIF);}
		bool decode(xFile * hFile);

		bool decode(FILE *hFile) 
		{ 
			xIOFile file(hFile); return decode(&file); 
		}

#if CXIMAGE_SUPPORT_ENCODE
		bool encode(xFile * hFile, bool bAppend = false);

		bool encode(xFile * hFile, xImage ** pImages, int32_t pagecount);

		bool encode(FILE *hFile, bool bAppend = false) 
		{
			xIOFile file(hFile); return encode(&file, bAppend); 
		}

		bool encode(FILE *hFile, xImage ** pImages, int32_t pagecount)
		{
			xIOFile file(hFile); return encode(&file, pImages, pagecount);
		}
#endif // CXIMAGE_SUPPORT_ENCODE

	protected:
		void TileToStrip(uint8* out, uint8* in, uint32 rows, uint32 cols, int32_t outskew, int32_t inskew);
		bool EncodeBody(TIFF *m_tif, bool multipage = false, int32_t page = 0, int32_t pagecount = 0);
		TIFF *m_tif2;
		bool m_multipage;
		int32_t  m_pages;
		void MoveBits(uint8_t* dest, uint8_t* from, int32_t count, int32_t bpp);
		void MoveBitsPal(uint8_t* dest, uint8_t*from, int32_t count, int32_t bpp, RGBQUAD* pal);
	};
}
#endif

#endif

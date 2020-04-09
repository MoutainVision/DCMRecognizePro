// xImalpha.cpp : Alpha channel functions
/* 07/08/2001 v1.00 - Davide Pizzolato - www.xdp.it
 * xImage version 7.0.2 07/Feb/2011
 */

#include "image.h"

#if XIMAGE_SUPPORT_ALPHA

namespace avs
{
	unsigned char* xImage::getAlpha() const
	{
		return m_pAlpha;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * \sa AlphaSetMax
	 */
	uint8_t xImage::alphaGetMax() const
	{
		return m_extInfo.nAlphaMax;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Sets global Alpha (opacity) value applied to the whole image,
	 * valid only for painting functions.
	 * \param nAlphaMax: can be from 0 to 255
	 */
	void xImage::alphaSetMax(uint8_t nAlphaMax)
	{
		m_extInfo.nAlphaMax = nAlphaMax;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Checks if the image has a valid alpha channel.
	 */
	bool xImage::alphaIsValid()
	{
		return m_pAlpha != 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Enables the alpha palette, so the Draw() function changes its behavior.
	 */
	void xImage::alphaPaletteEnable(bool enable)
	{
		m_extInfo.bAlphaPaletteEnabled = enable;

		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * True if the alpha palette is enabled for painting.
	 */
	bool xImage::alphaPaletteIsEnabled()
	{
		return m_extInfo.bAlphaPaletteEnabled;
	}
	
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Sets the alpha channel to full transparent. AlphaSet(0) has the same effect
	 */
	void xImage::alphaClear()
	{
		if (m_pAlpha)
		{
			memset(m_pAlpha, 0, m_bmpHead.biWidth * m_bmpHead.biHeight);
		}
		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Sets the alpha level for the whole image.
	 * \param level : from 0 (transparent) to 255 (opaque)
	 */
	void xImage::alphaSet(uint8_t level)
	{
		if (m_pAlpha)
		{
			memset(m_pAlpha, level, m_bmpHead.biWidth * m_bmpHead.biHeight);
		}
		return;
	}
	
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Allocates an empty (opaque) alpha channel.
	 */
	bool xImage::alphaCreate()
	{
		if (m_pAlpha == NULL) 
		{
			m_pAlpha = (uint8_t*)malloc(m_bmpHead.biWidth * m_bmpHead.biHeight);
			if (m_pAlpha)
			{
				memset(m_pAlpha, 255, m_bmpHead.biWidth * m_bmpHead.biHeight);
			}
		}

		return (m_pAlpha != 0);
	}

	////////////////////////////////////////////////////////////////////////////////
	void xImage::alphaDelete()
	{
		if (m_pAlpha) 
		{
			free(m_pAlpha); 
			m_pAlpha = 0; 
		}

		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	void xImage::alphaInvert()
	{
		if (m_pAlpha)
		{
			uint8_t *iSrc = m_pAlpha;
			int32_t n = m_bmpHead.biHeight * m_bmpHead.biWidth;
			for (int32_t i = 0; i < n; i++) 
			{
				*iSrc = (uint8_t)~(*(iSrc));
				iSrc++;
			}
		}

		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Imports an existing alpha channel from another image with the same width and height.
	 */
	bool xImage::alphaCopy(const xImage &from)
	{
		if (from.m_pAlpha == NULL ||
			m_bmpHead.biWidth != from.m_bmpHead.biWidth ||
			m_bmpHead.biHeight != from.m_bmpHead.biHeight)
		{
			return false;
		}

		if (m_pAlpha == NULL)
		{
			m_pAlpha = (uint8_t*)malloc(m_bmpHead.biWidth * m_bmpHead.biHeight);
		}
		
		if (m_pAlpha == NULL)
		{
			return false;
		}

		memcpy(m_pAlpha, from.m_pAlpha, m_bmpHead.biWidth * m_bmpHead.biHeight);
		
		m_extInfo.nAlphaMax = from.m_extInfo.nAlphaMax;
		
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Creates the alpha channel from a gray scale image.
	 */
	bool xImage::alphaSet(xImage &from)
	{
		if (!from.isGrayScale() ||
			m_bmpHead.biWidth != from.m_bmpHead.biWidth ||
			m_bmpHead.biHeight != from.m_bmpHead.biHeight)
		{
			return false;
		}

		if (m_pAlpha == NULL)
		{
			m_pAlpha = (uint8_t*)malloc(m_bmpHead.biWidth * m_bmpHead.biHeight);
		}

		uint8_t* src = from.m_extInfo.pImage;
		uint8_t* dst = m_pAlpha;

		if (src == NULL || dst == NULL)
		{
			return false;
		}

		for (int32_t y = 0; y < m_bmpHead.biHeight; y++)
		{
			memcpy(dst, src, m_bmpHead.biWidth);
			dst += m_bmpHead.biWidth;
			src += from.m_extInfo.dwEffWidth;
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Sets the alpha level for a single pixel
	 */
	bool xImage::alphaSet(const int32_t x, const int32_t y, const uint8_t level)
	{
		if (m_pAlpha && isInside(x, y))
		{
			m_pAlpha[x + y * m_bmpHead.biWidth] = level;

			return true;
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Gets the alpha level for a single pixel
	 */
	uint8_t xImage::alphaGet(const int32_t x, const int32_t y)
	{
		if (m_pAlpha && isInside(x, y))
		{
			return m_pAlpha[x + y * m_bmpHead.biWidth];
		}

		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Returns pointer to alpha data for pixel (x,y).
	 *
	 * \author ***bd*** 2.2004
	 */
	uint8_t* xImage::alphaGetPointer(const int32_t x, const int32_t y)
	{
		if (m_pAlpha && isInside(x, y))
		{
			return m_pAlpha + x + y * m_bmpHead.biWidth;
		}

		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Get alpha value without boundscheck (a bit faster). Pixel must be inside the image.
	 *
	 * \author ***bd*** 2.2004
	 */
	unsigned char xImage::blindAlphaGet(const int x, const int y)
	{
#ifdef _DEBUG
		if (!isInside(x, y) || (m_pAlpha == nullptr))
#if CXIMAGE_SUPPORT_EXCEPTION_HANDLING
			throw 0;
#else
			return 0;
#endif
#endif
		return m_pAlpha[x + y * m_bmpHead.biWidth];
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Resets the alpha palette
	 */
	void xImage::alphaPaletteClear()
	{
		RGBQUAD c;
		for (uint16_t ip = 0; ip < m_bmpHead.biClrUsed; ip++) 
		{
			c = getPaletteColor((uint8_t)ip);
			c.rgbReserved = 0;
			setPaletteColor((uint8_t)ip, c);
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Checks if the image has a valid alpha palette.
	 */
	bool xImage::alphaPaletteIsValid()
	{
		RGBQUAD c;
		for (uint16_t ip = 0; ip < m_bmpHead.biClrUsed; ip++) 
		{
			c = getPaletteColor((uint8_t)ip);
		
			if (c.rgbReserved != 0)
			{
				return true;
			}
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Blends the alpha channel and the alpha palette with the pixels. The result is a 24 bit image.
	 * The background color can be selected using SetTransColor().
	 */
	void xImage::alphaStrip()
	{
		bool bAlphaPaletteIsValid = alphaPaletteIsValid();
		bool bAlphaIsValid = alphaIsValid();
		if (!(bAlphaIsValid || bAlphaPaletteIsValid))
		{
			return;
		}

		RGBQUAD c;
		int32_t a, a1;
		if (m_bmpHead.biBitCount == 24) 
		{
			for (int32_t y = 0; y < m_bmpHead.biHeight; y++) 
			{
				for (int32_t x = 0; x < m_bmpHead.biWidth; x++)
				{
					c = blindGetPixelColor(x, y);
					if (bAlphaIsValid)
					{
						a = (blindAlphaGet(x, y)*m_extInfo.nAlphaMax) / 255;
					}
					else
					{
						a = m_extInfo.nAlphaMax;
					}

					a1 = 256 - a;
					c.rgbBlue	= (uint8_t)((c.rgbBlue	* a + a1 * m_extInfo.nBkgndColor.rgbBlue) >> 8);
					c.rgbGreen	= (uint8_t)((c.rgbGreen * a + a1 * m_extInfo.nBkgndColor.rgbGreen) >> 8);
					c.rgbRed	= (uint8_t)((c.rgbRed	* a + a1 * m_extInfo.nBkgndColor.rgbRed) >> 8);
					
					blindSetPixelColor(x, y, c);
				}
			}
			alphaDelete();
		}
		else 
		{
			xImage tmp(m_bmpHead.biWidth, m_bmpHead.biHeight, 24);
			if (!tmp.isValid()) 
			{
				//strcpy(m_extInfo.szLastError, tmp.GetLastError());
				return;
			}

			for (int32_t y = 0; y < m_bmpHead.biHeight; y++) 
			{
				for (int32_t x = 0; x < m_bmpHead.biWidth; x++) 
				{
					c = blindGetPixelColor(x, y);
					if (bAlphaIsValid)
					{
						a = (blindAlphaGet(x, y) * m_extInfo.nAlphaMax) / 255;
					}
					else
					{
						a = m_extInfo.nAlphaMax;
					}

					if (bAlphaPaletteIsValid)
					{
						a = (c.rgbReserved*a) / 255;
					}

					a1 = 256 - a;
					c.rgbBlue	= (uint8_t)((c.rgbBlue	* a + a1 * m_extInfo.nBkgndColor.rgbBlue) >> 8);
					c.rgbGreen	= (uint8_t)((c.rgbGreen * a + a1 * m_extInfo.nBkgndColor.rgbGreen) >> 8);
					c.rgbRed	= (uint8_t)((c.rgbRed	* a + a1 * m_extInfo.nBkgndColor.rgbRed) >> 8);
					
					tmp.blindSetPixelColor(x, y, c);
				}
			}
			transfer(tmp);
		}
		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::alphaFlip()
	{
		if (!m_pAlpha)
		{
			return false;
		}

		uint8_t *buff = (uint8_t*)malloc(m_bmpHead.biWidth);
		if (!buff)
		{
			return false;
		}

		uint8_t *iSrc, *iDst;
		iSrc = m_pAlpha + (m_bmpHead.biHeight - 1)*m_bmpHead.biWidth;
		iDst = m_pAlpha;
		for (int32_t i = 0; i < (m_bmpHead.biHeight / 2); ++i)
		{
			memcpy(buff, iSrc, m_bmpHead.biWidth);
			memcpy(iSrc, iDst, m_bmpHead.biWidth);
			memcpy(iDst, buff, m_bmpHead.biWidth);
			iSrc -= m_bmpHead.biWidth;
			iDst += m_bmpHead.biWidth;
		}

		free(buff);

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::alphaMirror()
	{
		if (!m_pAlpha)
		{
			return false;
		}
		
		uint8_t* pAlpha2 = (uint8_t*)malloc(m_bmpHead.biWidth * m_bmpHead.biHeight);
		if (!pAlpha2)
		{
			return false;
		}

		uint8_t *iSrc, *iDst;
		int32_t wdt = m_bmpHead.biWidth - 1;
		iSrc = m_pAlpha + wdt;
		iDst = pAlpha2;
		for (int32_t y = 0; y < m_bmpHead.biHeight; y++)
		{
			for (int32_t x = 0; x <= wdt; x++)
				*(iDst + x) = *(iSrc - x);

			iSrc += m_bmpHead.biWidth;
			iDst += m_bmpHead.biWidth;
		}
		free(m_pAlpha);
		m_pAlpha = pAlpha2;
		
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Exports the alpha channel in a 8bpp grayscale image.
	 */
	bool xImage::alphaSplit(xImage *dest)
	{
		if (!m_pAlpha || !dest)
		{
			return false;
		}

		xImage tmp(m_bmpHead.biWidth, m_bmpHead.biHeight, 8);
		if (!tmp.isValid())
		{
			//strcpy(m_extInfo.szLastError, tmp.GetLastError());
			return false;
		}

		uint8_t* src = m_pAlpha;
		uint8_t* dst = tmp.m_extInfo.pImage;
		for (int32_t y = 0; y < m_bmpHead.biHeight; y++)
		{
			memcpy(dst, src, m_bmpHead.biWidth);
			dst += tmp.m_extInfo.dwEffWidth;
			src += m_bmpHead.biWidth;
		}

		tmp.setGrayPalette();
		dest->transfer(tmp);

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Exports the alpha palette channel in a 8bpp grayscale image.
	 */
	bool xImage::alphaPaletteSplit(xImage *dest)
	{
		if (!alphaPaletteIsValid() || !dest)
		{
			return false;
		}

		xImage tmp(m_bmpHead.biWidth, m_bmpHead.biHeight, 8);
		if (!tmp.isValid()) 
		{
			//strcpy(m_extInfo.szLastError, tmp.GetLastError());
			return false;
		}

		for (int32_t y = 0; y < m_bmpHead.biHeight; y++) 
		{
			for (int32_t x = 0; x < m_bmpHead.biWidth; x++) 
			{
				tmp.blindSetPixelIndex(x, y, blindGetPixelColor(x, y).rgbReserved);
			}
		}

		tmp.setGrayPalette();
		dest->transfer(tmp);

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Merge in the alpha layer the transparent color mask
	 * (previously set with SetTransColor or SetTransIndex)
	 */
	bool xImage::alphaFromTransparency()
	{
		if (!isValid() || !isTransparent())
		{
			return false;
		}

		alphaCreate();

		for (int32_t y = 0; y < m_bmpHead.biHeight; y++) 
		{
			for (int32_t x = 0; x < m_bmpHead.biWidth; x++) 
			{
				if (isTransparent(x, y)) 
				{
					alphaSet(x, y, 0);
				}
			}
		}

		return true;
	}

}

////////////////////////////////////////////////////////////////////////////////
#endif //CXIMAGE_SUPPORT_ALPHA

#include "Image.h"

namespace avs
{
	bool xImage::createPalette(unsigned char nColors)
	{
		if (nullptr != m_pPalette)
		{
			delete[]m_pPalette;
			m_pPalette = nullptr;
		}

		if (0 < nColors)
		{
			if (nullptr == (m_pPalette = new RGBQUAD[nColors]))
			{
				m_bmpHead.biClrUsed = 0;
				return false;
			}
		}

		m_bmpHead.biClrUsed = nColors;
			   
		return true;
	}

	/**
	 * delete the palette
	*/
	void xImage::deletePalette()
	{
		if (nullptr != m_pPalette)
		{
			delete[]m_pPalette;
			m_pPalette = nullptr;
		}

		return;
	}


	////////////////////////////////////////////////////////////////////////////////
	unsigned xImage::getClrImportant() const
	{
		return m_bmpHead.biClrImportant;
	}

	////////////////////////////////////////////////////////////////////////////////
	void xImage::setClrImportant(unsigned nColors)
	{
		if (nColors == 0 || nColors > 256)
		{
			m_bmpHead.biClrImportant = 0;
			return;
		}

		switch (m_bmpHead.biBitCount) 
		{
		case 1:
			m_bmpHead.biClrImportant = min(nColors, 2);
			break;

		case 4:
			m_bmpHead.biClrImportant = min(nColors, 16);
			break;

		case 8:
			m_bmpHead.biClrImportant = nColors;
			break;
		}

		return;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::isGrayScale()
	{
		RGBQUAD* ppal = getPalette();

		if (nullptr == m_pBuffer || nullptr == ppal || m_bmpHead.biClrUsed == 0)
		{
			return false;
		}

		for (unsigned i = 0; i < m_bmpHead.biClrUsed; i++) 
		{
			if (ppal[i].rgbBlue != i || ppal[i].rgbGreen != i || ppal[i].rgbRed != i)
			{
				return false;
			}
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::isIndexed() const
	{
		return (m_bmpHead.biClrUsed != 0);
	}

	////////////////////////////////////////////////////////////////////////////////
	unsigned xImage::getPaletteSize() const
	{
		return (m_bmpHead.biClrUsed * sizeof(RGBQUAD));
	}
	   
	////////////////////////////////////////////////////////////////////////////////
	RGBQUAD* xImage::getPalette() const
	{
		return m_pPalette;
	}

	////////////////////////////////////////////////////////////////////////////////
	unsigned xImage::getPaletteItemCount() const
	{
		return m_bmpHead.biClrUsed;
	}

	bool xImage::hasPalette() const
	{
		return (nullptr != m_pPalette && m_bmpHead.biClrUsed > 0);
	}

	bool xImage::copyPalette(const xImage &from)
	{
		if (from.hasPalette())
		{
			if (createPalette(from.getPaletteItemCount()))
			{
				memcpy(m_pPalette, from.getPalette(), from.getPaletteSize());

				return true;
			}
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::setPalette(rgb_color *rgb, unsigned nColors)
	{
		if ((nullptr == rgb) || (m_bmpHead.biClrUsed == 0))
		{
			return false;
		}

		RGBQUAD* ppal = getPalette();
		unsigned m = min(nColors, m_bmpHead.biClrUsed);
		for (unsigned i = 0; i < m; i++) 
		{
			ppal[i].rgbRed = rgb[i].r;
			ppal[i].rgbGreen = rgb[i].g;
			ppal[i].rgbBlue = rgb[i].b;
		}
		
		m_extInfo.last_c_isvalid = false;

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::setGrayPalette()
	{
		if ((nullptr == m_pPalette) || (m_bmpHead.biClrUsed == 0))
		{
			return false;
		}

		RGBQUAD* pal = getPalette();
		for (uint32_t ni = 0; ni < m_bmpHead.biClrUsed; ni++)
		{
			pal[ni].rgbBlue = pal[ni].rgbGreen = pal[ni].rgbRed = (uint8_t)(ni*(255 / (m_bmpHead.biClrUsed - 1)));
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	void xImage::setPalette(uint32_t n, uint8_t *r, uint8_t *g, uint8_t *b)
	{
		if ((!r) || (m_pBuffer == NULL) || (m_bmpHead.biClrUsed == 0)) return;
		if (!g) g = r;
		if (!b) b = g;
		RGBQUAD* ppal = getPalette();
		uint32_t m = min(n, m_bmpHead.biClrUsed);
		for (uint32_t i = 0; i < m; i++) 
		{
			ppal[i].rgbRed = r[i];
			ppal[i].rgbGreen = g[i];
			ppal[i].rgbBlue = b[i];
		}
		m_extInfo.last_c_isvalid = false;

		return;
	}


	////////////////////////////////////////////////////////////////////////////////
	bool xImage::setPaletteColor(unsigned char idx, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
	{
		if (nullptr != m_pPalette)
		{
			RGBQUAD* iDst = m_pPalette;
			
			if (idx < m_bmpHead.biClrUsed) 
			{
				m_pPalette[idx].rgbBlue = b;
				m_pPalette[idx].rgbGreen = g;
				m_pPalette[idx].rgbRed = r;
				m_pPalette[idx].rgbReserved = alpha;
			
				m_extInfo.last_c_isvalid = false;

				return true;
			}
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::setPaletteColor(unsigned char idx, RGBQUAD c)
	{
		if (nullptr != m_pPalette)
		{
			if (idx < m_bmpHead.biClrUsed) 
			{
				m_pPalette[idx] = c;

				m_extInfo.last_c_isvalid = false;

				return true;
			}
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::setPaletteColor(unsigned char idx, COLORREF cr)
	{
		if (nullptr != m_pPalette) 
		{			
			if (idx < m_bmpHead.biClrUsed) 
			{				
				m_pPalette[idx].rgbRed		= (unsigned char)(cr&0x000000ff);
				m_pPalette[idx].rgbGreen	= (unsigned char)((cr&0x0000ff00)>>8);
				m_pPalette[idx].rgbBlue		= (unsigned char)((cr&0x00ff0000)>>16);

				m_extInfo.last_c_isvalid = false;

				return true;
			}
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	RGBQUAD xImage::getPaletteColor(unsigned char idx)
	{
		RGBQUAD rgb = { 0,0,0,0 };
		
		if (nullptr != m_pPalette) 
		{
			if (idx < m_bmpHead.biClrUsed) 
			{
				rgb = m_pPalette[idx];
			}
		}
		return rgb;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::getPaletteColor(unsigned char i, unsigned char* r, unsigned char* g, unsigned char* b)
	{
		if (nullptr != m_pPalette && i < m_bmpHead.biClrUsed) 
		{
			*r = m_pPalette[i].rgbRed;
			*g = m_pPalette[i].rgbGreen;
			*b = m_pPalette[i].rgbBlue;

			return true;
		}

		return false;
	}



	////////////////////////////////////////////////////////////////////////////////
	bool xImage::swapIndex(unsigned char idx1, unsigned char idx2)
	{
		if (nullptr == m_pPalette)
		{
			return false;
		}

		//swap the colors
		RGBQUAD tempRGB = getPaletteColor(idx1);

		setPaletteColor(idx1, getPaletteColor(idx2));

		setPaletteColor(idx2, tempRGB);

		//swap the pixels
		unsigned char idx;
		for (int y = 0; y < m_bmpHead.biHeight; y++) 
		{
			for (int x = 0; x < m_bmpHead.biWidth; x++) 
			{
				idx = blindGetPixelIndex(x, y);
				if (idx == idx1) blindSetPixelIndex(x, y, idx2);
				if (idx == idx2) blindSetPixelIndex(x, y, idx1);
			}
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::swapRGB2BGR()
	{
		if (nullptr == m_pBuffer)
		{
			return false;
		}

		if (m_bmpHead.biClrUsed > 0) 
		{
			RGBQUAD* ppal = getPalette();
			if (nullptr == ppal)
			{
				return false;
			}

			unsigned char b;
			for (unsigned short a = 0; a < m_bmpHead.biClrUsed; a++) 
			{
				b = ppal[a].rgbBlue; 
				ppal[a].rgbBlue = ppal[a].rgbRed; 
				ppal[a].rgbRed = b;
			}
		}
		else
		{
			for (int y = 0; y < m_bmpHead.biHeight; y++) 
			{
				if (!RGBtoBGR(getScanLine(y), 3 * m_bmpHead.biWidth))
				{
					return false;
				}
			}
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::RGBtoBGR(unsigned char *buffer, unsigned length)
	{
		if (buffer && (m_bmpHead.biClrUsed == 0)) 
		{
			length = min(length, m_extInfo.dwEffWidth);
			length = min(length, 3 * m_bmpHead.biWidth);

			unsigned char temp;
			for (unsigned i = 0; i < length; i += 3) 
			{
				temp = buffer[i]; 
				buffer[i] = buffer[i + 2]; 
				buffer[i + 2] = temp;
			}

			return true;
		}

		return false;
	}


	////////////////////////////////////////////////////////////////////////////////
	unsigned char xImage::blindGetPixelIndex(const int x, const int y)
	{
		if ((nullptr == m_pBuffer) || (m_bmpHead.biClrUsed == 0) || !isInside(x, y))
		{
			return 0;
		}

		if (m_bmpHead.biBitCount == 8)
		{
			return m_extInfo.pImage[y*m_extInfo.dwEffWidth + x];
		}
		else 
		{
			unsigned char pos;
			unsigned char iDst = m_extInfo.pImage[y*m_extInfo.dwEffWidth + (x*m_bmpHead.biBitCount >> 3)];
		
			if (m_bmpHead.biBitCount == 4) 
			{
				pos = (unsigned char)(4 * (1 - x % 2));
				iDst &= (0x0F << pos);
				return (unsigned char)(iDst >> pos);
			}
			else if (m_bmpHead.biBitCount == 1) 
			{
				pos = (unsigned char)(7 - x % 8);
				iDst &= (0x01 << pos);
				return (unsigned char)(iDst >> pos);
			}
		}

		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	void xImage::blindSetPixelIndex(int x, int y, unsigned char i)
	{
		if ((nullptr == m_pBuffer) || (m_bmpHead.biClrUsed == 0) ||
			(x < 0) || (y < 0) || (x >= m_bmpHead.biWidth) || (y >= m_bmpHead.biHeight))
		{
			return;
		}

		if (m_bmpHead.biBitCount == 8) 
		{
			m_extInfo.pImage[y*m_extInfo.dwEffWidth + x] = i;

			return;
		}
		else 
		{
			unsigned char pos;
			unsigned char* iDst = m_extInfo.pImage + y * m_extInfo.dwEffWidth + (x*m_bmpHead.biBitCount >> 3);
			if (m_bmpHead.biBitCount == 4) 
			{
				pos = (unsigned char)(4 * (1 - x % 2));
				*iDst &= ~(0x0F << pos);
				*iDst |= ((i & 0x0F) << pos);
				return;
			}
			else if (m_bmpHead.biBitCount == 1) 
			{
				pos = (unsigned char)(7 - x % 8);
				*iDst &= ~(0x01 << pos);
				*iDst |= ((i & 0x01) << pos);
				return;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Returns the palette index of the specified pixel.
	 */
	unsigned char xImage::getPixelIndex(int x, int y)
	{
		if ((m_pBuffer == NULL) || (m_bmpHead.biClrUsed == 0))
		{
			return 0;
		}

		if ((x < 0) || (y < 0) || (x >= m_bmpHead.biWidth) || (y >= m_bmpHead.biHeight))
		{
			if (m_extInfo.nBkgndIndex >= 0)
			{
				return (unsigned char)m_extInfo.nBkgndIndex;
			}
			else
			{
				return *m_extInfo.pImage;
			}
		}
		if (m_bmpHead.biBitCount == 8) 
		{
			return m_extInfo.pImage[y*m_extInfo.dwEffWidth + x];
		}
		else 
		{
			uint8_t pos;
			uint8_t iDst = m_extInfo.pImage[y*m_extInfo.dwEffWidth + (x*m_bmpHead.biBitCount >> 3)];
			if (m_bmpHead.biBitCount == 4) 
			{
				pos = (uint8_t)(4 * (1 - x % 2));
				iDst &= (0x0F << pos);
				return (uint8_t)(iDst >> pos);
			}
			else if (m_bmpHead.biBitCount == 1) 
			{
				pos = (uint8_t)(7 - x % 8);
				iDst &= (0x01 << pos);
				return (uint8_t)(iDst >> pos);
			}
		}
		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * This is (a bit) faster version of GetPixelColor.
	 * It tests bounds only in debug mode (_DEBUG defined).
	 *
	 * It is an error to request out-of-borders pixel with this method.
	 * In DEBUG mode an exception will be thrown, and data will be violated in non-DEBUG mode.
	 * \author ***bd*** 2.2004
	 */
	RGBQUAD xImage::blindGetPixelColor(const int x, const int y, bool bGetAlpha)
	{
		RGBQUAD rgb;

#ifdef _DEBUG
		if ((m_pBuffer == NULL) || !isInside(x, y))
#if CXIMAGE_SUPPORT_EXCEPTION_HANDLING
			throw 0;
#else
		{rgb.rgbReserved = 0; return rgb; }
#endif
#endif

		if (m_bmpHead.biClrUsed)
		{
			rgb = getPaletteColor(blindGetPixelIndex(x, y));
		}
		else 
		{
			uint8_t* iDst = m_extInfo.pImage + y * m_extInfo.dwEffWidth + x * 3;
			rgb.rgbBlue = *iDst++;
			rgb.rgbGreen = *iDst++;
			rgb.rgbRed = *iDst;
			rgb.rgbReserved = 0; //needed for images without alpha layer
		}
#if XIMAGE_SUPPORT_ALPHA
		if (m_pAlpha && bGetAlpha) rgb.rgbReserved = blindAlphaGet(x, y);
#else
		rgb.rgbReserved = 0;
#endif //CXIMAGE_SUPPORT_ALPHA

		return rgb;
	}

	////////////////////////////////////////////////////////////////////////////////
	RGBQUAD xImage::getPixelColor(int x, int y, bool bGetAlpha)
	{
		//	RGBQUAD rgb={0,0,0,0};
		RGBQUAD rgb = m_extInfo.nBkgndColor; //<mpwolski>
		if ((m_pBuffer == NULL) || 
			(0 > x) || (x >= m_bmpHead.biWidth) ||
			(0 > y) || (y >= m_bmpHead.biHeight))
		{
			if (m_extInfo.nBkgndIndex >= 0) 
			{
				if (m_bmpHead.biBitCount < 24)
				{
					return getPaletteColor((uint8_t)m_extInfo.nBkgndIndex);
				}
				else
				{
					return m_extInfo.nBkgndColor;
				}
			}
			else if (nullptr == m_pBuffer)
			{
				return getPixelColor(0, 0);
			}

			return rgb;
		}

		if (m_bmpHead.biClrUsed) 
		{
			rgb = getPaletteColor(blindGetPixelIndex(x, y));
		}
		else 
		{
			uint8_t* iDst = m_extInfo.pImage + y * m_extInfo.dwEffWidth + x * 3;
			rgb.rgbBlue = *iDst++;
			rgb.rgbGreen = *iDst++;
			rgb.rgbRed = *iDst;
		}

#if XIMAGE_SUPPORT_ALPHA
		if (m_pAlpha && bGetAlpha)
		{
			rgb.rgbReserved = blindAlphaGet(x, y);
		}
#else
		rgb.rgbReserved = 0;
#endif //XIMAGE_SUPPORT_ALPHA

		return rgb;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::isTransparent(int x, int y)
	{
		if (nullptr == m_pBuffer)
		{
			return false;
		}

		if (m_extInfo.nBkgndIndex >= 0)
		{
			if (m_bmpHead.biClrUsed) 
			{
				if (getPixelIndex(x, y) == m_extInfo.nBkgndIndex)
				{
					return true;
				}
			}
			else 
			{
				RGBQUAD ct = m_extInfo.nBkgndColor;
				RGBQUAD c = getPixelColor(x, y, false);
				if (*(int*)&c == *(int*)&ct)
				{
					return true;
				}
			}
		}

#if XIMAGE_SUPPORT_ALPHA
		if (m_pAlpha)
		{
			return alphaGet(x, y) == 0;
		}
#endif

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Returns pointer to pixel. Currently implemented only for truecolor images.
	 *
	 * \param  x,y - coordinates
	 *
	 * \return pointer to first byte of pixel data
	 *
	 * \author ***bd*** 2.2004
	 */
	void* xImage::blindGetPixelPointer(const int x, const int y)
	{
#ifdef _DEBUG
		if ((m_pBuffer == NULL) || !isInside(x, y))
#if CXIMAGE_SUPPORT_EXCEPTION_HANDLING
			throw 0;
#else
			return 0;
#endif
#endif
		if (!isIndexed())
			return m_extInfo.pImage + y * m_extInfo.dwEffWidth + x * 3;
		else
			return 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Returns the best palette index that matches a specified color.
	 */
	unsigned char xImage::getNearestIndex(RGBQUAD c)
	{
		if ((m_pBuffer == NULL) || (m_bmpHead.biClrUsed == 0)) return 0;

		// <RJ> check matching with the previous result
		if (m_extInfo.last_c_isvalid && (*(int32_t*)&m_extInfo.last_c == *(int32_t*)&c))
		{
			return m_extInfo.last_c_index;
		}
		m_extInfo.last_c = c;
		m_extInfo.last_c_isvalid = true;

		//uint8_t* iDst = (uint8_t*)(pDib)+sizeof(BITMAPINFOHEADER);
		uint8_t* iDst = (unsigned char*)m_pPalette;

		int32_t distance = 200000;
		int32_t i, j = 0;
		int32_t k, l;
		int32_t m = (int32_t)(m_bmpHead.biClrImportant == 0 ? m_bmpHead.biClrUsed : m_bmpHead.biClrImportant);
		for (i = 0, l = 0; i < m; i++, l += sizeof(RGBQUAD)) 
		{
			k = (iDst[l] - c.rgbBlue)*(iDst[l] - c.rgbBlue) +
				(iDst[l + 1] - c.rgbGreen)*(iDst[l + 1] - c.rgbGreen) +
				(iDst[l + 2] - c.rgbRed)*(iDst[l + 2] - c.rgbRed);
			//		k = abs(iDst[l]-c.rgbBlue)+abs(iDst[l+1]-c.rgbGreen)+abs(iDst[l+2]-c.rgbRed);
			if (k == 0) 
			{
				j = i;
				break;
			}
			if (k < distance) 
			{
				distance = k;
				j = i;
			}
		}
		m_extInfo.last_c_index = (uint8_t)j;

		return (uint8_t)j;
	}

	////////////////////////////////////////////////////////////////////////////////
	void xImage::blindSetPixelColor(int x, int y, RGBQUAD c, bool bSetAlpha)
	{
#ifdef _DEBUG
		if ((m_pBuffer == NULL) || (x < 0) || (y < 0) ||
			(x >= m_bmpHead.biWidth) || (y >= m_bmpHead.biHeight))
#if CXIMAGE_SUPPORT_EXCEPTION_HANDLING
			throw 0;
#else
			return;
#endif
#endif
		if (m_bmpHead.biClrUsed)
		{
			blindSetPixelIndex(x, y, getNearestIndex(c));
		}
		else 
		{
			uint8_t* iDst = m_extInfo.pImage + y * m_extInfo.dwEffWidth + x * 3;
			*iDst++ = c.rgbBlue;
			*iDst++ = c.rgbGreen;
			*iDst = c.rgbRed;
		}

#if XIMAGE_SUPPORT_ALPHA
		if (bSetAlpha)
		{
			alphaSet(x, y, c.rgbReserved);
		}
#endif //CXIMAGE_SUPPORT_ALPHA
	}
}
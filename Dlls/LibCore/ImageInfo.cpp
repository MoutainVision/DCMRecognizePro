#include "Image.h"

namespace avs
{
	////////////////////////////////////////////////////////////////////////////////
/**
 * \sa SetJpegQuality, GetJpegQualityF
 * \author [DP]; changes [Stefan Schürmans]
 */
	uint8_t xImage::getJpegQuality() const
	{
		return (uint8_t)(m_extInfo.fQuality + 0.5f);
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * \sa SetJpegQuality, GetJpegQuality
	 * \author [Stefan Schürmans]
	 */
	float xImage::getJpegQualityF() const
	{
		return m_extInfo.fQuality;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * quality level for JPEG and JPEG2000
	 * \param q: can be from 0 to 100
	 * \author [DP]; changes [Stefan Schürmans]
	 */
	void xImage::setJpegQuality(uint8_t q)
	{
		m_extInfo.fQuality = (float)q;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * quality level for JPEG and JPEG2000
	 * necessary for JPEG2000 when quality is between 0.0 and 1.0
	 * \param q: can be from 0.0 to 100.0
	 * \author [Stefan Schürmans]
	 */
	void xImage::setJpegQualityF(float q) 
	{
		if (q > 0) m_extInfo.fQuality = q;
		else  m_extInfo.fQuality = 0.0f;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * \sa SetJpegScale
	 */
	uint8_t xImage::getJpegScale() const
	{
		return m_extInfo.nJpegScale;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * scaling down during JPEG decoding valid numbers are 1, 2, 4, 8
	 * \author [ignacio]
	 */
	void xImage::setJpegScale(uint8_t q)
	{
		m_extInfo.nJpegScale = q;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * \return Resolution for TIFF, JPEG, PNG and BMP formats.
	 */
	int xImage::getXDPI() const
	{
		return m_extInfo.xDPI;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * \return Resolution for TIFF, JPEG, PNG and BMP formats.
	 */
	int xImage::getYDPI() const
	{
		return m_extInfo.yDPI;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Set resolution for TIFF, JPEG, PNG and BMP formats.
	 */
	void xImage::setXDPI(int dpi)
	{
		if (dpi <= 0) dpi = XIMAGE_DEFAULT_DPI;
		m_extInfo.xDPI = dpi;
		m_bmpHead.biXPelsPerMeter = (int)floor(dpi * 10000.0 / 254.0 + 0.5);
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Set resolution for TIFF, JPEG, PNG and BMP formats.
	 */
	void xImage::setYDPI(int dpi)
	{
		if (dpi <= 0) dpi = XIMAGE_DEFAULT_DPI;
		m_extInfo.yDPI = dpi;
		m_bmpHead.biYPelsPerMeter = (int)floor(dpi * 10000.0 / 254.0 + 0.5);
	}

	////////////////////////////////////////////////////////////////////////////////
/**
 * \return 2, 16, 256; 0 for RGB images.
 */
	unsigned xImage::getColorCount() const
	{
		return m_bmpHead.biClrUsed;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * \return the color used for transparency, and/or for background color
	 */
	RGBQUAD	xImage::getTransColor()
	{
		if (m_bmpHead.biBitCount < 24 && m_extInfo.nBkgndIndex >= 0)
		{
			return getPaletteColor((unsigned char)m_extInfo.nBkgndIndex);
		}

		return m_extInfo.nBkgndColor;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Sets the color used for transparency with 24 bpp images.
	 * You must call SetTransIndex(0) to enable the effect, SetTransIndex(-1) to disable it.
	 */
	void xImage::setTransColor(RGBQUAD rgb)
	{
		rgb.rgbReserved = 0;
		m_extInfo.nBkgndColor = rgb;
	}
	
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Gets the index used for transparency. Returns -1 for no transparancy.
	 */
	int xImage::getTransIndex() const
	{
		return m_extInfo.nBkgndIndex;
	}

	////////////////////////////////////////////////////////////////////////////////
	/**
	 * Sets the index used for transparency with 1, 4 and 8 bpp images. Set to -1 to remove the effect.
	 */
	void xImage::setTransIndex(int idx)
	{
		if (idx < (int)m_bmpHead.biClrUsed)
			m_extInfo.nBkgndIndex = idx;
		else
			m_extInfo.nBkgndIndex = 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	bool xImage::isTransparent() const
	{
		return m_extInfo.nBkgndIndex >= 0; // <vho>
	}

}
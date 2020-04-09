#include "xImageBMP.h"

namespace avs
{
	xImageBMP::xImageBMP()
	{
	}


	xImageBMP::~xImageBMP()
	{
	}

	bool xImageBMP::decode(xFile * hFile)
	{
		if (hFile == nullptr)
		{
			return false;
		}

		BITMAPFILEHEADER bfh;
		int n1 = sizeof(bfh.bfOffBits);
		int n2 = sizeof(bfh.bfSize);
		int n3 = sizeof(bfh.bfType);
		int n4 = sizeof(bfh.bfReserved1);
		int n5 = sizeof(bfh.bfReserved2);
		int n6 = min(14,sizeof(bfh));

		int off = hFile->tell(); //<CSC>
		if (hFile->read(&bfh, sizeof(bfh), 1) == 0)
		{
			//"Not a BMP";
			return false;
		}

		if (bfh.bfType != 0x4d42)
		{
			return false;
		}

		BITMAPINFOHEADER bmpInfoHeader;
		if (hFile->read(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1) == 0)
		{
			return false;
		}

		if (bmpInfoHeader.biCompression != 0)//0 == BI_RGB
		{
			return false;
		}

		int nBpp = bmpInfoHeader.biBitCount;
		int nW = bmpInfoHeader.biWidth;
		int nH = bmpInfoHeader.biHeight;
		if (nH < 0)
			nH = -nH;
		
		int nP;
		size_t imgSize;
		unsigned char *pImgBuffer = nullptr;

		int nColorNum = bmpInfoHeader.biClrUsed;

		bool bTopDownDib = bmpInfoHeader.biHeight < 0; //<Flanders> check if it's a top-down bitmap
		if (bTopDownDib) bmpInfoHeader.biHeight = -bmpInfoHeader.biHeight;

		int nPaletteItem;

		switch (nBpp)
		{
		case 32:
			nP = ((((nBpp * nW) + 31) / 32) * 4);
			imgSize = nP * nH;
			pImgBuffer = new unsigned char[imgSize];
			if (hFile->read(pImgBuffer, imgSize, 1) == 0)  // read in the pixels
			{
				delete[]pImgBuffer;
				return false;
			}

			m_pBuffer = pImgBuffer;
			m_nWidth = nW;
			m_nHeight = nH;
			m_nBpp = nBpp;
			m_nPitch = nP;
			m_nImgSize = imgSize;
			m_bAligned = true;
			m_pixFmt = PIXEL_FORMAT_BGRU;
			m_byrFmt = BAYER_FORMAT_NONE;

			return true;

		case 24:
			nP = ((((nBpp * nW) + 31) / 32) * 4);
			imgSize = nP * nH;
			pImgBuffer = new unsigned char[imgSize];
			if (hFile->read(pImgBuffer, imgSize, 1) == 0)  // read in the pixels
			{
				delete[]pImgBuffer;
				return false;
			}

			m_pBuffer = pImgBuffer;
			m_nWidth = nW;
			m_nHeight = nH;
			m_nBpp = nBpp;
			m_nPitch = nP;
			m_nImgSize = imgSize;
			m_bAligned = true;
			m_pixFmt = PIXEL_FORMAT_BGR;
			m_byrFmt = BAYER_FORMAT_NONE;
			
			return true;

		case 16:
		{

			nP = ((((nBpp * nW) + 31) / 32) * 4);
			imgSize = nP * nH;
			pImgBuffer = new unsigned char[imgSize];
			if (hFile->read(pImgBuffer, imgSize, 1) == 0)  // read in the pixels
			{
				delete[]pImgBuffer;
				return false;
			}

			m_nHeight = nH;
			m_nBpp = 24;
			m_nWidth = nW;
			m_nPitch = ((((m_nBpp * nW) + 31) / 32) * 4);
			m_nImgSize = m_nHeight * m_nPitch;
			m_pBuffer = new unsigned char[m_nImgSize];
			m_bAligned = true;
			m_pixFmt = PIXEL_FORMAT_BGR;
			m_byrFmt = BAYER_FORMAT_NONE;

			unsigned char *pPixRow = pImgBuffer;
			unsigned char *pImg = m_pBuffer;
			for (unsigned y = 0; y < nH; y++)
			{
				for (unsigned x = 0; x < nW; x++)
				{
					unsigned short nPix = pPixRow[2 * x] + pPixRow[2 * x + 1] << 8;
					//unsigned char ucBlue = nPix & 0x1F;
					//unsigned char ucGreen = (nPix & 0x3E0) >> 5;
					//unsigned char ucRed = (nPix & 0x7C00) >> 10;
					*(pImg + 3 * x)		=  nPix & 0x1F;
					*(pImg + 3 * x + 1) = (nPix & 0x3E0) >> 5;
					*(pImg + 3 * x + 2) = (nPix & 0x7C00) >> 10;
				}

				pPixRow += nP;
				pImg += m_nPitch;
			}

			delete[]pImgBuffer;
		}

			return true;

		case 8:
			if (nColorNum == 0)
			{
				nColorNum = 1 << bmpInfoHeader.biBitCount;
			}

			nPaletteItem = (bfh.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)) / sizeof(RGBQUAD);

			if (nColorNum == nPaletteItem)
			{
				RGBQUAD *pPalette = new RGBQUAD[nColorNum];
				if (hFile->read(pPalette, nColorNum * sizeof(RGBQUAD), 1) == 0)
				{
					delete[]pPalette;
					return false;
				}

				bool bMonoImage = true;
				for (unsigned k = 0; k < nColorNum; k++)
				{
					if (pPalette[k].rgbBlue != pPalette[k].rgbGreen || 
						pPalette[k].rgbGreen != pPalette[k].rgbRed)
					{
						bMonoImage = false;
						break;
					}
				}

				nP = ((((nBpp * nW) + 31) / 32) * 4);
				imgSize = nH * nP;
				unsigned char *pBuf = new unsigned char[imgSize];
				if (hFile->read(pBuf, imgSize, 1) == 0)  // read in the pixels
				{
					delete[]pBuf;
					return false;
				}

				if (bMonoImage)
				{
					m_nBpp = 8;
					m_nWidth = nW;
					m_nHeight = nH;
					m_nPitch = nP;
					m_nImgSize = imgSize;
					m_pBuffer = pBuf;
					m_bAligned = true;
					m_pixFmt = PIXEL_FORMAT_MONO8;
					m_byrFmt = BAYER_FORMAT_NONE;
				}
				else
				{
					m_nHeight = nH;
					m_nBpp = 24;
					m_nWidth = nW;
					m_nPitch = ((((m_nBpp * nW) + 31) / 32) * 4);
					m_nImgSize = m_nHeight * m_nPitch;
					m_pBuffer = new unsigned char[m_nImgSize];
					m_bAligned = true;
					m_pixFmt = PIXEL_FORMAT_BGR;
					m_byrFmt = BAYER_FORMAT_NONE;

					unsigned char *pDst = m_pBuffer;
					unsigned char *pSrc = pBuf;
					for (unsigned y = 0; y < nH; y++)
					{
						for (unsigned x = 0; x < nW; x++)
						{
							pDst[3 * x]		= pPalette[pSrc[x]].rgbBlue;
							pDst[3 * x + 1] = pPalette[pSrc[x]].rgbGreen;
							pDst[3 * x + 2] = pPalette[pSrc[x]].rgbRed;
						}

						pSrc += nP;
						pDst += m_nPitch;
					}

					delete[]pBuf;
				}

				return true;
			}

		default:
			break;
		}

		return false;
	}

	bool xImageBMP::encode(xFile * hFile)
	{
		BITMAPFILEHEADER	hdr;

		hdr.bfType = 0x4d42;   // 'BM' WINDOWS_BITMAP_SIGNATURE
		hdr.bfReserved1 = hdr.bfReserved2 = 0;

		if (m_nBpp == 8)
		{
			int nColorNum = 256;
			RGBQUAD *pPalette = new RGBQUAD[nColorNum];
			for (int k = 0; k < nColorNum; k++)
			{
				pPalette[k].rgbBlue = pPalette[k].rgbGreen = pPalette[k].rgbRed = k;
			}

			hdr.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
				+ nColorNum * sizeof(RGBQUAD) + m_nImgSize;

			hdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
				+ nColorNum * sizeof(RGBQUAD);

			hFile->write(&hdr, min(14, sizeof(BITMAPFILEHEADER)), 1);

			BITMAPINFOHEADER bih;
			bih.biBitCount = 8;
			bih.biClrImportant = 0;
			bih.biClrUsed = nColorNum;
			bih.biCompression = 0;//BI_RGB
			bih.biHeight = m_nHeight;
			bih.biWidth = m_nWidth;
			bih.biPlanes = 1;
			bih.biSize = sizeof(BITMAPINFOHEADER);
			bih.biSizeImage = m_nImgSize;
			bih.biXPelsPerMeter = 0;
			bih.biYPelsPerMeter = 0;

			hFile->write(&bih, sizeof(BITMAPINFOHEADER), 1);

			hFile->write(pPalette, nColorNum * sizeof(RGBQUAD), 1);

			hFile->write(m_pBuffer, m_nImgSize, 1);

			return true;
		}
		else if (m_nBpp == 24 || m_nBpp == 32)
		{
			hdr.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_nImgSize;

			hdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

			hFile->write(&hdr, min(14, sizeof(BITMAPFILEHEADER)), 1);

			BITMAPINFOHEADER bih;
			bih.biBitCount = m_nBpp;
			bih.biClrImportant = 0;
			bih.biClrUsed = 0;
			bih.biCompression = 0;//BI_RGB
			bih.biHeight = m_nHeight;
			bih.biWidth = m_nWidth;
			bih.biPlanes = 1;
			bih.biSize = sizeof(BITMAPINFOHEADER);
			bih.biSizeImage = m_nImgSize;
			bih.biXPelsPerMeter = 0;
			bih.biYPelsPerMeter = 0;

			hFile->write(&bih, sizeof(BITMAPINFOHEADER), 1);

			hFile->write(m_pBuffer, m_nImgSize, 1);

			return true;
		}

		return false;
	}
}


#include "Image.h"

#if XIMAGE_SUPPORT_WINDOWS

namespace avs
{

	inline unsigned calcImagePitch(unsigned nW, unsigned nBpp)
	{
		return ((nW * nBpp + 31) & ~31) >> 3;
	}

	bool convert8BitTo24Bit(unsigned char *pImg24, int nW, int nH, int nP24, unsigned char *pImg8, int nP8)
	{
		if (NULL == pImg24 || nW < 0 || nH < 0 || NULL == pImg8)
		{
			return false;
		}

		if (nP24 != calcImagePitch(nW, 24) || nP8 != calcImagePitch(nW, 8))
		{
			return false;
		}


		//int ypos = 0;
		//int pos8 = 0;
		//int pos24 = 0;
		for (int y = 0; y < nH; y++)
		{
			//pos24 = ypos;

			unsigned char *pPixRow24 = pImg24;
			unsigned char *pPixRow8  = pImg8;

			for (int x = 0; x < nW; x++)
			{
				//*(pImg24 + pos24) = *(pImg24 + pos24 + 1) = *(pImg24 + pos24 + 2) = *(pImg8 + pos8 + x);

				//pos24 += 3;

				*(pPixRow24++) = *pPixRow8;
				*(pPixRow24++) = *pPixRow8;
				*(pPixRow24++) = *(pPixRow8++);
			}

			pImg24 += nP24;
			pImg8  += nP8;

			//ypos += nP24;
			//pos8 += nP8;
		}

		return true;
	}

	bool xImage::showImage(unsigned char *pImage, int nWidth, int nHeight, int nBitsPerPixel,
		HWND hDisplayWnd, EDisplayMode dm, int nDispOffsetX, int nDispOffsetY)
	{
		if (NULL == pImage || nWidth < 0 || nHeight < 0 || nBitsPerPixel < 8 || NULL == hDisplayWnd)
		{
			return false;
		}

		RECT rect;
		GetWindowRect(hDisplayWnd, &rect);
		HDC hDC = GetDC(hDisplayWnd);
		if (hDC == NULL)
		{
			return false;
		}

		unsigned char *pImg = pImage;
		int nW = nWidth;
		int nH = nHeight;
		int nBpp = nBitsPerPixel;

		if (nBpp == 8)
		{
			nBpp = 24;
			int nP0 = calcImagePitch(nW, nBitsPerPixel);
			int nP1 = calcImagePitch(nW, nBpp);
			pImg = new unsigned char[nH*nP1];

			convert8BitTo24Bit(pImg, nW, nH, nP1, pImage, nP0);
		}

		BITMAPINFO bfi;
		ZeroMemory(&bfi, sizeof(BITMAPINFO));
		bfi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bfi.bmiHeader.biCompression = BI_RGB;
		bfi.bmiHeader.biPlanes = 1;
		bfi.bmiHeader.biSizeImage = 0;
		bfi.bmiHeader.biBitCount = nBpp;
		bfi.bmiHeader.biWidth = nW;
		bfi.bmiHeader.biHeight = -nH;


		int xs, ys, w, h;
		xs = 0;
		ys = 0;
		w = nW;
		h = nH;

		switch (dm)
		{
		case DM_FIT_TO_WINDOW:
		{
			int nX = 0;
			int nY = 0;
			int nWidth = 0;
			int nHeight = 0;

			double dRatioW = (double)(rect.right - rect.left) / (double)nW;
			double dRatioH = (double)(rect.bottom - rect.top) / (double)nH;
			double dRat = dRatioW > dRatioH ? dRatioH : dRatioW;

			nWidth = dRat * nW;
			nHeight = dRat * nH;
			nX = dRatioW > dRatioH ? ((rect.right - rect.left) - nWidth) / 2 : 0;
			nY = dRatioW > dRatioH ? 0 : ((rect.bottom - rect.top) - nHeight) / 2;
			SetStretchBltMode(hDC, STRETCH_DELETESCANS);
			StretchDIBits(hDC, nX, nY, nWidth, nHeight, xs, ys, w, h, pImg, &bfi, DIB_RGB_COLORS, SRCCOPY);
			break;
		}

		case DM_ACTUAL_SIZE:
		{
			int xs = nDispOffsetX, ys = h - 1 - nDispOffsetY - (rect.bottom - rect.top);

			SetDIBitsToDevice(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, xs, ys, 0, h, pImg, &bfi, DIB_RGB_COLORS);
			break;
		}

		case DM_FULL_WINDOW:
		default:
		{
			SetStretchBltMode(hDC, STRETCH_DELETESCANS);
			StretchDIBits(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, xs, ys, w, h, pImg, &bfi, DIB_RGB_COLORS, SRCCOPY);
			break;
		}
		}

		ReleaseDC(hDisplayWnd, hDC);

		if (pImg != pImage)
		{
			delete[]pImg;
			pImg = NULL;
		}

		return true;
	}

	void xImage::display(HWND hWnd, EDisplayMode eDispMode, int nDispOffX, int nDispOffY)
	{
		xImage::showImage(m_pBuffer, m_nWidth, m_nHeight, m_nBpp, hWnd, eDispMode, nDispOffX, nDispOffY);
		//show(m_hWndDisplay, m_dispMode);

		return;
	}

}


#endif // XIMAGE_SUPPORT_WINDOWS

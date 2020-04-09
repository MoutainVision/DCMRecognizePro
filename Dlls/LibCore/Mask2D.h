#pragma once

#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include<cstring>

namespace avs
{

#ifndef _MASK2D_
#define _MASK2D_
	struct LIBCORE_API Mask2D
	{
		unsigned char *pData;
		int w, h;

		Mask2D()
			: pData(nullptr)
			, w(0)
			, h(0)
		{
		}

		Mask2D(int cx, int cy)
			: w(cx)
			, h(cy)
		{
			pData = new unsigned char[cx*cy];
		}

		Mask2D(unsigned char *pMask, int cx, int cy)
			: w(cx)
			, h(cy)
		{
			pData = new unsigned char[cx*cy];
			memcpy(pData, pMask, cx*cy * sizeof(unsigned char));
		}

		void create(int cx, int cy)
		{
			if (nullptr != pData)
			{
				delete[]pData;
				pData = nullptr;
			}

			w = cx;
			h = cy;
			pData = new unsigned char[cx*cy];

			return;
		}

		void create(int cx, int cy, unsigned char *pMask)
		{
			if (nullptr != pData)
			{
				delete[]pData;
				pData = nullptr;
			}

			w = cx;
			h = cy;
			pData = new unsigned char[cx*cy];
			memcpy(pData, pMask, cx*cy * sizeof(unsigned char));

			return;
		}

		void create(int cx, int cy, bool *pMask)
		{
			if (nullptr != pData)
			{
				delete[]pData;
				pData = nullptr;
			}

			w = cx;
			h = cy;
			pData = new unsigned char[cx*cy];
			int n = cx * cy;
			for (int i = 0; i < n; i++)
				pData[i] = pMask[i] ? 255 : 0;

			return;
		}

		Mask2D& operator=(const Mask2D &rhs)
		{
			//identity test
			if (this == &rhs)
			{
				return *this;
			}

			if (nullptr != pData)
			{
				delete[]pData;
				pData = nullptr;

				w = h = 0;
			}

			if (rhs.w > 0 && rhs.h > 0)
			{
				w = rhs.w;
				h = rhs.h;
				pData = new unsigned char[w*h];
				memcpy(pData, rhs.pData, w * h * sizeof(unsigned char));
			}

			return *this;
		}

		unsigned char* data()
		{
			return pData;
		}

		bool copy(Mask2D &srcMask)
		{
			if (srcMask.empty())
				return false;

			if (nullptr != pData)
			{
				delete[]pData;
			}

			w = srcMask.w;
			h = srcMask.h;
			pData = new unsigned char[w*h];
			memcpy(pData, srcMask.pData, w*h * sizeof(unsigned char));

			return true;
		}

		bool empty()
		{
			return (nullptr == pData || 0 >= w || 0 >= h);
		}

		~Mask2D()
		{
			if (nullptr != pData)
			{
				delete[]pData;
				pData = nullptr;
				w = h = 0;
			}
		}
	};
#endif

}
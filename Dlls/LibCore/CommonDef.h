#pragma once


#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include<cmath>
#include<cstring>

/**
*@brief marco for turning RGB to Grayscale
*/
#ifndef RGB2GRAY
#define RGB2GRAY(r,g,b) (((b)*117 + (g)*601 + (r)*306) >> 10)
#endif

#ifndef PI
#define PI 3.1415926
#endif

#ifndef EPSILON
#define EPSILON	1.0e-8
#endif

#ifndef _MAX_
#define _MAX_
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef _MIN_
#define _MIN_
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

namespace avs
{

#ifndef _DATA_ELEMENT_INT_
#define _DATA_ELEMENT_INT_
	struct LIBCORE_API IntegerDataElement
	{
		int	val;
		int key;
	};
#endif

#ifndef _DATA_ELEMENT_DOUBLE_
#define _DATA_ELEMENT_DOUBLE_
	struct LIBCORE_API DoubleDataElement
	{
		double val;
		int    key;
	};
#endif

#ifndef _DATA_ELEMENT_UINT_
#define _DATA_ELEMENT_UINT_
	struct UIntDataElement
	{
		size_t  val;
		size_t	key;
	};
#endif

#ifndef _POINT_2I_
#define _POINT_2I_
	typedef struct LIBCORE_API Point2I
	{
		int x, y;

		Point2I()
			: x(0)
			, y(0)
		{
		}

		Point2I(int xx, int yy)
			: x(xx)
			, y(yy)
		{
		}
	}IPoint, ImagePoint, PixPos;
#endif

	//#ifndef _I_POINT_
	//#define _I_POINT_
	//typedef Point2I IPoint;
	//#endif
	//
	//#ifndef _IMAGE_POINT_
	//#define _IMAGE_POINT_
	//typedef Point2I ImagePoint;
	//#endif
	//
	//#ifndef _PIX_POS_
	//#define _PIX_POS_
	//typedef Point2I PixPos;
	//#endif

#ifndef _OFFSET_2I_
#define _OFFSET_2I_
	struct LIBCORE_API Offset2I
	{
		int dx, dy;

		Offset2I()
			: dx(0)
			, dy(0)
		{
		}

		Offset2I(int xx, int yy)
			: dx(xx)
			, dy(yy)
		{
		}
	};
#endif

#ifndef _POINT_2F_
#define _POINT_2F_
	struct LIBCORE_API Point2F
	{
		double x, y;

		Point2F()
			: x(0.0)
			, y(0.0)
		{
		}

		Point2F(double xx, double yy)
			: x(xx)
			, y(yy)
		{
		}
	};
#endif


#ifndef _VEC_2F_
#define _VEC_2F_
	struct LIBCORE_API Vec2F
	{
		double nx, ny;

		Vec2F()
			: nx(0.0)
			, ny(1.0)
		{
		}

		Vec2F(double tx, double ty)
			: nx(tx)
			, ny(ty)
		{
		}

		Vec2F(Point2F ps, Point2F pe)
			: nx(pe.x - ps.x)
			, ny(pe.y - ps.y)
		{
		}

		double norm()
		{
			double fx = fabs(nx);
			double fy = fabs(ny);

			if (fx > fy)
			{
				return fx * sqrt(1.0 + (fy / fx)*(fy / fx));
			}
			else if (fx < fy)
			{
				return fy * sqrt(1.0 + (fx / fy)*(fx / fy));
			}
			else
			{
				return 0.0;
			}
		}

		bool valid()
		{
			return fabs(nx) > 0.0 || fabs(ny) > 0.0;
		}

		bool normalize()
		{
			if (valid())
			{
				double d = norm();
				nx /= d;
				ny /= d;

				return true;
			}

			return false;
		}
	};
#endif

	#ifndef _POINT_3F_
	#define _POINT_3F_
	struct LIBCORE_API Point3F
	{
		double x, y, z;

		Point3F()
			: x(0.0)
			, y(0.0)
			, z(0.0)
		{
		}

		Point3F(double xx, double yy, double zz)
			: x(xx)
			, y(yy)
			, z(zz)
		{
		}
	};
	#endif

	#ifndef _SIZE_2I_
	#define _SIZE_2I_
	struct LIBCORE_API Size2I
	{
		int cx, cy;

		Size2I()
			: cx(0)
			, cy(0)
		{
		}

		Size2I(int w, int h)
			: cx(w)
			, cy(h)
		{
		}
	};
	#endif


	#ifndef _SIZE_2F_
	#define _SIZE_2F_
	struct LIBCORE_API Size2F
	{
		double cx, cy;

		Size2F()
			: cx(0.0)
			, cy(0.0)
		{
		}

		Size2F(double w, double h)
			: cx(w)
			, cy(h)
		{
		}
	};
	#endif



	#ifndef _RECT_2I_
	#define _RECT_2I_
	struct LIBCORE_API Rect2I
	{
		int xs, xe;
		int ys, ye;

		Rect2I()
			: xs(0)
			, xe(0)
			, ys(0)
			, ye(0)
		{
		}

		Rect2I(Point2I centre, int rx, int ry = -1)
			: xs(centre.x - rx)
			, xe(centre.x + rx)
			, ys((ry == -1) ? (centre.y - rx) : (centre.y - ry))
			, ye((ry == -1) ? (centre.y + rx) : (centre.y + ry))
		{
		}

		Rect2I(Point2I ps, Size2I size)
			: xs(ps.x)
			, xe(ps.x+size.cx-1)
			, ys(ps.y)
			, ye(ps.y+size.cy-1)
		{
		}

		Rect2I(int xxs, int xxe, int yys, int yye)
			: xs(xxs)
			, xe(xxe)
			, ys(yys)
			, ye(yye)
		{
		}

		/**
		*@brief		Get the overlapping region with another rectangle
		*@param r	[in] the other rectangle
		*@return	the overlapping region represented by Rect2I
		*@note -
		*@remarks -
		*/
		Rect2I overlap(const Rect2I &r)
		{
			return Rect2I(max(xs, r.xs), min(xe, r.xe), max(ys, r.ys), min(ye, r.ye));
		}

		Rect2I overlap(const Rect2I &r) const
		{
			return Rect2I(max(xs, r.xs), min(xe, r.xe), max(ys, r.ys), min(ye, r.ye));
		}

		bool equalTo(const Rect2I &r)
		{
			return (r.xs == xs && r.xe == xe && r.ys == ys && r.ye == ye);
		}

		bool inclose(Rect2I &r)
		{
			return overlap(r).equalTo(r);
		}

		bool inclose(const Rect2I &r) const
		{
			return overlap(r).equalTo(r);
		}

		bool inclose(Point2I pt)
		{
			return (xs <= pt.x && pt.x <= xe && ys <= pt.y && pt.y <= ye);
		}

		bool inclose(const Point2I &pt) const
		{
			return (xs <= pt.x && pt.x <= xe && ys <= pt.y && pt.y <= ye);
		}

		int width()
		{
			return xe - xs + 1;
		}

		int width() const
		{
			return xe - xs + 1;
		}

		int height()
		{
			return ye - ys + 1;
		}

		int height() const
		{
			return ye - ys + 1;
		}

		Size2I size()
		{
			return Size2I(xe - xs + 1, ye - ys + 1);
		}

		long long area()
		{
			return (long long)(xe - xs + 1) * (ye - ys + 1);
		}

		bool positive()
		{
			return (xe > xs && ye > ys);
		}

		bool semi_positive()
		{
			return (xe >= xs && ye >= ys);
		}

		Rect2I translate(int tx, int ty)
		{
			return Rect2I(xs - tx, xe - tx, ys - ty, ye - ty);
		}

		void translate_self(int tx, int ty)
		{
			xs -= tx;
			xe -= tx;
			ys -= ty;
			ye -= ty;

			return;
		}
	};
	#endif

	#ifndef _IMAGE_RECT_
	#define _IMAGE_RECT_
	typedef Rect2I ImageRect;
	#endif


	#ifndef _IMAGE_ROI_
	#define _IMAGE_ROI_
	typedef Rect2I ImageROI;
	#endif


	#ifndef _IMAGE_AOI_
	#define _IMAGE_AOI_
	typedef Rect2I ImageAOI;
	#endif


#ifndef _WND_RECT_
#define _WND_RECT_
	struct LIBCORE_API WndRect
	{
		long left, right, top, bottom;
		long width, height;

		WndRect()
			: left(0)
			, right(0)
			, top(0)
			, bottom(0)
			, width(0)
			, height(0)
		{
		}

		WndRect(long l, long r, long t, long b)
			: left(l)
			, right(r)
			, top(t)
			, bottom(b)
			, width(r - l)
			, height(b - t)
		{
		}
	};
#endif


	#ifndef _LINE_SEGMENT_
	#define _LINE_SEGMENT_
	struct LIBCORE_API LineSegment
	{
		Point2F ptStart;//starting point
		Point2F ptEnd;//ending point

		LineSegment()
		{
			ptStart.x = ptStart.y = 0.0;
			ptEnd.x = ptEnd.y = 1.0;
		}

		LineSegment(double xs, double ys, double xe, double ye)
		{
			ptStart.x = xs;
			ptStart.y = ys;
			ptEnd.x = xe;
			ptEnd.y = ye;
		}

		LineSegment(Point2F ps, Point2F pe)
			: ptStart(ps)
			, ptEnd(pe)
		{
		}

		double length()
		{
			return sqrt((ptStart.x - ptEnd.x)*(ptStart.x - ptEnd.x) +
				(ptStart.y - ptEnd.y)*(ptStart.y - ptEnd.y));
		}

		bool valid()
		{
			return fabs(ptStart.x - ptEnd.x) > 0.0 || fabs(ptStart.y - ptEnd.y) > 0.0;
		}

		Vec2F direction()
		{
			return Vec2F(ptStart, ptEnd);
		}
	};
	#endif

	#ifndef _RAY_
	#define _RAY_
	struct LIBCORE_API Ray
	{
		Point2F pt; //starting point
		Vec2F   dir; //direction

		Ray()
		{
			dir.nx = 0.0;
			dir.ny = 1.0;
		}

		Ray(double x0, double y0, double tx, double ty)
		{
			pt.x = x0;
			pt.y = y0;

			dir.nx = tx;
			dir.ny = ty;

			dir.normalize();
		}

		Ray(Point2F point, Vec2F vec)
			: pt(point)
		{
			dir = vec;
			dir.normalize();
		}

		Ray(LineSegment s)
		{
			pt = s.ptStart;

			dir = s.direction();

			dir.normalize();
		}

		bool isValid()
		{
			return dir.valid();
		}
	};
	#endif

	//! type of morphological operation
#ifndef _E_MORPH_TYPE_
#define _E_MORPH_TYPE_
	enum LIBCORE_API EMorphType
	{
		MORPH_TYPE_ERODE = 0,	//!< see cv::erode
		MORPH_TYPE_DILATE = 1,	//!< see cv::dilate
		MORPH_TYPE_OPEN = 2,	//!< an opening operation
								//!< \f[\texttt{dst} = \mathrm{open} ( \texttt{src} , \texttt{element} )= \mathrm{dilate} ( \mathrm{erode} ( \texttt{src} , \texttt{element} ))\f]
		MORPH_TYPE_CLOSE = 3,	//!< a closing operation
								//!< \f[\texttt{dst} = \mathrm{close} ( \texttt{src} , \texttt{element} )= \mathrm{erode} ( \mathrm{dilate} ( \texttt{src} , \texttt{element} ))\f]
		MORPH_TYPE_GRADIENT = 4,//!< a morphological gradient
								//!< \f[\texttt{dst} = \mathrm{morph\_grad} ( \texttt{src} , \texttt{element} )= \mathrm{dilate} ( \texttt{src} , \texttt{element} )- \mathrm{erode} ( \texttt{src} , \texttt{element} )\f]
		MORPH_TYPE_TOPHAT = 5,	//!< "top hat"
								//!< \f[\texttt{dst} = \mathrm{tophat} ( \texttt{src} , \texttt{element} )= \texttt{src} - \mathrm{open} ( \texttt{src} , \texttt{element} )\f]
		MORPH_TYPE_BOTTOMHAT = 6 //!< "black hat"
								//!< \f[\texttt{dst} = \mathrm{blackhat} ( \texttt{src} , \texttt{element} )= \mathrm{close} ( \texttt{src} , \texttt{element} )- \texttt{src}\f]
	};
#endif // !_E_MORPH_TYPE_

	//! shape of the structuring element
#ifndef _E_MORPH_SHAPE_
#define _E_MORPH_SHAPE_
	enum LIBCORE_API EMorphShape
	{
		MORPH_SHAPE_RECT = 0,	//!< a rectangular structuring element:  \f[E_{ij}=1\f]

		MORPH_SHAPE_CROSS = 1,	//!< a cross-shaped structuring element:
								//!< \f[E_{ij} =  \fork{1}{if i=\texttt{anchor.y} or j=\texttt{anchor.x}}{0}{otherwise}\f]
		MORPH_SHAPE_ELLIPSE = 2	//!< an elliptic structuring element, that is, a filled ellipse inscribed
								//!< into the rectangle Rect(0, 0, esize.width, 0.esize.height)
	};
#endif

	//! structuring element for morphological transform
#ifndef _STRUCTURING_ELEMENT_
#define _STRUCTURING_ELEMENT_
	struct LIBCORE_API StructuringElement
	{
		unsigned char *pKernel;
		Size2I szKernel;

		StructuringElement(EMorphShape shape = MORPH_SHAPE_CROSS, Size2I sz = Size2I(3, 3))
		{
			pKernel = nullptr;
			szKernel.cx = szKernel.cy = 0;

			switch (shape)
			{
			case MORPH_SHAPE_CROSS:
				if (sz.cx > 0 && sz.cy > 0  && nullptr != (pKernel = new unsigned char[sz.cx*sz.cy]))
				{
					memset(pKernel, 0, sz.cx*sz.cy * sizeof(unsigned char));
					
					for (int i = 0; i < sz.cy; i++)
					{
						pKernel[i * sz.cx + sz.cx / 2] = 255;
					}
					
					for (int j = 0; j < sz.cx; j++)
					{
						pKernel[sz.cy / 2 * sz.cx + j] = 255;
					}

					szKernel = sz;
				}
				break;

			case MORPH_SHAPE_RECT:
				if (sz.cx > 0 && sz.cy > 0 && nullptr != (pKernel = new unsigned char[sz.cx*sz.cy]))
				{
					memset(pKernel, 255, sz.cx*sz.cy * sizeof(unsigned char));

					szKernel = sz;
				}
				break;

			case MORPH_SHAPE_ELLIPSE:
				if (sz.cx > 0 && sz.cy > 0 && nullptr != (pKernel = new unsigned char[sz.cx*sz.cy]))
				{
					memset(pKernel, 255, sz.cx*sz.cy * sizeof(unsigned char));

					double xc = sz.cx / 2.0;
					double yc = sz.cy / 2.0;
					for (int y = 0; y < sz.cy; y++)
					{
						for (int x = 0; x < sz.cx; x++)
						{
							double dx = (x - xc) / sz.cx;
							double dy = (y - yc) / sz.cy;
							if (dx * dx + dy * dy > 1)
							{
								pKernel[y*sz.cx + x] = 0;
							}
						}
					}
					szKernel = sz;
				}
				break;

			default:
				break;
			}
		}

		bool isValid()
		{
			return (nullptr != pKernel && szKernel.cx > 0 && szKernel.cy > 0);
		}

		~StructuringElement()
		{
			if (nullptr != pKernel)
			{
				delete[]pKernel;
				pKernel = nullptr;
			}
		}
	};
#endif // !_STRUCTURING_ELEMENT_
}

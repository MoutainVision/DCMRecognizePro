#pragma once


#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include "CommonDef.h"
#include<vector>

using std::vector;

namespace avs
{

#ifndef _AFFINE_TRANSFORM_
#define _AFFINE_TRANSFORM_
	typedef struct LIBCORE_API AffineTransform
	{
		//Affine is comprised of Rotation, Translation, Shear, Scale, Flip
		double a11, a12, a21, a22;
		double t1, t2;

		AffineTransform()
			: a11(1.0)
			, a12(0.0)
			, a21(0.0)
			, a22(1.0)
			, t1(0.0)
			, t2(0.0)
		{
		}

		AffineTransform(double b11, double b12, double b21, double b22, double tx, double ty)
			: a11(b11)
			, a12(b12)
			, a21(b21)
			, a22(b22)
			, t1(tx)
			, t2(ty)
		{
		}
	}Affine;
#endif

	LIBCORE_API bool calcAffine(Point2F *pObjPt, Point2F *pImgPt, int nPt, Affine &a);
	
	LIBCORE_API bool calcInverseAffine(Affine &a_inv, Affine &a);

	LIBCORE_API bool calcAffine(Point2F *pObjPt, Point2F *pImgPt, int nPt, Affine &a, Affine &a_inv);

	LIBCORE_API Point2F applyAffine(const Affine &a, Point2F ptObj);
	   
	/**
	*@brief get the intersection of two line segments
	*@param P1		[in] start point of first line segment
	*@param P2		[in] end point of first line segment
	*@param Q1		[in] start point of second line segment
	*@param Q2		[in] end point of second line segment
	*@param x0		[out] x coordinate of the intersection
	*@param y0		[out] y coordinate of the intersection
	*@return true if there is an intersection between the input line segments, else return false
	*@note -
	*@remarks -
	*/
	LIBCORE_API bool calcLineSegIntersection(double &dInterX, double &dInterY, Point2F P1, Point2F P2, Point2F Q1, Point2F Q2);


	typedef vector<Point2I> IPolygon;

#ifndef _E_POINT_TO_POLYGON_
#define _E_POINT_TO_POLYGON_
	enum LIBCORE_API EPointToPolygon
	{
		POINT_OUT_POLYGON = -1,
		POINT_IN_POLYGON,
		POINT_ON_POLYGON
	};
#endif

	LIBCORE_API bool point2Polygon(IPolygon &p, Point2I pt, EPointToPolygon &relation);


}
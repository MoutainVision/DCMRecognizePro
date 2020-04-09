#include "Geometry.h"

namespace avs
{


	bool calcAffine(Point2F *pObjPt, Point2F *pImgPt, int nPt, Affine &a)
	{
		if (nPt < 3)
			return false;

		double *pDox = new double[nPt - 1];
		double *pDoy = new double[nPt - 1];
		double *pDix = new double[nPt - 1];
		double *pDiy = new double[nPt - 1];

		double p11 = 0.0, p12 = 0.0, p21 = 0.0, p22 = 0.0;
		double q11 = 0.0, q12 = 0.0, q21 = 0.0, q22 = 0.0;
		double ave_xo = pObjPt[0].x, ave_yo = pObjPt[0].y;
		double ave_xi = pImgPt[0].x, ave_yi = pImgPt[0].y;
		for (int i = 0; i < nPt - 1; i++)
		{
			pDox[i] = pObjPt[i + 1].x - pObjPt[i].x;
			pDoy[i] = pObjPt[i + 1].y - pObjPt[i].y;

			ave_xo += pObjPt[i + 1].x;
			ave_yo += pObjPt[i + 1].y;

			p11 += pDox[i] * pDox[i];
			p12 += pDox[i] * pDoy[i];
			p21 += pDoy[i] * pDox[i];
			p22 += pDoy[i] * pDoy[i];

			pDix[i] = pImgPt[i + 1].x - pImgPt[i].x;
			pDiy[i] = pImgPt[i + 1].y - pImgPt[i].y;

			ave_xi += pImgPt[i + 1].x;
			ave_yi += pImgPt[i + 1].y;

			q11 += pDix[i] * pDox[i];
			q12 += pDix[i] * pDoy[i];
			q21 += pDiy[i] * pDox[i];
			q22 += pDiy[i] * pDoy[i];
		}


		ave_xo /= nPt;
		ave_yo /= nPt;

		ave_xi /= nPt;
		ave_yi /= nPt;

		double det = p11 * p22 - p12 * p21;
		if (fabs(det) < EPSILON)
		{
			delete[]pDox;
			delete[]pDoy;
			delete[]pDix;
			delete[]pDiy;

			return false;
		}

		//the inverse of 2nd order matrix: [p11 p12; p21 p22]
		double c11 =  p22 / det;
		double c12 = -p12 / det;
		double c21 = -p21 / det;
		double c22 =  p11 / det;

		a.a11 = q11 * c11 + q12 * c21;
		a.a12 = q11 * c12 + q12 * c22;
		a.a21 = q21 * c11 + q22 * c21;
		a.a22 = q21 * c12 + q22 * c22;

		a.t1 = ave_xi - (a.a11 * ave_xo + a.a12 * ave_yo);
		a.t2 = ave_yi - (a.a21 * ave_xo + a.a22 * ave_yo);

		delete[]pDox;
		delete[]pDoy;
		delete[]pDix;
		delete[]pDiy;

		return true;
	}

	bool calcInverseAffine(Affine &a_inv, Affine &a)
	{
		double det = a.a11 * a.a22 - a.a12 * a.a21;
		if (fabs(det) < EPSILON)
		{
			return false;
		}

		a_inv.a11 =  a.a22 / det;
		a_inv.a12 = -a.a12 / det;
		a_inv.a21 = -a.a21 / det;
		a_inv.a22 =  a.a11 / det;

		a_inv.t1 = -(a_inv.a11 * a.t1 + a_inv.a12 * a.t2);
		a_inv.t2 = -(a_inv.a21 * a.t1 + a_inv.a22 * a.t2);

		return true;
	}

	bool calcAffine(Point2F *pObjPt, Point2F *pImgPt, int nPt, Affine &a, Affine &a_inv)
	{		
		return calcAffine(pObjPt, pImgPt, nPt, a) && calcInverseAffine(a_inv, a);
	}

	Point2F applyAffine(const Affine &a, Point2F pt)
	{
		Point2F pt1;
		pt1.x = a.a11 * pt.x + a.a12 * pt.y + a.t1;
		pt1.y = a.a21 * pt.x + a.a22 * pt.y + a.t2;

		return pt1;
	}


	bool calcLineSegIntersection(double &dInterX, double &dInterY, Point2F P1, Point2F P2, Point2F Q1, Point2F Q2)
	{
		double xminp = min(P1.x, P2.x);
		double xmaxp = max(P1.x, P2.x);
		double yminp = min(P1.y, P2.y);
		double ymaxp = max(P1.y, P2.y);


		double xminq = min(Q1.x, Q2.x);
		double xmaxq = max(Q1.x, Q2.x);
		double yminq = min(Q1.y, Q2.y);
		double ymaxq = max(Q1.y, Q2.y);

		double xmin = max(xminp, xminq);
		double xmax = min(xmaxp, xmaxq);
		double ymin = max(yminp, yminq);
		double ymax = min(ymaxp, ymaxq);

		if (xmin > xmax || ymin > ymax)
		{
			//no intersection
			return false;
		}

		double dxp = P2.x - P1.x;
		double dyp = P2.y - P1.y;
		double dxq = Q2.x - Q1.x;
		double dyq = Q2.y - Q1.y;

		if (fabs(dyp) < EPSILON)
		{//P1P2 is a horizontal line segment

			if (fabs(dyq) < EPSILON)
			{//Q1Q2 is a horizontal line segment
				return false;
			}
			else
			{
				dInterX = (dyq*Q1.x - dxq * Q1.y + dxq * P1.y) / dyq;
				dInterY = P1.y;
				if (dInterX > xminp && dInterX < xmaxp)
				{
					return true;
				}
			}
		}
		else
		{
			if (fabs(dyq) < EPSILON)
			{//Q1Q2 is a horizontal line segment
				dInterX = (dyp*P1.x - dxp * P1.y + dxp * Q1.y) / dyp;
				dInterY = Q1.y;
				if (dInterX > xminq && dInterX < xmaxq)
				{
					return true;
				}
			}
			else
			{
				double det = dxp * dyq - dyp * dxq;
				if (fabs(det) < EPSILON)
				{//P1P2 and Q1Q2 are parallel line segments
					return false;
				}
				else
				{
					double a11 = dyp, a12 = -dxp;
					double a21 = dyq, a22 = -dxq;
					double b1 = dyp * P1.x - dxp * P1.y;
					double b2 = dyq * Q1.x - dxq * Q1.y;

					dInterX = (a22 * b1 - a12 * b2) / det;
					dInterY = (a11 * b2 - a21 * b1) / det;

					if ((dInterX > xminq && dInterX < xmaxq) && (dInterX > xminp && dInterX < xmaxp))
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	//calc the pos relationship of the given point to the polygon
	//return -1: out of the polygon
	//return  0: on the polygon
	//return  1: in the polygon
	int point2Polygon(Point2I pts[], int nPt, Point2I pt)
	{
		//calc the outer rectangle
		long left, right, top, bottom;
		left = pts[0].x;
		right = pts[0].x;
		top = pts[0].y;
		bottom = pts[0].y;
		for (int i = 1; i < nPt; i++)
		{
			if (pts[i].x < left)
				left = pts[i].x;
			if (pts[i].x > right)
				right = pts[i].x;
			if (pts[i].y < bottom)
				bottom = pts[i].y;
			if (pts[i].y > top)
				top = pts[i].y;
		}

		if (pt.x < left || pt.x > right || pt.y < bottom || pt.y > top)
		{
			//the point is out of the polygon
			return -1;
		}
		else
		{
			//number of intersection
			int nIntersection = 0;

			const double eps = 1.0e-8;

			for (int i = 0; i < nPt; i++)//for each edge
			{
				long x1 = pts[i].x;
				long y1 = pts[i].y;
				long x2, y2;
				if (i < nPt - 1)
				{
					x2 = pts[i + 1].x;
					y2 = pts[i + 1].y;
				}
				else
				{
					x2 = pts[0].x;
					y2 = pts[0].y;
				}

				long maxx = x1 > x2 ? x1 : x2;
				long maxy = y1 > y2 ? y1 : y2;
				long minx = x1 < x2 ? x1 : x2;
				long miny = y1 < y2 ? y1 : y2;

				if (pt.x > maxx || pt.y > maxy || pt.y < miny)
				{
					//no intersection with the edge
					continue;
				}

				if (maxy == miny)
				{
					if (pt.x >= minx && pt.x <= maxx)
					{
						//the point is on the polygon
						return 0;
					}
					else
					{
						//ignor the horizontal edge, no counting for intersection
						continue;
					}
				}
				else
				{
					double x0 = x1 + (double)(pt.y - y1) * (x1 - x2) / (y1 - y2);
					if (fabs(x0 - pt.x) < eps)
					{
						//the point is on the polygon
						return 0;
					}
					else
					{
						if (x0 < pt.x)
						{
							//no intersection with the edge
							continue;
						}
						else
						{
							if (pt.y == miny)
							{
								//intersection with the lower endpoint, ignored. no counting
								continue;
							}
							else
							{
								nIntersection++;
							}
						}
					}
				}
			}

			if (nIntersection % 2 == 0)
			{
				//the point is out of the polygon
				return -1;
			}
			else
			{
				//the point is in the polygon
				return 1;
			}
		}
	}

	bool point2Polygon(IPolygon &p, Point2I pt, EPointToPolygon &relation)
	{
		if (p.size() <= 2)
			return false;

		relation = (EPointToPolygon)point2Polygon((Point2I*)p.data(), p.size(), pt);

		return true;
	}

}
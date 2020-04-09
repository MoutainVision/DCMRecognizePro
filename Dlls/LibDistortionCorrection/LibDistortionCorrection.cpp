#include "LibDistortionCorrection.h"

#include<cmath>

namespace avs
{

	bool calcDivisionModel(double &x0, double &y0, double &lambda, 
							double xc0, double yc0, double r0, 
							double xc1, double yc1, double r1, 
							double xc2, double yc2, double r2)
	{
		double e[3], f[3], g[3];
		e[0] = -2.0*xc0; f[0] = -2.0*yc0; g[0] = xc0 * xc0 + yc0 * yc0 - r0 * r0;
		e[1] = -2.0*xc1; f[1] = -2.0*yc1; g[1] = xc1 * xc1 + yc1 * yc1 - r1 * r1;
		e[2] = -2.0*xc2; f[2] = -2.0*yc2; g[2] = xc2 * xc2 + yc2 * yc2 - r2 * r2;

		double a11 = e[0] - e[1];
		double a12 = f[0] - f[1];
		double a21 = e[0] - e[2];
		double a22 = f[0] - f[2];
		double b1 = g[1] - g[0];
		double b2 = g[2] - g[0];

		x0 = (b1 * a22 - b2 * a12) / (a11 * a22 - a12 * a21);
		y0 = (b1 - a11 * x0) / a12;

		lambda = 1.0 / (x0 * x0 + y0 * y0 + e[0] * x0 + f[0] * y0 + g[0]);

		return true;
	}

	bool calcDivisionModel(double &x0, double &y0, double &lambda, double xc[3], double yc[3], double r[3])
	{
		return calcDivisionModel(x0, y0, lambda, xc[0], yc[0], r[0], xc[1], yc[1], r[1], xc[2], yc[2], r[2]);
	}


	bool calcDivisionModel(division_model &dm, double xc[3], double yc[3], double r[3])
	{
		return calcDivisionModel(dm.x0, dm.y0, dm.lambda, xc, yc, r);
	}


	bool calcDivisionModel(division_model &dm,	
							double xc0, double yc0, double r0,
							double xc1, double yc1, double r1,	
							double xc2, double yc2, double r2)
	{
		return calcDivisionModel(dm.x0, dm.y0, dm.lambda, xc0, yc0, r0, xc1, yc1, r1, xc2, yc2, r2);
	}

	void getUndistortedPoint(double &xu, double &yu, division_model &dm, double xd, double yd)
	{
		double rd2 = (xd - dm.x0) * (xd - dm.x0) + (yd - dm.y0) * (yd - dm.y0);
		double d = (1 + dm.lambda * rd2);
		xu = dm.x0 + (xd - dm.x0) / d;
		yu = dm.y0 + (yd - dm.y0) / d;

		return;
	}


	bool getDistortedPoint(double &xd, double &yd, double &rd, division_model &dm, double xu, double yu)
	{
		double ru = sqrt((xu - dm.x0)*(xu - dm.x0) + (yu - dm.y0)*(yu - dm.y0));
		
		if (ru < 1.0e-10)
		{
			xd = xu;
			yd = yu;

			rd = ru;

			return true;
		}

		double a = 1.0, b = -1.0 / dm.lambda / ru, c = 1.0 / dm.lambda;
		double delta = b * b - 4 * a * c;
		if (delta > 0.0)
		{
			if (dm.lambda > 0.0)
				rd = (-b - sqrt(delta)) / 2;
				//rd = (-b - sqrt(delta)) / 2 / a;
			else
				rd = (-b + sqrt(delta)) / 2;
				//rd = (-b + sqrt(delta)) / 2 / a;

			xd = dm.x0 + rd / ru * (xu - dm.x0);
			yd = dm.y0 + rd / ru * (yu - dm.y0);

			return true;
		}

		return false;
	}



	bool createDistortionMap(distortion_pair *&pDP, double &mind, double &maxd, 
							bool bOutputDistMap, unsigned char *&pDistMap, unsigned &nPd, 
							unsigned nW, unsigned nH, division_model &dm)
	{
		if (nW <= 1 || nH <= 1)
		{
			return false;
		}

		if (nullptr != pDP)
			delete[]pDP;
		pDP = new distortion_pair[nW*nH];

		//calculate the size of undistorted image
		double minxu = 1.0e16, maxxu = -1.0e16;
		double minyu = 1.0e16, maxyu = -1.0e16;

		//bottom edge
		unsigned yd = 0;
		for (unsigned xd = 0; xd < nW; xd++)
		{
			double xu = 0.0;
			double yu = 0.0;
			getUndistortedPoint(xu, yu, dm, xd, yd);

			if (xu < minxu) minxu = xu;
			if (xu > maxxu) maxxu = xu;
			if (yu < minyu) minyu = yu;
			if (yu > maxyu) maxyu = yu;
		}

		//top edge
		yd = nH - 1;
		for (unsigned xd = 0; xd < nW; xd++)
		{
			double xu = 0.0;
			double yu = 0.0;
			getUndistortedPoint(xu, yu, dm, xd, yd);

			if (xu < minxu) minxu = xu;
			if (xu > maxxu) maxxu = xu;
			if (yu < minyu) minyu = yu;
			if (yu > maxyu) maxyu = yu;
		}
		
		//left edge
		unsigned xd = 0;
		for (unsigned yd = 0; yd < nH; yd++)
		{
			double xu = 0.0;
			double yu = 0.0;
			getUndistortedPoint(xu, yu, dm, xd, yd);

			if (xu < minxu) minxu = xu;
			if (xu > maxxu) maxxu = xu;
			if (yu < minyu) minyu = yu;
			if (yu > maxyu) maxyu = yu;
		}

		//right edge
		xd = nW - 1;
		for (unsigned yd = 0; yd < nH; yd++)
		{
			double xu = 0.0;
			double yu = 0.0;
			getUndistortedPoint(xu, yu, dm, xd, yd);

			if (xu < minxu) minxu = xu;
			if (xu > maxxu) maxxu = xu;
			if (yu < minyu) minyu = yu;
			if (yu > maxyu) maxyu = yu;
		}
			   
		double dw = maxxu - minxu;
		double dh = maxyu - minyu;

		//dm.xumin = minxu;
		//dm.xumax = maxxu;
		//dm.yumin = minyu;
		//dm.yumax = maxyu;

		if (bOutputDistMap)
		{
			nPd = ((nW * 8 + 31) & ~31) >> 3;
			if (nullptr != pDistMap)
				delete[]pDistMap;
			pDistMap = new unsigned char[nH*nPd];
		}

		mind = 1.0e10;
		maxd = -1.0e10;

		const double eps = 1.0e-2;

		//undistortion map
		double deltax = dw / (nW - 1);
		double deltay = dh / (nH - 1);
		for (unsigned y = 0; y < nH; y++)
		{
			for (unsigned x = 0; x < nW; x++)
			{
				double xu = minxu + x * deltax;
				double yu = minyu + y * deltay;

				double xd, yd, rd;
				if (getDistortedPoint(xd, yd, rd, dm, xu, yu))
				{
					if (xd > 0 && xd < nW - 1 && yd > 0 && yd < nH - 1)
					{
						double d = sqrt((xd - xu)*(xd - xu) + (yd - yu)*(yd - yu));
						if (d < mind) mind = d;
						if (d > maxd) maxd = d;

						pDP[y*nW + x].xd = (float)xd;
						pDP[y*nW + x].yd = (float)yd;
						pDP[y*nW + x].dist = (float)d;

						if (bOutputDistMap)
						{
							if (d <= 0.00001)
							{
								pDistMap[y*nPd + x] = 128;
							}
							else
							{
								if (fabs(d - 0.5) < eps || fabs(d - 1) < eps ||
									fabs(d - 2) < eps   || fabs(d - 3) < eps ||
									fabs(d - 4) < eps   || fabs(d - 5) < eps ||
									fabs(d - 6) < eps   || fabs(d - 7) < eps ||
									fabs(d - 8) < eps   || fabs(d - 9) < eps ||
									fabs(d - 10) < eps)
								{
									pDistMap[y*nPd + x] = 255;
								}
								else
								{
									pDistMap[y*nPd + x] = (unsigned char)(10 * d);
								}
							}
						}
					}
				}
			}
		}


		//double xuLB = 0.0, yuLB = 0.0;
		//getUndistortedPoint(xuLB, yuLB, dm, 0, 0);

		//double xuRB = 0.0, yuRB = 0.0;
		//getUndistortedPoint(xuLB, yuLB, dm, nW-1, 0);
		//
		//double xuLT = 0.0, yuLT = 0.0;
		//getUndistortedPoint(xuLB, yuLB, dm, 0, nH-1);

		//double xuRT = 0.0, yuRT = 0.0;
		//getUndistortedPoint(xuLB, yuLB, dm, nW-1, nH-1);

		//double xlb = (xuLB - minxu) / deltax;
		//double ylb = (yuLB - minyu) / deltay;

		//double xrb = (xuRB - minxu) / deltax;
		//double yrb = (yuRB - minyu) / deltay;

		//double xlt = (xuLT - minxu) / deltax;
		//double ylt = (yuLT - minyu) / deltay;

		//double xrt = (xuRT - minxu) / deltax;
		//double yrt = (yuRT - minyu) / deltay;

		//dm.xs = xlb > xlt ? xlb : xlt;
		//dm.xe = xrb < xrt ? xrb : xrt;
		//dm.ys = ylb > yrb ? ylb : yrb;
		//dm.ye = ylt < yrt ? ylt : yrt;

		return true; 
	}


	bool undistortion(unsigned char *&pImgU, unsigned &nWu, unsigned &nPu, unsigned &nHu,
		distortion_pair *pDistPair,
		unsigned char *pImg, unsigned nW, unsigned nP, unsigned nH,
		unsigned nCropLength, double dUndistortionRadius)
	{
		if (nullptr == pDistPair 
			|| nullptr == pImg 
			|| nW > nP 
			|| 2 * nCropLength >= nW 
			|| 2 * nCropLength >= nH)
		{
			return false;
		}

		const unsigned nC = nP / nW;
		const unsigned xs = nCropLength, xe = nW - nCropLength, ys = nCropLength, ye = nH - nCropLength;
		nWu = xe - xs;
		nHu = ye - ys;
		nPu = (((xe - xs)*nC * 8 + 31) & ~31) >> 3;
		if (nullptr != pImgU)
			delete[]pImgU;
		pImgU = new unsigned char[nHu*nPu];

		if (1 == nC)
		{
			unsigned uPos = 0;
			unsigned iPos = ys * nW;
			for (unsigned y = ys; y < ye; y++)
			{
				unsigned xuPos = uPos;
				for (unsigned x = xs; x < xe; x++)
				{
					unsigned xiPos = iPos + x;

					if (pDistPair[xiPos].dist > 0.0)
					{
						float xd = pDistPair[xiPos].xd;
						float yd = pDistPair[xiPos].yd;

						int i1 = (int)xd;
						int j1 = (int)yd;
						unsigned dPos = j1 * nP + i1 * nC;

						if (pDistPair[xiPos].dist > dUndistortionRadius)
						{
							int i2 = (int)xd + 1;
							int j2 = (int)yd + 1;
							double d1 = (i2 - xd)*(j2 - yd);
							double d2 = (xd - i1)*(j2 - yd);
							double d3 = (i2 - xd)*(yd - j1);
							double d4 = (xd - i1)*(yd - j1);
							pImgU[xuPos] =  (unsigned char)(pImg[dPos] * d1 + 
															pImg[dPos + nC] * d2 + 
															pImg[dPos + nP] * d3 + 
															pImg[dPos + nP + nC] * d4);
						}
						else
						{
							pImgU[xuPos] = pImg[dPos];
						}
					}

					xuPos += nC;
				}

				uPos += nPu;
				iPos += nW;
			}
		}
		else if (nC >= 3)
		{
			unsigned uPos = 0;
			unsigned iPos = ys * nW;
			for (unsigned y = ys; y < ye; y++)
			{
				unsigned xuPos = uPos;
				for (unsigned x = xs; x < xe; x++)
				{
					unsigned xiPos = iPos + x;

					if (pDistPair[xiPos].dist > 0.0)
					{
						float xd = pDistPair[xiPos].xd;
						float yd = pDistPair[xiPos].yd;

						int i1 = (int)xd;
						int j1 = (int)yd;
						unsigned dPos = j1 * nP + i1 * nC;

						if (pDistPair[xiPos].dist > dUndistortionRadius)
						{
							int i2 = (int)xd + 1;
							int j2 = (int)yd + 1;
							double d1 = (i2 - xd)*(j2 - yd), d2 = (xd - i1)*(j2 - yd), d3 = (i2 - xd)*(yd - j1), d4 = (xd - i1)*(yd - j1);
							pImgU[xuPos + 0] = (unsigned char)(pImg[dPos + 0] * d1 + pImg[dPos + nC + 0] * d2 + pImg[dPos + nP + 0] * d3 + pImg[dPos + nP + nC + 0] * d4);
							pImgU[xuPos + 1] = (unsigned char)(pImg[dPos + 1] * d1 + pImg[dPos + nC + 1] * d2 + pImg[dPos + nP + 1] * d3 + pImg[dPos + nP + nC + 1] * d4);
							pImgU[xuPos + 2] = (unsigned char)(pImg[dPos + 2] * d1 + pImg[dPos + nC + 2] * d2 + pImg[dPos + nP + 2] * d3 + pImg[dPos + nP + nC + 2] * d4);
						}
						else
						{
							pImgU[xuPos]   = pImg[dPos];
							pImgU[xuPos+1] = pImg[dPos+1];
							pImgU[xuPos+2] = pImg[dPos+2];
						}
					}

					xuPos += nC;
				}
				uPos += nPu;
				iPos += nW;
			}
		}
		else
		{
			delete[]pImgU;

			return false;
		}

		return true;
	}

	bool undistortion(unsigned char *&pImgU, unsigned &nWu, unsigned &nPu, unsigned &nHu,
		division_model &dm,
		unsigned char *pImg, unsigned nW, unsigned nP, unsigned nH,
		unsigned nCropLength, double dUndistortionRadius)
	{
		distortion_pair *pDistPair = nullptr;
		double dMinOffset, dMaxOffset;
		unsigned char *pDist = nullptr;
		unsigned nPd = 0;
		if (!createDistortionMap(pDistPair, dMinOffset, dMaxOffset, false, pDist, nPd, nW, nH, dm))
		{
			return false;
		}

		bool bOK = undistortion(pImgU, nWu, nPu, nHu, pDistPair, pImg, nW, nP, nH, nCropLength, dUndistortionRadius);
		
		delete[]pDistPair;

		return bOK;
	}


	void undistortionOpenMP(unsigned char *pImg, unsigned nW, unsigned nP, unsigned nH,
		unsigned nCropLength, double dUndistortionRadius,
		distortion_pair *pDistMap,
		unsigned char *&pImgU, unsigned &nWu, unsigned &nPu, unsigned &nHu)
	{
		const unsigned nC = nP / nW;
		const unsigned xs = nCropLength, xe = nW - nCropLength, ys = nCropLength, ye = nH - nCropLength;
		nWu = xe - xs;
		nHu = ye - ys;
		nPu = (((xe - xs)*nC * 8 + 31) & ~31) >> 3;
		if (nullptr != pImgU)
			delete[]pImgU;
		pImgU = new unsigned char[nHu*nPu];

		int n = nW * nH;
		int ks = ys * nW;
		int ke = ye * nW;

#pragma omp parallel
		{
#pragma omp for
			for (int k = ks; k < ke; k++)
			{
				int y = k / nW;
				int x = k % nW;

				if (x >= xs && x < xe)
				{
					float xd = pDistMap[k].xd;
					float yd = pDistMap[k].yd;

					int xuPos = (y - ys) * nPu + (x - xs) * nC;

					int i1 = (int)xd;
					int j1 = (int)yd;
					int dPos = j1 * nP + i1 * nC;
					//if (pDistMap[k].dist > dUndistortionRadius)
					if (x<xs + 100 || x>xe - 100 || y<ys + 100 || y>ye - 100)
					{
						int i2 = (int)xd + 1;
						int j2 = (int)yd + 1;
						double d1 = (i2 - xd)*(j2 - yd), d2 = (xd - i1)*(j2 - yd), d3 = (i2 - xd)*(yd - j1), d4 = (xd - i1)*(yd - j1);
						pImgU[xuPos + 0] = (unsigned char)(pImg[dPos + 0] * d1 + pImg[dPos + nC + 0] * d2 + pImg[dPos + nP + 0] * d3 + pImg[dPos + nP + nC + 0] * d4);
						pImgU[xuPos + 1] = (unsigned char)(pImg[dPos + 1] * d1 + pImg[dPos + nC + 1] * d2 + pImg[dPos + nP + 1] * d3 + pImg[dPos + nP + nC + 1] * d4);
						pImgU[xuPos + 2] = (unsigned char)(pImg[dPos + 2] * d1 + pImg[dPos + nC + 2] * d2 + pImg[dPos + nP + 2] * d3 + pImg[dPos + nP + nC + 2] * d4);
					}
					else
					{
						pImgU[xuPos + 0] = pImg[dPos + 0];
						pImgU[xuPos + 1] = pImg[dPos + 1];
						pImgU[xuPos + 2] = pImg[dPos + 2];
					}
				}
			}
		}

		return;
	}
}
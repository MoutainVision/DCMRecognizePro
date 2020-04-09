#pragma once


#ifdef LIBDISTORTIONCORRECTION_EXPORTS
#define LIBDISTORTIONCORRECTION_API __declspec(dllexport)
#else
#define LIBDISTORTIONCORRECTION_API __declspec(dllimport)
#endif

namespace avs
{


	/**
	*@brief Fitzgibbon's single-parameter division model of lens distortion:
	* ru = rd / (1 + lambda * rd^2)
	* xu = x0 + (xd - x0) / (1 + lambda * rd^2)
	* yu = y0 + (yd - y0) / (1 + lambda * rd^2)
	* rd = sqrt((xd - x0)^2 + (yd - y0)^2)
	*
	*@param x0 x coordinate of the distortion centre
	*@param y0 y coordinate of the distortion centre
	*@param lambda  the first and only radial distortion parameter used in division model
	*@note Nothing
	*@remarks Nothing
	*/
	struct LIBDISTORTIONCORRECTION_API division_model
	{
		double x0, y0, lambda;
	};


	/**
	*@brief the distortion pair
	*@param xd x coordinate of the corresponding point in the distorted image
	*@param yd y coordinate of the corresponding point in the distorted image
	*@param dist  distance between the pair of distorted and undistorted point
	*@note Nothing
	*@remarks Nothing
	*/
	struct LIBDISTORTIONCORRECTION_API distortion_pair
	{
		//unsigned xu, yu;
		//unsigned p[4];
		//float    d[4];
		float xd, yd, dist;
		distortion_pair()
		{
			dist = -1.0;
		}
	};

	/**
	*@brief Calculation of the division model
	*@param xc0 [in] x coordinate of centre of the first circle
	*@param yc0 [in] y coordinate of centre of the first circle
	*@param r0  [in] radius of centre of the first circles
	*@param xc1 [in] x coordinate of centre of the second circle
	*@param yc1 [in] y coordinate of centre of the second circle
	*@param r1  [in] radius of centre of the second circles
	*@param xc2 [in] x coordinate of centre of third first circle
	*@param yc2 [in] y coordinate of centre of third first circle
	*@param r2  [in] radius of centre of the third circles
	*@param x0 [out] x cordinate of the distortion centre of division model
	*@param y0 [out] y cordinate of the distortion centre of division model
	*@param lambda [out] radial distortion parameter of the division model
	*@return True if everything is OK, else return false
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API bool calcDivisionModel(double &x0, double &y0, double &lambda, 
														double xc0, double yc0, double r0, 
														double xc1, double yc1, double r1, 
														double xc2, double yc2, double r2);
	/**
	*@brief Calculation of the division model
	*@param xc [in] x coordinates of centres of  three circles
	*@param yc [in] y coordinates of centres of three circles
	*@param r  [in] radius of centres of three circles
	*@param x0 [out] x cordinate of the distortion centre of division model
	*@param y0 [out] y cordinate of the distortion centre of division model
	*@param lambda [out] radial distortion parameter of the division model
	*@return True if everything is OK, else return false
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API bool calcDivisionModel(double &x0, double &y0, double &lambda, 
													   double xc[3], double yc[3], double r[3]);


	/**
	*@brief Calculation of the division model
	*@param xc [in] x coordinates of centres of three circles
	*@param yc [in] y coordinates of centres of three circles
	*@param r  [in] radius of centres of three circles
	*@param dm [out] distortion model
	*@return True if everything is OK, else return false
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API bool calcDivisionModel(division_model &dm, double xc[3], double yc[3], double r[3]);


	/**
	*@brief Calculation of the division model
	*@param xc0 [in] x coordinate of centre of the first circle
	*@param yc0 [in] y coordinate of centre of the first circle
	*@param r0  [in] radius of centre of the first circles
	*@param xc1 [in] x coordinate of centre of the second circle
	*@param yc1 [in] y coordinate of centre of the second circle
	*@param r1  [in] radius of centre of the second circles
	*@param xc2 [in] x coordinate of centre of third first circle
	*@param yc2 [in] y coordinate of centre of third first circle
	*@param r2  [in] radius of centre of the third circles
	*@param dm [out] distortion model
	*@return True if everything is OK, else return false
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API bool calcDivisionModel(division_model &dm, 
														double xc0, double yc0, double r0, 
														double xc1, double yc1, double r1, 
														double xc2, double yc2, double r2);


	LIBDISTORTIONCORRECTION_API void getUndistortedPoint(double &xu, double &yu, division_model &dm, double xd, double yd);

	LIBDISTORTIONCORRECTION_API bool getDistortedPoint(double &xd, double &yd, double &rd, division_model &dm, double xu, double yu);


	/**
	*@brief For each point of the undistorted image calculate its corresponding point in the distorted image
	*@param nW [in] image width of the undistorted image
	*@param nP [in] image pitch of the undistorted image
	*@param nH [in] image height of the undistored image
	*@param dm [in] distortion model
	*@param pDP [out] array of distortion_pair containing the position of each corresponding point in the distorted image
	*@param mind [out] minimum distance between the distorted point and its corresponding undistored point
	*@param maxd [out] maximum distance between the distorted point and its corresponding undistored point
	*@param bOutputDistMap [in] flag indicating outputing the disotrtion map or not, true--YES, false--NO
	*@param pDist [out] array of the distance between the distorted point and its corresponding undistored point
	*@param nPd [out] pitch of the array pDist
	*@return void
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API bool createDistortionMap(distortion_pair *&pDistPair, double &mind, double &maxd,
										bool bOutputDistMap, unsigned char *&pDist, unsigned &nPd,
										unsigned nW, unsigned nH, division_model &dm);



	/**
	*@brief Distortion correction for the input image
	*@param pImg [in] input distorted image
	*@param nW   [in] image width of the undistorted image
	*@param nP   [in] image pitch of the undistorted image
	*@param nH   [in] image height of the undistored image
	*@param nCropLength   [in] length of cropping the undistorted image, whose size will be (nW-2*nCropLength)x(nH-2*nCropLength)
	*@param nUndistortionRadius [in] distance threshold for distortion correction, each point from the undistorted image with a distance from its corresponding distorted point less larger than the threshold will perform correction
	*@param pDistMap [in] array of distortion_pair
	*@param pImgU [out] output undistorted image
	*@param nWu [out] width of the output undistorted image
	*@param nHu [out] height of the output undistorted image
	*@param nPu [out] pitch of the output undistorted image
	*@return void
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API bool undistortion(unsigned char *&pImgU, unsigned &nWu, unsigned &nPu, unsigned &nHu,
		distortion_pair *pDistPair,
		unsigned char *pImg, unsigned nW, unsigned nP, unsigned nH,
		unsigned nCropLength=0, double dUndistortionRadius=1.0);

	LIBDISTORTIONCORRECTION_API bool undistortion(unsigned char *&pImgU, unsigned &nWu, unsigned &nPu, unsigned &nHu,
		division_model &dm,
		unsigned char *pImg, unsigned nW, unsigned nP, unsigned nH,
		unsigned nCropLength=0, double dUndistortionRadius=1.0);


	/**
	*@brief Distortion correction for the input image with OpenMP for speedup
	*@param pImg [in] input distorted image
	*@param nW   [in] image width of the undistorted image
	*@param nP   [in] image pitch of the undistorted image
	*@param nH   [in] image height of the undistored image
	*@param nCropLength   [in] length of cropping the undistorted image, whose size will be (nW-2*nCropLength)x(nH-2*nCropLength)
	*@param nUndistortionRadius [in] distance threshold for distortion correction, each point from the undistorted image with a distance from its corresponding distorted point less larger than the threshold will perform correction
	*@param pDistMap [in] array of distortion_pair
	*@param pImgU [out] output undistorted image
	*@param nWu [out] width of the output undistorted image
	*@param nHu [out] height of the output undistorted image
	*@param nPu [out] pitch of the output undistorted image
	*@return void
	*@note Nothing
	*@remarks Nothing
	*/
	LIBDISTORTIONCORRECTION_API void undistortionOpenMP(unsigned char *pImg, unsigned nW, unsigned nP, unsigned nH,
		unsigned nCropLength, double dUndistortionRadius,
		distortion_pair *pDistMap,
		unsigned char *&pImgU, unsigned &nWu, unsigned &nPu, unsigned &nHu);

}
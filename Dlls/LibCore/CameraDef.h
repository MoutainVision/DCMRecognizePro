#pragma once

namespace avs
{
#ifndef _CAMERA_VENDOR_
#define _CAMERA_VENDOR_
	enum ECameraVendor
	{
		CAMERA_VENDOR_POINTGREY,

		CAMERA_VENDOR_IMI,

		CAMERA_VENDOR_MOTIC,

		CAMERA_VENDOR_JAI,

		CAMERA_VENDOR_IDS,

		CAMERA_VENDOR_MOTICIMX,

		CAMERA_VENDOR_TOUPTEK,

		CAMERA_VENDOR_UNKNOWN
	};
#endif 

#ifndef _DISPLAY_FORMAT_
#define _DISPLAY_FORMAT_
	enum EDisplayFormat
	{
		DISPLAY_NONE,

		DISPLAY_COLOR_IMAGE,

		DISPLAY_RAW_IMAGE
	};
#endif


#ifndef _BAYER_FORMAT_
#define _BAYER_FORMAT_
	enum EBayerFormat
	{
		BAYER_FORMAT_UNKNOWN = -1,

		BAYER_FORMAT_NONE, //No bayer tile format. 

		BAYER_FORMAT_RGGB, //Red-Green-Green-Blue. 

		BAYER_FORMAT_GRBG, //Green-Red-Blue-Green. 

		BAYER_FORMAT_GBRG, //Green-Blue-Red-Green. 

		BAYER_FORMAT_BGGR, //Blue-Green-Green-Red. 

		BAYER_FORMAT_BT_FORCE_32BITS
	};
#endif


#ifndef _FLIP_TYPE_
#define _FLIP_TYPE_
	enum EFlipType
	{
		FLIP_NONE,

		FLIP_HOR,

		FLIP_VER
	};
#endif




}
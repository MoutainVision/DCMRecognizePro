#pragma once
#include "Image.h"

namespace avs
{


#pragma pack(1)
	typedef struct tagBITMAPFILEHEADER 
	{
		WORD bfType;
		DWORD bfSize;
		WORD bfReserved1;
		WORD bfReserved2;
		DWORD bfOffBits;
	} BITMAPFILEHEADER;
#pragma pack()


class xImageBMP :
	public xImage
{
public:
	xImageBMP();
	virtual ~xImageBMP();


	bool decode(xFile * hFile);
	bool decode(FILE *hFile) { xIOFile file(hFile); return decode(&file); }

//#if CXIMAGE_SUPPORT_ENCODE
	bool encode(xFile * hFile);
	bool encode(FILE *hFile) { xIOFile file(hFile); return encode(&file); }
//#endif // CXIMAGE_SUPPORT_ENCODE

//protected:
//	bool dibReadBitmapInfo(xFile* fh, BITMAPINFOHEADER *pdib);
};

}


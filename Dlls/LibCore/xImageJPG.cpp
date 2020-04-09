/*
 * File:	ximajpg.cpp
 * Purpose:	Platform Independent JPEG Image Class Loader and Writer
 * 07/Aug/2001 Davide Pizzolato - www.xdp.it
 * CxImage version 7.0.2 07/Feb/2011
 */
 
#include "xImageJPG.h"

#if XIMAGE_SUPPORT_JPG

#ifdef _LINUX
 #include <jmorecfg.h>
#else
 #include "jpeg/jmorecfg.h"
#endif

#include "ximageiter.h"

#include <setjmp.h>

#pragma comment(lib,"jpeg.lib")

namespace avs
{
	struct jpg_error_mgr 
	{
		struct jpeg_error_mgr pub;	/* "public" fields */
		jmp_buf setjmp_buffer;		/* for return to caller */
		char* buffer;				/* error message <CSC>*/
	};
	typedef jpg_error_mgr *jpg_error_ptr;


	////////////////////////////////////////////////////////////////////////////////
	// Here's the routine that will replace the standard error_exit method:
	////////////////////////////////////////////////////////////////////////////////
	static void
		ima_jpeg_error_exit(j_common_ptr cinfo)
	{
		/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
		jpg_error_ptr myerr = (jpg_error_ptr)cinfo->err;
		/* Create the message */
		myerr->pub.format_message(cinfo, myerr->buffer);
		/* Send it to stderr, adding a newline */
		/* Return control to the setjmp point */
		longjmp(myerr->setjmp_buffer, 1);
	}

	////////////////////////////////////////////////////////////////////////////////
	xImageJPG::xImageJPG() : xImage(XIMAGE_FORMAT_JPG)
	{
#if CXIMAGEJPG_SUPPORT_EXIF
		m_exif = NULL;
		memset(&info.ExifInfo, 0, sizeof(EXIFINFO));
#endif
	}

	////////////////////////////////////////////////////////////////////////////////
	xImageJPG::~xImageJPG()
	{
#if CXIMAGEJPG_SUPPORT_EXIF
		if (m_exif) delete m_exif;
#endif
	}

	////////////////////////////////////////////////////////////////////////////////
#if CXIMAGEJPG_SUPPORT_EXIF
	bool CxImageJPG::DecodeExif(CxFile * hFile)
	{
		m_exif = new CxExifInfo(&info.ExifInfo);
		if (m_exif) {
			int32_t pos = hFile->Tell();
			m_exif->DecodeExif(hFile);
			hFile->Seek(pos, SEEK_SET);
			return m_exif->m_exifinfo->IsExif;
		}
		else {
			return false;
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	bool CxImageJPG::GetExifThumbnail(const TCHAR *filename, const TCHAR *outname, int32_t type)
	{
		CxIOFile file;
		if (!file.Open(filename, _T("rb"))) return false;
		CxExifInfo exif(&info.ExifInfo);
		exif.DecodeExif(&file);
		if (info.ExifInfo.IsExif && info.ExifInfo.ThumbnailPointer && info.ExifInfo.ThumbnailSize > 0)
		{ // have a thumbnail - check whether it needs rotating or resizing
		  // TODO: Write a fast routine to read the jpeg header to get the width and height
			CxImage image(info.ExifInfo.ThumbnailPointer, info.ExifInfo.ThumbnailSize, CXIMAGE_FORMAT_JPG);
			if (image.IsValid())
			{
				if (image.GetWidth() > 256 || image.GetHeight() > 256)
				{ // resize the image
		  //        float amount = 256.0f / max(image.GetWidth(), image.GetHeight());
		  //        image.Resample((int32_t)(image.GetWidth() * amount), (int32_t)(image.GetHeight() * amount), 0);
				}
#if CXIMAGE_SUPPORT_TRANSFORMATION
				if (info.ExifInfo.Orientation != 1)
					image.RotateExif(info.ExifInfo.Orientation);
#endif
#if CXIMAGE_SUPPORT_ENCODE
				return image.Save(outname, CXIMAGE_FORMAT_JPG);
#endif
			}
			// nice and fast, but we can't resize :(
			/*
			FILE *hFileWrite;
			if ((hFileWrite=fopen(outname, "wb")) != NULL)
			{
			  fwrite(m_exifinfo.ThumbnailPointer, m_exifinfo.ThumbnailSize, 1, hFileWrite);
			  fclose(hFileWrite);
			  return true;
			}*/
		}
		return false;
	}
#endif //CXIMAGEJPG_SUPPORT_EXIF

	////////////////////////////////////////////////////////////////////////////////
#if XIMAGE_SUPPORT_DECODE
////////////////////////////////////////////////////////////////////////////////
	bool xImageJPG::decode(xFile * hFile)
	{

		bool is_exif = false;
#if CXIMAGEJPG_SUPPORT_EXIF
		is_exif = DecodeExif(hFile);
#endif

		ImageIterator iter(this);

		/* This struct contains the JPEG decompression parameters and pointers to
		* working space (which is allocated as needed by the JPEG library).
		*/
		struct jpeg_decompress_struct cinfo;

		/* We use our private extension JPEG error handler. <CSC> */
		struct jpg_error_mgr jerr;
		jerr.buffer = m_extInfo.szLastError;

		/* More stuff */
		JSAMPARRAY buffer;	/* Output row buffer */
		int32_t row_stride;		/* physical row width in output buffer */

		/* In this example we want to open the input file before doing anything else,
		* so that the setjmp() error recovery below can assume the file is open.
		* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
		* requires it in order to read binary files.
		*/

		/* Step 1: allocate and initialize JPEG decompression object */
		/* We set up the normal JPEG error routines, then override error_exit. */
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = ima_jpeg_error_exit;

		CxFileJpg src(hFile);

		/* Establish the setjmp return context for my_error_exit to use. */
		if (setjmp(jerr.setjmp_buffer)) 
		{
			/* If we get here, the JPEG code has signaled an error.
			* We need to clean up the JPEG object, close the input file, and return.
			*/
			jpeg_destroy_decompress(&cinfo);
			return 0;
		}

		/* Now we can initialize the JPEG decompression object. */
		jpeg_create_decompress(&cinfo);

		/* Step 2: specify data source (eg, a file) */
		//jpeg_stdio_src(&cinfo, infile);
		cinfo.src = &src;

		/* Step 3: read file parameters with jpeg_read_header() */
		(void)jpeg_read_header(&cinfo, TRUE);

		/* Step 4 <chupeev> handle decoder options*/
		uint32_t dwCodecOptions = getCodecOption(XIMAGE_FORMAT_JPG); //[nm_114]
		if ((dwCodecOptions & DECODE_GRAYSCALE) != 0)
			cinfo.out_color_space = JCS_GRAYSCALE;
		if ((dwCodecOptions & DECODE_QUANTIZE) != 0) 
		{
			cinfo.quantize_colors = TRUE;
			cinfo.desired_number_of_colors = getJpegQuality();
		}
		if ((dwCodecOptions & DECODE_DITHER) != 0)
			cinfo.dither_mode = m_nDither;
		if ((dwCodecOptions & DECODE_ONEPASS) != 0)
			cinfo.two_pass_quantize = FALSE;
		if ((dwCodecOptions & DECODE_NOSMOOTH) != 0)
			cinfo.do_fancy_upsampling = FALSE;

		//<DP>: Load true color images as RGB (no quantize) 
		/* Step 4: set parameters for decompression */
		/*  if (cinfo.jpeg_color_space!=JCS_GRAYSCALE) {
		 *	cinfo.quantize_colors = TRUE;
		 *	cinfo.desired_number_of_colors = 128;
		 *}
		 */ //</DP>

		cinfo.scale_num = 1;
		// Set the scale <ignacio>
		cinfo.scale_denom = getJpegScale();

		// Borrowed the idea from GIF implementation <ignacio>
		if (m_extInfo.nEscape == -1) 
		{
			// Return output dimensions only
			jpeg_calc_output_dimensions(&cinfo);
			m_bmpHead.biWidth = cinfo.output_width;
			m_bmpHead.biHeight = cinfo.output_height;
			m_extInfo.dwType = XIMAGE_FORMAT_JPG;
			jpeg_destroy_decompress(&cinfo);
			return true;
		}

		/* Step 5: Start decompressor */
		jpeg_start_decompress(&cinfo);

		/* We may need to do some setup of our own at this point before reading
		* the data.  After jpeg_start_decompress() we have the correct scaled
		* output image dimensions available, as well as the output colormap
		* if we asked for color quantization.
		*/
		//Create the image using output dimensions <ignacio>
		//Create(cinfo.image_width, cinfo.image_height, 8*cinfo.output_components, CXIMAGE_FORMAT_JPG);
		create(cinfo.output_width, cinfo.output_height, 8 * cinfo.output_components, XIMAGE_FORMAT_JPG);

		//if (!pDib) longjmp(jerr.setjmp_buffer, 1);  //<DP> check if the image has been created
		
		if (is_exif) 
		{
#if CXIMAGEJPG_SUPPORT_EXIF
			if ((info.ExifInfo.Xresolution != 0.0) && (info.ExifInfo.ResolutionUnit != 0))
				SetXDPI((int32_t)(info.ExifInfo.Xresolution / info.ExifInfo.ResolutionUnit));
			if ((info.ExifInfo.Yresolution != 0.0) && (info.ExifInfo.ResolutionUnit != 0))
				SetYDPI((int32_t)(info.ExifInfo.Yresolution / info.ExifInfo.ResolutionUnit));
#endif
		}
		else 
		{
			switch (cinfo.density_unit)
			{
			case 0:	// [andy] fix for aspect ratio...
				if ((cinfo.Y_density > 0) && (cinfo.X_density > 0)) {
					setYDPI((int32_t)(getXDPI()*(float(cinfo.Y_density) / float(cinfo.X_density))));
				}
				break;
			case 2: // [andy] fix: cinfo.X/Y_density is pixels per centimeter
				setXDPI((int32_t)floor(cinfo.X_density * 2.54 + 0.5));
				setYDPI((int32_t)floor(cinfo.Y_density * 2.54 + 0.5));
				break;
			default:
				setXDPI(cinfo.X_density);
				setYDPI(cinfo.Y_density);
			}
		}

		if (cinfo.out_color_space == JCS_GRAYSCALE) 
		{
			setGrayPalette();
			m_bmpHead.biClrUsed = 256;
		}
		else 
		{
			if (cinfo.quantize_colors) {
				setPalette(cinfo.actual_number_of_colors, cinfo.colormap[0], cinfo.colormap[1], cinfo.colormap[2]);
				m_bmpHead.biClrUsed = cinfo.actual_number_of_colors;
			}
			else
			{
				m_bmpHead.biClrUsed = 0;
			}
		}

		/* JSAMPLEs per row in output buffer */
		row_stride = cinfo.output_width * cinfo.output_components;

		/* Make a one-row-high sample array that will go away when done with image */
		buffer = (*cinfo.mem->alloc_sarray)
			((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

		/* Step 6: while (scan lines remain to be read) */
		/*           jpeg_read_scanlines(...); */
		/* Here we use the library's state variable cinfo.output_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		*/
		iter.Upset();
		while (cinfo.output_scanline < cinfo.output_height)
		{

			if (m_extInfo.nEscape)
			{
				longjmp(jerr.setjmp_buffer, 1); // <vho> - cancel decoding
			}

			(void)jpeg_read_scanlines(&cinfo, buffer, 1);
			// info.nProgress = (int32_t)(100*cinfo.output_scanline/cinfo.output_height);
			//<DP> Step 6a: CMYK->RGB */ 
			if ((cinfo.num_components == 4) && (cinfo.quantize_colors == FALSE)) 
			{
				uint8_t k, *dst, *src;
				dst = iter.GetRow();
				src = buffer[0];
				for (int32_t x3 = 0, x4 = 0; x3 < (int32_t)m_extInfo.dwEffWidth && x4 < row_stride; x3 += 3, x4 += 4) 
				{
					k = src[x4 + 3];
					dst[x3] = (uint8_t)((k * src[x4 + 2]) / 255);
					dst[x3 + 1] = (uint8_t)((k * src[x4 + 1]) / 255);
					dst[x3 + 2] = (uint8_t)((k * src[x4 + 0]) / 255);
				}
			}
			else
			{
				/* Assume put_scanline_someplace wants a pointer and sample count. */
				iter.SetRow(buffer[0], row_stride);
			}

			iter.PrevRow();
		}

		/* Step 7: Finish decompression */
		(void)jpeg_finish_decompress(&cinfo);
		/* We can ignore the return value since suspension is not possible
		* with the stdio data source.
		*/

		//<DP> Step 7A: Swap red and blue components
		// not necessary if swapped red and blue definition in jmorecfg.h;ln322 <W. Morrison>
		if ((cinfo.num_components == 3) && (cinfo.quantize_colors == FALSE)) 
		{
			uint8_t* r0 = getBuffer();

			for (int32_t y = 0; y < m_bmpHead.biHeight; y++) 
			{
				if (m_extInfo.nEscape)
				{
					longjmp(jerr.setjmp_buffer, 1); // <vho> - cancel decoding
				}

				RGBtoBGR(r0, 3 * m_bmpHead.biWidth);

				r0 += m_extInfo.dwEffWidth;
			}
		}

		/* Step 8: Release JPEG decompression object */
		/* This is an important step since it will release a good deal of memory. */
		jpeg_destroy_decompress(&cinfo);

		/* At this point you may want to check to see whether any corrupt-data
		* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
		*/

		if (cinfo.out_color_space == JCS_GRAYSCALE)
		{
			m_pixFmt = PIXEL_FORMAT_MONO8;
		}
		else
		{
			m_pixFmt = PIXEL_FORMAT_BGR;
		}
		m_byrFmt = BAYER_FORMAT_NONE;

		/* And we're done! */
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////
#endif //CXIMAGE_SUPPORT_DECODE

////////////////////////////////////////////////////////////////////////////////
#if XIMAGE_SUPPORT_ENCODE
////////////////////////////////////////////////////////////////////////////////
	bool xImageJPG::encode(xFile * hFile)
	{
		if (!safeForEncode(hFile))
		{
			return false;
		}

		if (m_bmpHead.biClrUsed != 0 && !isGrayScale()) 
		{
			//strcpy(m_extInfo.szLastError, "JPEG can save only RGB or GreyScale images");
			return false;
		}

		// necessary for EXIF, and for roll backs
		int32_t pos = hFile->tell();

		/* This struct contains the JPEG compression parameters and pointers to
		* working space (which is allocated as needed by the JPEG library).
		* It is possible to have several such structures, representing multiple
		* compression/decompression processes, in existence at once.  We refer
		* to any one struct (and its associated working data) as a "JPEG object".
		*/
		struct jpeg_compress_struct cinfo;
		/* This struct represents a JPEG error handler.  It is declared separately
		* because applications often want to supply a specialized error handler
		* (see the second half of this file for an example).  But here we just
		* take the easy way out and use the standard error handler, which will
		* print a message on stderr and call exit() if compression fails.
		* Note that this struct must live as int32_t as the main JPEG parameter
		* struct, to avoid dangling-pointer problems.
		*/
		//struct jpeg_error_mgr jerr;
		/* We use our private extension JPEG error handler. <CSC> */
		struct jpg_error_mgr jerr;
		jerr.buffer = m_extInfo.szLastError;
		/* More stuff */
		int32_t row_stride;		/* physical row width in image buffer */
		JSAMPARRAY buffer;		/* Output row buffer */

		/* Step 1: allocate and initialize JPEG compression object */
		/* We have to set up the error handler first, in case the initialization
		* step fails.  (Unlikely, but it could happen if you are out of memory.)
		* This routine fills in the contents of struct jerr, and returns jerr's
		* address which we place into the link field in cinfo.
		*/
		//cinfo.err = jpeg_std_error(&jerr); <CSC>
		/* We set up the normal JPEG error routines, then override error_exit. */
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = ima_jpeg_error_exit;

		/* Establish the setjmp return context for my_error_exit to use. */
		if (setjmp(jerr.setjmp_buffer))
		{
			/* If we get here, the JPEG code has signaled an error.
			* We need to clean up the JPEG object, close the input file, and return.
			*/
			//strcpy(m_extInfo.szLastError, jerr.buffer); //<CSC>
			jpeg_destroy_compress(&cinfo);
			return false;
		}

		/* Now we can initialize the JPEG compression object. */
		jpeg_create_compress(&cinfo);
		/* Step 2: specify data destination (eg, a file) */
		/* Note: steps 2 and 3 can be done in either order. */
		/* Here we use the library-supplied code to send compressed data to a
		* stdio stream.  You can also write your own code to do something else.
		* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
		* requires it in order to write binary files.
		*/

		//jpeg_stdio_dest(&cinfo, outfile);
		CxFileJpg dest(hFile);
		cinfo.dest = &dest;

		/* Step 3: set parameters for compression */
		/* First we supply a description of the input image.
		* Four fields of the cinfo struct must be filled in:
		*/
		cinfo.image_width = getWidth(); 	// image width and height, in pixels
		cinfo.image_height = getHeight();

		if (isGrayScale())
		{
			cinfo.input_components = 1;			// # of color components per pixel
			cinfo.in_color_space = JCS_GRAYSCALE; /* colorspace of input image */
		}
		else 
		{
			cinfo.input_components = 3; 	// # of color components per pixel
			cinfo.in_color_space = JCS_RGB; /* colorspace of input image */
		}

		/* Now use the library's routine to set default compression parameters.
		* (You must set at least cinfo.in_color_space before calling this,
		* since the defaults depend on the source color space.)
		*/
		jpeg_set_defaults(&cinfo);
		/* Now you can set any non-default parameters you wish to.
		* Here we just illustrate the use of quality (quantization table) scaling:
		*/

		uint32_t dwCodecOptions = getCodecOption(XIMAGE_FORMAT_JPG); //[nm_114]
	//#ifdef C_ARITH_CODING_SUPPORTED
		if ((dwCodecOptions & ENCODE_ARITHMETIC) != 0)
			cinfo.arith_code = TRUE;
		//#endif

		//#ifdef ENTROPY_OPT_SUPPORTED
		if ((dwCodecOptions & ENCODE_OPTIMIZE) != 0)
			cinfo.optimize_coding = TRUE;
		//#endif

		if ((dwCodecOptions & ENCODE_GRAYSCALE) != 0)
			jpeg_set_colorspace(&cinfo, JCS_GRAYSCALE);

		if ((dwCodecOptions & ENCODE_SMOOTHING) != 0)
			cinfo.smoothing_factor = m_nSmoothing;

		int nQuality = getJpegQuality(); 
		jpeg_set_quality(&cinfo, nQuality, (dwCodecOptions & ENCODE_BASELINE) != 0);

		//#ifdef C_PROGRESSIVE_SUPPORTED
		if ((dwCodecOptions & ENCODE_PROGRESSIVE) != 0)
			jpeg_simple_progression(&cinfo);
		//#endif

#ifdef C_LOSSLESS_SUPPORTED
		if ((dwCodecOptions & ENCODE_LOSSLESS) != 0)
			jpeg_simple_lossless(&cinfo, m_nPredictor, m_nPointTransform);
#endif

		//SetCodecOption(ENCODE_SUBSAMPLE_444 | GetCodecOption(CXIMAGE_FORMAT_JPG),CXIMAGE_FORMAT_JPG);

			// 2x2, 1x1, 1x1 (4:1:1) : High (default sub sampling)
		cinfo.comp_info[0].h_samp_factor = 2;
		cinfo.comp_info[0].v_samp_factor = 2;
		cinfo.comp_info[1].h_samp_factor = 1;
		cinfo.comp_info[1].v_samp_factor = 1;
		cinfo.comp_info[2].h_samp_factor = 1;
		cinfo.comp_info[2].v_samp_factor = 1;

		if ((dwCodecOptions & ENCODE_SUBSAMPLE_422) != 0)
		{
			// 2x1, 1x1, 1x1 (4:2:2) : Medium
			cinfo.comp_info[0].h_samp_factor = 2;
			cinfo.comp_info[0].v_samp_factor = 1;
			cinfo.comp_info[1].h_samp_factor = 1;
			cinfo.comp_info[1].v_samp_factor = 1;
			cinfo.comp_info[2].h_samp_factor = 1;
			cinfo.comp_info[2].v_samp_factor = 1;
		}

		if ((dwCodecOptions & ENCODE_SUBSAMPLE_444) != 0) 
		{
			// 1x1 1x1 1x1 (4:4:4) : None
			cinfo.comp_info[0].h_samp_factor = 1;
			cinfo.comp_info[0].v_samp_factor = 1;
			cinfo.comp_info[1].h_samp_factor = 1;
			cinfo.comp_info[1].v_samp_factor = 1;
			cinfo.comp_info[2].h_samp_factor = 1;
			cinfo.comp_info[2].v_samp_factor = 1;
		}

		cinfo.density_unit = 1;
		cinfo.X_density = (uint16_t)getXDPI();
		cinfo.Y_density = (uint16_t)getYDPI();

		/* Step 4: Start compressor */
		/* TRUE ensures that we will write a complete interchange-JPEG file.
		* Pass TRUE unless you are very sure of what you're doing.
		*/
		jpeg_start_compress(&cinfo, TRUE);

		/* Step 5: while (scan lines remain to be written) */
		/*           jpeg_write_scanlines(...); */
		/* Here we use the library's state variable cinfo.next_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		* To keep things simple, we pass one scanline per call; you can pass
		* more if you wish, though.
		*/
		row_stride = m_extInfo.dwEffWidth;	/* JSAMPLEs per row in image_buffer */

		//<DP> "8+row_stride" fix heap deallocation problem during debug???
		buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, 8 + row_stride, 1);

		ImageIterator iter(this);

		iter.Upset();
		while (cinfo.next_scanline < cinfo.image_height) 
		{
			// m_extInfo.nProgress = (int32_t)(100*cinfo.next_scanline/cinfo.image_height);
			iter.GetRow(buffer[0], row_stride);
			
			// not necessary if swapped red and blue definition in jmorecfg.h;ln322 <W. Morrison>
			if (m_bmpHead.biClrUsed == 0) 
			{				 // swap R & B for RGB images
				RGBtoBGR(buffer[0], row_stride); // Lance : 1998/09/01 : Bug ID: EXP-2.1.1-9
			}
		
			iter.PrevRow();
			
			(void)jpeg_write_scanlines(&cinfo, buffer, 1);
		}

		/* Step 6: Finish compression */
		jpeg_finish_compress(&cinfo);

		/* Step 7: release JPEG compression object */
		/* This is an important step since it will release a good deal of memory. */
		jpeg_destroy_compress(&cinfo);


#if CXIMAGEJPG_SUPPORT_EXIF
		if (m_exif && m_exif->m_exifinfo->IsExif) {
			// discard useless sections (if any) read from original image
			m_exif->DiscardAllButExif();
			// read new created image, to split the sections
			hFile->Seek(pos, SEEK_SET);
			m_exif->DecodeExif(hFile, EXIF_READ_IMAGE);
			// save back the image, adding EXIF section
			hFile->Seek(pos, SEEK_SET);
			m_exif->EncodeExif(hFile);
		}
#endif


		/* And we're done! */
		return true;
	}
	////////////////////////////////////////////////////////////////////////////////
#endif // CXIMAGE_SUPPORT_ENCODE

}

////////////////////////////////////////////////////////////////////////////////
#endif // CXIMAGE_SUPPORT_JPG

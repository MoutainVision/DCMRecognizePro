#pragma once

#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif


namespace avs
{
	/**
	*@brief class for describing the memory buffer
	*
	*/
	#ifndef _BUFFER_
	#define _BUFFER_
	class LIBCORE_API Buffer
	{
	private:
		unsigned char  *m_pData;
		size_t			m_nLength;

	public:
		Buffer();
		Buffer(size_t nLen);
		Buffer(const unsigned char *pBuf, size_t nLen);
		Buffer(const Buffer &img);
		Buffer(const char *szFileName);
		virtual ~Buffer();

		Buffer& operator=(const Buffer &rhs);

		void release();

		bool empty();
		bool empty() const;

		size_t getLength();
		size_t getLength() const;

		unsigned char* getBuffer();
		unsigned char* getBuffer() const;

		bool readFrom(const char *szInFile);
		bool writeTo(const char *szOutFile);


		bool create(size_t nLen);
		bool create(const unsigned char *pBuf, size_t nLen);

	public:
		static bool getFileSize(const char* szFileName, size_t &size);

	};
	#endif

	/**
	*@brief struct for describing the image buffer in compressed format
	*@param m_pBuffer	pointer to the image compressed data
	*@param m_nLength	length of the image buffer in byte
	*@note Nothing
	*@remarks Nothing
	*/
#ifndef _COMPRESSEDIMAGE_
#define _COMPRESSEDIMAGE_
	class LIBCORE_API CompressedImage
	{
	private:
		unsigned char  *m_pBuffer;
		size_t			m_nLength;

	public:
		CompressedImage();
		CompressedImage(size_t nLen);
		CompressedImage(const unsigned char *pBuf, size_t nLen);
		CompressedImage(const CompressedImage &img);
		CompressedImage(const char *szFileName);
		~CompressedImage();

		CompressedImage& operator=(const CompressedImage &rhs);

		void release();

		bool empty();
		bool empty() const;

		size_t getLength();
		size_t getLength() const;

		unsigned char* getBuffer();
		unsigned char* getBuffer() const;

		bool readFrom(const char *szInFile);

		bool create(size_t nLen);
		bool create(const unsigned char *pBuf, size_t nLen);
	};
#endif

	/**
*@brief struct for describing the image buffer in RGB format
*@param m_pBuffer pointer to the image data
*@param m_nWidth  width of the image in pixel
*@param m_nHeight height of the image in pixel
*@param m_nPitch  width of the image in byte
*@note Nothing
*@remarks Nothing
*/
#ifndef _UNCOMPRESSEDIMAGE_
#define _UNCOMPRESSEDIMAGE_
	class LIBCORE_API UncompressedImage
	{
	private:
		unsigned char  *m_pBuffer;
		int				m_nWidth;
		int				m_nHeight;
		int				m_nPitch;


	public:
		UncompressedImage();
		UncompressedImage(int nW, int nH, int nP);
		UncompressedImage(const unsigned char *pBuf, int nW, int nH, int nP);

		~UncompressedImage();

		void release();

		bool create(int nW, int nH, int nP);
		bool create(const unsigned char *pBuf, int nW, int nH, int nP);

		bool empty();

		unsigned char *getBuffer();

		int getWidth();

		int getHeight();

		int getPitch();

		size_t getBufferLength();
	};
#endif

}

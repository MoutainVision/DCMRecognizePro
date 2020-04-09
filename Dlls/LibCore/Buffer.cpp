#include "Buffer.h"

#include<cstring>
#include<fstream>

using std::fstream;
using std::ios;

namespace avs
{

	////////////////////////////////////////////////////////////////////////////////////////
	//implementation of Buffer
	////////////////////////////////////////////////////////////////////////////////////////
	Buffer::Buffer()
		: m_pData(nullptr)
		, m_nLength(0)
	{
	}

	Buffer::Buffer(size_t nLen)
	{
		if (0 == nLen)
		{
			m_nLength = 0;
			m_pData = nullptr;
		}
		else
		{
			m_pData = nullptr;
			if (nullptr != (m_pData = new unsigned char[nLen]))
			{
				m_nLength = nLen;
			}
			else
			{//out of memory
				m_nLength = 0;
			}
		}
	}

	Buffer::Buffer(const unsigned char *pBuf, size_t nLen)
	{
		if (nullptr == pBuf || 0 == nLen)
		{
			m_nLength = 0;
			m_pData = nullptr;
		}
		else
		{
			m_pData = nullptr;
			if (nullptr != (m_pData = new unsigned char[nLen]))
			{
				m_nLength = nLen;
				memcpy(m_pData, pBuf, nLen * sizeof(unsigned char));
			}
			else
			{//out of memory
				m_nLength = 0;
				m_pData = nullptr;
			}
		}
	}

	Buffer::Buffer(const Buffer &buf)
	{
		if (buf.empty())
		{
			m_pData = nullptr;
			m_nLength = 0;
		}
		else
		{
			size_t nLen = buf.getLength();

			m_pData = nullptr;
			if (nullptr == (m_pData = new unsigned char[nLen]))
			{//out of memory!!
				m_nLength = 0;
				m_pData = nullptr;
			}
			else
			{
				memcpy(m_pData, buf.getBuffer(), nLen * sizeof(unsigned char));
				m_nLength = nLen;
			}
		}
	}

	Buffer::Buffer(const char *szFileName)
	{
		m_nLength = 0;
		m_pData = nullptr;

		fstream rfile(szFileName, fstream::in | fstream::binary);
		if (rfile)
		{
			//get length of file
			rfile.seekg(0, ios::end);
			size_t nL = rfile.tellg();

			//allocate memory if necessary
			if (nL > 0)
			{
				if (nullptr != (m_pData = new unsigned char[nL]))
				{//out of memory
					m_nLength = nL;

					rfile.seekg(0, ios::beg);
					rfile.read((char*)m_pData, m_nLength);
					if (!rfile)
					{ //Error: only rfile.gcount() could be read£¡£¡
						delete[]m_pData;
						m_pData = nullptr;

						m_nLength = 0;
					}
				}
			}

			rfile.close();
		}
	}

	Buffer& Buffer::operator=(const Buffer &rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		else
		{
			release();

			if (!rhs.empty())
			{
				m_pData = nullptr;
				m_nLength = 0;

				size_t nLen = rhs.getLength();

				if (nullptr != (m_pData = new unsigned char[nLen]))
				{//out of memory 
					m_nLength = nLen;
					memcpy(m_pData, rhs.getBuffer(), m_nLength * sizeof(unsigned char));
				}
			}
		}

		return *this;
	}

	void Buffer::release()
	{
		if (nullptr != m_pData)
		{
			delete[]m_pData;
			m_pData = nullptr;
		}

		m_nLength = 0;

		return;
	}

	Buffer::~Buffer()
	{
		release();
	}

	bool Buffer::empty()
	{
		return (nullptr == m_pData || 0 == m_nLength);
	}

	bool Buffer::empty() const
	{
		return (nullptr == m_pData || 0 == m_nLength);
	}

	size_t Buffer::getLength()
	{
		return m_nLength;
	}

	size_t Buffer::getLength() const
	{
		return m_nLength;
	}

	unsigned char* Buffer::getBuffer()
	{
		return m_pData;
	}

	unsigned char* Buffer::getBuffer() const
	{
		return m_pData;
	}

	bool Buffer::readFrom(const char *szInFile)
	{
		fstream rfile(szInFile, fstream::in | fstream::binary);
		if (!rfile)
		{
			return false;
		}

		//get length of file:
		rfile.seekg(0, ios::end);
		size_t nL = rfile.tellg();
		rfile.seekg(0, ios::beg);

		//re-allocate memory if necessary
		if (nL != m_nLength)
		{
			if (nullptr != m_pData)
			{
				delete[]m_pData;
				m_pData = nullptr;
			}

			if (nL > 0)
			{
				if (nullptr == (m_pData = new unsigned char[nL]))
				{//out of memory
					m_nLength = 0;

					return false;
				}
			}

			m_nLength = nL;
		}

		if (m_nLength > 0)
		{
			//read data as a block:
			rfile.read((char*)m_pData, m_nLength);
		}

		rfile.close();

		return true;
	}


	bool Buffer::writeTo(const char *szOutFile)
	{
		//write to outfile
		fstream wfile(szOutFile, fstream::out | fstream::binary);
		if (!wfile)
		{
			return false;
		}

		if (!empty())
		{
			wfile.write((char*)m_pData, m_nLength);
		}

		//close rfile wfile
		wfile.close();

		return true;
	}


	bool Buffer::create(size_t nLen)
	{
		if (m_nLength == nLen)
		{
			return true;
		}
		else
		{
			release();

			if (nLen > 0)
			{
				if (nullptr == (m_pData = new unsigned char[nLen]))
				{//out of memory
					return false;
				}
				else
				{
					m_nLength = nLen;
				}
			}
		}

		return true;
	}

	bool Buffer::create(const unsigned char *pBuf, size_t nLen)
	{
		if (m_pData == pBuf)
		{
			if (m_nLength == nLen)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (nullptr == m_pData)
			{
				if (0 == nLen || nullptr == pBuf)
				{
					m_nLength = 0;

					return true;
				}
				else
				{
					if (nullptr == (m_pData = new unsigned char[nLen]))
					{//out of memory
						return false;
					}
					else
					{
						memcpy(m_pData, pBuf, nLen * sizeof(unsigned char));
						m_nLength = nLen;

						return true;
					}
				}
			}
			else
			{
				if (0 == nLen || nullptr == pBuf)
				{
					release();

					return true;
				}
				else
				{
					if (nLen != m_nLength)
					{
						release();
					}

					if (nullptr == (m_pData = new unsigned char[nLen]))
					{//out of memory
						return false;
					}
					else
					{
						memcpy(m_pData, pBuf, nLen * sizeof(unsigned char));
						m_nLength = nLen;

						return true;
					}
				}
			}
		}

		return false;
	}


	bool Buffer::getFileSize(const char* szFileName, size_t &size)
	{
		fstream file(szFileName, ios::in | ios::ate | ios::binary);
		if (file)
		{
			size = file.tellg();
			return true;
		}

		return false;
	}


	////////////////////////////////////////////////////////////////////////////////////////
	//implementation of CompressedImage
	////////////////////////////////////////////////////////////////////////////////////////
	CompressedImage::CompressedImage()
		: m_pBuffer(nullptr)
		, m_nLength(0)
	{
	}

	CompressedImage::CompressedImage(size_t nLen)
	{
		if (0 == nLen)
		{
			m_nLength = 0;
			m_pBuffer = nullptr;
		}
		else
		{
			m_pBuffer = nullptr;
			if (nullptr != (m_pBuffer = new unsigned char[nLen]))
			{
				m_nLength = nLen;
			}
			else
			{//out of memory
				m_nLength = 0;
			}
		}
	}

	CompressedImage::CompressedImage(const unsigned char *pBuf, size_t nLen)
	{
		if (nullptr == pBuf || 0 == nLen)
		{
			m_nLength = 0;
			m_pBuffer = nullptr;
		}
		else
		{
			m_pBuffer = nullptr;
			if (nullptr != (m_pBuffer = new unsigned char[nLen]))
			{
				m_nLength = nLen;
				memcpy(m_pBuffer, pBuf, nLen * sizeof(unsigned char));
			}
			else
			{//out of memory
				m_nLength = 0;
				m_pBuffer = nullptr;
			}
		}
	}

	CompressedImage::CompressedImage(const CompressedImage &img)
	{
		if (img.empty())
		{
			m_pBuffer = nullptr;
			m_nLength = 0;
		}
		else
		{
			size_t nLen = img.getLength();

			m_pBuffer = nullptr;
			if (nullptr == (m_pBuffer = new unsigned char[nLen]))
			{//out of memory!!
				m_nLength = 0;
				m_pBuffer = nullptr;
			}
			else
			{
				memcpy(m_pBuffer, img.getBuffer(), nLen * sizeof(unsigned char));
				m_nLength = nLen;
			}
		}
	}

	CompressedImage::CompressedImage(const char *szFileName)
	{
		m_nLength = 0;
		m_pBuffer = nullptr;

		fstream rfile(szFileName, fstream::in | fstream::binary);
		if (rfile)
		{
			//get length of file
			rfile.seekg(0, ios::end);
			size_t nL = rfile.tellg();

			//allocate memory if necessary
			if (nL > 0)
			{
				if (nullptr != (m_pBuffer = new unsigned char[nL]))
				{//out of memory
					m_nLength = nL;

					rfile.seekg(0, ios::beg);
					rfile.read((char*)m_pBuffer, m_nLength);
					if (!rfile)
					{ //Error: only rfile.gcount() could be read£¡£¡
						delete[]m_pBuffer;
						m_pBuffer = nullptr;

						m_nLength = 0;
					}
				}
			}

			rfile.close();
		}
	}

	CompressedImage& CompressedImage::operator=(const CompressedImage &rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		else
		{
			release();

			if (!rhs.empty())
			{
				m_pBuffer = nullptr;
				m_nLength = 0;

				size_t nLen = rhs.getLength();

				if (nullptr != (m_pBuffer = new unsigned char[nLen]))
				{//out of memory 
					m_nLength = nLen;
					memcpy(m_pBuffer, rhs.getBuffer(), m_nLength * sizeof(unsigned char));
				}
			}
		}

		return *this;
	}

	void CompressedImage::release()
	{
		if (nullptr != m_pBuffer)
		{
			delete[]m_pBuffer;
			m_pBuffer = nullptr;
		}

		m_nLength = 0;

		return;
	}

	CompressedImage::~CompressedImage()
	{
		release();
	}

	bool CompressedImage::empty()
	{
		return (nullptr == m_pBuffer || 0 == m_nLength);
	}

	bool CompressedImage::empty() const
	{
		return (nullptr == m_pBuffer || 0 == m_nLength);
	}

	size_t CompressedImage::getLength()
	{
		return m_nLength;
	}

	size_t CompressedImage::getLength() const
	{
		return m_nLength;
	}

	unsigned char* CompressedImage::getBuffer()
	{
		return m_pBuffer;
	}

	unsigned char* CompressedImage::getBuffer() const
	{
		return m_pBuffer;
	}

	bool CompressedImage::readFrom(const char *szInFile)
	{
		fstream rfile(szInFile, fstream::in | fstream::binary);
		if (!rfile)
		{
			return false;
		}

		//get length of file:
		rfile.seekg(0, ios::end);
		size_t nL = rfile.tellg();
		rfile.seekg(0, ios::beg);

		//re-allocate memory if necessary
		if (nL != m_nLength)
		{
			if (nullptr != m_pBuffer)
			{
				delete[]m_pBuffer;
				m_pBuffer = nullptr;
			}

			if (nL > 0)
			{
				if (nullptr == (m_pBuffer = new unsigned char[nL]))
				{//out of memory
					m_nLength = 0;

					return false;
				}
			}

			m_nLength = nL;
		}

		if (m_nLength > 0)
		{
			//read data as a block:
			rfile.read((char*)m_pBuffer, m_nLength);
		}

		rfile.close();

		return true;
	}

	bool CompressedImage::create(size_t nLen)
	{
		if (m_nLength == nLen)
		{
			return true;
		}
		else
		{
			release();

			if (nLen > 0)
			{
				if (nullptr == (m_pBuffer = new unsigned char[nLen]))
				{//out of memory
					return false;
				}
				else
				{
					m_nLength = nLen;
				}
			}
		}

		return true;
	}

	bool CompressedImage::create(const unsigned char *pBuf, size_t nLen)
	{
		if (m_pBuffer == pBuf)
		{
			if (m_nLength == nLen)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (nullptr == m_pBuffer)
			{
				if (0 == nLen || nullptr == pBuf)
				{
					m_nLength = 0;

					return true;
				}
				else
				{
					if (nullptr == (m_pBuffer = new unsigned char[nLen]))
					{//out of memory
						return false;
					}
					else
					{
						memcpy(m_pBuffer, pBuf, nLen * sizeof(unsigned char));
						m_nLength = nLen;

						return true;
					}
				}
			}
			else
			{
				if (0 == nLen || nullptr == pBuf)
				{
					release();

					return true;
				}
				else
				{
					if (nLen != m_nLength)
					{
						release();
					}

					if (nullptr == (m_pBuffer = new unsigned char[nLen]))
					{//out of memory
						return false;
					}
					else
					{
						memcpy(m_pBuffer, pBuf, nLen * sizeof(unsigned char));
						m_nLength = nLen;

						return true;
					}
				}
			}
		}

		return false;
	}




	////////////////////////////////////////////////////////////////////////////////////
	//implementation of UncompressedImage
	////////////////////////////////////////////////////////////////////////////////////
	UncompressedImage::UncompressedImage()
		: m_pBuffer(nullptr)
		, m_nWidth(0)
		, m_nHeight(0)
		, m_nPitch(0)
	{
	}

	UncompressedImage::UncompressedImage(int nW, int nH, int nP)
	{
		if (0 >= nW || nW > nP || 0 >= nH)
		{
			m_nWidth = 0;
			m_nHeight = 0;
			m_nPitch = 0;
			m_pBuffer = nullptr;
		}
		else
		{
			m_pBuffer = nullptr;
			if (nullptr == (m_pBuffer = new unsigned char[nH*nP]))
			{//out of memory
				m_nWidth = 0;
				m_nHeight = 0;
				m_nPitch = 0;
			}
			else
			{
				m_nWidth = nW;
				m_nHeight = nH;
				m_nPitch = nP;
			}
		}
	}

	UncompressedImage::UncompressedImage(const unsigned char *pBuf, int nW, int nH, int nP)
	{
		if (nullptr == pBuf || 0 >= nW || nW > nP || 0 >= nH)
		{
			m_nWidth = 0;
			m_nHeight = 0;
			m_nPitch = 0;
			m_pBuffer = nullptr;
		}
		else
		{
			m_pBuffer = nullptr;
			if (nullptr == (m_pBuffer = new unsigned char[nH*nP]))
			{//out of memory
				m_nWidth = 0;
				m_nHeight = 0;
				m_nPitch = 0;
			}
			else
			{
				m_nWidth = nW;
				m_nHeight = nH;
				m_nPitch = nP;
				memcpy(m_pBuffer, pBuf, nH*nP * sizeof(unsigned char));
			}
		}
	}

	bool UncompressedImage::create(int nW, int nH, int nP)
	{
		if (0 > nW || nW > nP || 0 > nH)
		{
			return false;
		}

		if (this->m_nWidth == nW && this->m_nHeight == nH && this->m_nPitch == nP)
		{
			return true;
		}
		else
		{
			release();

			if (0 < nW && 0 < nH)
			{
				if (nullptr == (m_pBuffer = new unsigned char[nH*nP]))
				{//out of memory
					return false;
				}
			}

			m_nWidth = nW;
			m_nHeight = nH;
			m_nPitch = nP;

			return true;
		}
	}

	bool UncompressedImage::create(const unsigned char *pBuf, int nW, int nH, int nP)
	{
		if (this->m_pBuffer == pBuf)//identity test
		{
			if (this->m_nWidth == nW && this->m_nHeight == nH && this->m_nPitch == nP)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (nullptr == pBuf)
			{
				if (0 == nW && nW == nP && 0 == nH)
				{
					release();

					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (0 >= nW && nW > nP && 0 >= nH)
				{
					return false;
				}
				else
				{
					release();

					if (nullptr == (m_pBuffer = new unsigned char[nH*nP]))
					{
						return false;
					}

					m_nWidth = nW;
					m_nHeight = nH;
					m_nPitch = nP;
					memcpy(m_pBuffer, pBuf, nH*nP * sizeof(unsigned char));

					return true;
				}
			}
		}
	}


	void UncompressedImage::release()
	{
		if (nullptr != m_pBuffer)
		{
			delete[]m_pBuffer;
			m_pBuffer = nullptr;
		}

		m_nWidth = m_nHeight = m_nPitch = 0;

		return;
	}

	UncompressedImage::~UncompressedImage()
	{
		release();
	}

	bool UncompressedImage::empty()
	{
		return (nullptr == m_pBuffer || 0 == m_nWidth || 0 == m_nHeight || 0 == m_nPitch);
	}

	int UncompressedImage::getWidth()
	{
		return m_nWidth;
	}

	int UncompressedImage::getHeight()
	{
		return m_nHeight;
	}

	int UncompressedImage::getPitch()
	{
		return m_nPitch;
	}

	unsigned char* UncompressedImage::getBuffer()
	{
		return m_pBuffer;
	}

	size_t UncompressedImage::getBufferLength()
	{
		return m_nHeight * m_nPitch;
	}

}
#include "xmemfile.h"

#include<cstring>

namespace avs
{
	//////////////////////////////////////////////////////////
	xMemFile::xMemFile( unsigned char* pBuffer,  unsigned size)
	{
		m_pBuffer = pBuffer;
		m_Position = 0;
		m_Size = m_Edge = size;
		m_bFreeOnClose = (bool)(pBuffer==0);
		m_bEOF = false;
	}
	
	//////////////////////////////////////////////////////////
	xMemFile::~xMemFile()
	{
		close();
	}
	
	//////////////////////////////////////////////////////////
	bool xMemFile::close()
	{
		if ( (m_pBuffer) && (m_bFreeOnClose) ){
			free(m_pBuffer);
			m_pBuffer = nullptr;
			m_Size = 0;
		}
		return true;
	}

	//////////////////////////////////////////////////////////
	bool xMemFile::open()
	{
		if (m_pBuffer) return false;	// Can't re-open without closing first

		m_Position = m_Size = m_Edge = 0;
		m_pBuffer=( unsigned char*)malloc(1);
		m_bFreeOnClose = true;

		return (m_pBuffer!=0);
	}

	//////////////////////////////////////////////////////////
	 unsigned char* xMemFile::getBuffer(bool bDetachBuffer)
	{
		//can only detach, avoid inadvertantly attaching to
		// memory that may not be ours [Jason De Arte]
		if( bDetachBuffer )
			m_bFreeOnClose = false;
		return m_pBuffer;
	}

	//////////////////////////////////////////////////////////
	size_t xMemFile::read(void *buffer, size_t size, size_t count)
	{
		if (buffer== nullptr) return 0;

		if (m_pBuffer== nullptr) return 0;
		if (m_Position >= (int)m_Size){
			m_bEOF = true;
			return 0;
		}

		int nCount = (int)(count*size);
		if (nCount == 0) return 0;

		int nRead;
		if (m_Position + nCount > (int)m_Size){
			m_bEOF = true;
			nRead = (m_Size - m_Position);
		} else
			nRead = nCount;

		memcpy(buffer, m_pBuffer + m_Position, nRead);
		m_Position += nRead;

		return (size_t)(nRead/size);
	}

	//////////////////////////////////////////////////////////
	size_t xMemFile::write(const void *buffer, size_t size, size_t count)
	{
		m_bEOF = false;
		if (m_pBuffer== nullptr) return 0;
		if (buffer== nullptr) return 0;

		int nCount = (int)(count*size);
		if (nCount == 0) return 0;

		if (m_Position + nCount > m_Edge){
			if (!alloc(m_Position + nCount)){
				return false;
			}
		}

		memcpy(m_pBuffer + m_Position, buffer, nCount);

		m_Position += nCount;

		if (m_Position > (int)m_Size) m_Size = m_Position;
	
		return count;
	}

	//////////////////////////////////////////////////////////
	bool xMemFile::seek(int offset, int origin)
	{
		m_bEOF = false;
		if (m_pBuffer== nullptr) return false;
		int lNewPos = m_Position;

		if (origin == SEEK_SET)		 lNewPos = offset;
		else if (origin == SEEK_CUR) lNewPos += offset;
		else if (origin == SEEK_END) lNewPos = m_Size + offset;
		else return false;

		if (lNewPos < 0) lNewPos = 0;

		m_Position = lNewPos;
		return true;
	}

	//////////////////////////////////////////////////////////
	int xMemFile::tell()
	{
		if (m_pBuffer== nullptr) return -1;
		return m_Position;
	}

	//////////////////////////////////////////////////////////
	int xMemFile::size()
	{
		if (m_pBuffer== nullptr) return -1;
		return m_Size;
	}

	//////////////////////////////////////////////////////////
	bool xMemFile::flush()
	{
		if (m_pBuffer== nullptr) return false;
		return true;
	}

	//////////////////////////////////////////////////////////
	bool xMemFile::eof()
	{
		if (m_pBuffer== nullptr) return true;
		return m_bEOF;
	}

	//////////////////////////////////////////////////////////
	int xMemFile::error()
	{
		if (m_pBuffer== nullptr) return -1;
		return (m_Position > (int)m_Size);
	}

	//////////////////////////////////////////////////////////
	bool xMemFile::putC( unsigned char c)
	{
		m_bEOF = false;
		if (m_pBuffer== nullptr) return false;

		if (m_Position >= m_Edge){
			if (!alloc(m_Position + 1)){
				return false;
			}
		}

		m_pBuffer[m_Position++] = c;

		if (m_Position > (int)m_Size) m_Size = m_Position;
	
		return true;
	}

	//////////////////////////////////////////////////////////
	int xMemFile::getC()
	{
		if (m_pBuffer== nullptr || m_Position >= (int)m_Size){
			m_bEOF = true;
			return EOF;
		}
		return *( unsigned char*)(( unsigned char*)m_pBuffer + m_Position++);
	}

	//////////////////////////////////////////////////////////
	char * xMemFile::getS(char *string, int n)
	{
		n--;
		int c,i=0;
		while (i<n){
			c = getC();
			if (c == EOF) return 0;
			string[i++] = (char)c;
			if (c == '\n') break;
		}
		string[i] = 0;
		return string;
	}

	//////////////////////////////////////////////////////////
	int	xMemFile::scanf(const char *format, void* output)
	{
		return 0;
	}

	//////////////////////////////////////////////////////////
	bool xMemFile::alloc( unsigned dwNewLen)
	{
		if (dwNewLen > ( unsigned)m_Edge)
		{
			// find new buffer size
			 unsigned dwNewBufferSize = ( unsigned)(((dwNewLen>>16)+1)<<16);

			// allocate new buffer
			if (m_pBuffer == nullptr) m_pBuffer = ( unsigned char*)malloc(dwNewBufferSize);
			else	m_pBuffer = ( unsigned char*)realloc(m_pBuffer, dwNewBufferSize);
			// I own this buffer now (caller knows nothing about it)
			m_bFreeOnClose = true;

			m_Edge = dwNewBufferSize;
		}
		return (m_pBuffer!=0);
	}

	//////////////////////////////////////////////////////////
	void xMemFile::dealloc()
	{
		close();
	}
	//////////////////////////////////////////////////////////

}


#pragma once

#include "xfile.h"

namespace avs
{
	//////////////////////////////////////////////////////////
	class LIBCORE_API  xMemFile : public xFile
	{
	public:
		xMemFile( unsigned char* pBuffer = nullptr, unsigned size = 0);
		~xMemFile();

		bool open();
		 unsigned char* getBuffer(bool bDetachBuffer = true);

		virtual bool	close();
		virtual size_t	read(void *buffer, size_t size, size_t count);
		virtual size_t	write(const void *buffer, size_t size, size_t count);
		virtual bool	seek(int offset, int origin);
		virtual int		tell();
		virtual int		size();
		virtual bool	flush();
		virtual bool	eof();
		virtual int		error();
		virtual bool	putC( unsigned char c);
		virtual int		getC();
		virtual char*	getS(char *string, int n);
		virtual int		scanf(const char *format, void* output);

	protected:
		bool	alloc(unsigned nBytes);
		void	dealloc();

		unsigned char*	m_pBuffer;
		unsigned		m_Size;
		bool			m_bFreeOnClose;
		int				m_Position;	//current position
		int				m_Edge;		//buffer size
		bool			m_bEOF;
	};


}

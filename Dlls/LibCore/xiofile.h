#pragma once

#include "xfile.h"

namespace avs
{

	class LIBCORE_API xIOFile : public xFile
	{
	public:
		xIOFile(FILE* fp = nullptr)
		{
			m_fp = fp;
			m_bCloseFile = (bool)(fp==0);
		}

		~xIOFile()
		{
			close();
		}

	//////////////////////////////////////////////////////////
		bool open(const char * filename, const char * mode)
		{
			if (m_fp) return false;	// Can't re-open without closing first

			errno_t err = fopen_s(&m_fp, filename, mode);
			if (err != 0 || !m_fp) return false;

			m_bCloseFile = true;

			return true;
		}

	//////////////////////////////////////////////////////////
		virtual bool close()
		{
			int iErr = 0;
			if ( (m_fp) && (m_bCloseFile) ){ 
				iErr = fclose(m_fp);
				m_fp = nullptr;
			}
			return (bool)(iErr==0);
		}

	//////////////////////////////////////////////////////////
		virtual size_t	read(void *buffer, size_t size, size_t count)
		{
			if (!m_fp) return 0;
			return fread(buffer, size, count, m_fp);
		}

	//////////////////////////////////////////////////////////
		virtual size_t	write(const void *buffer, size_t size, size_t count)
		{
			if (!m_fp) return 0;
			return fwrite(buffer, size, count, m_fp);
		}

	//////////////////////////////////////////////////////////
		virtual bool seek(int offset, int origin)
		{
			if (!m_fp) return false;
			return (bool)(fseek(m_fp, offset, origin) == 0);
		}

	//////////////////////////////////////////////////////////
		virtual int tell()
		{
			if (!m_fp) return 0;
			return ftell(m_fp);
		}

	//////////////////////////////////////////////////////////
		virtual int	size()
		{
			if (!m_fp) return -1;
			int pos,size;
			pos = ftell(m_fp);
			fseek(m_fp, 0, SEEK_END);
			size = ftell(m_fp);
			fseek(m_fp, pos,SEEK_SET);
			return size;
		}

	//////////////////////////////////////////////////////////
		virtual bool	flush()
		{
			if (!m_fp) return false;
			return (bool)(fflush(m_fp) == 0);
		}

	//////////////////////////////////////////////////////////
		virtual bool	eof()
		{
			if (!m_fp) return true;
			return (bool)(feof(m_fp) != 0);
		}

	//////////////////////////////////////////////////////////
		virtual int	error()
		{
			if (!m_fp) return -1;
			return ferror(m_fp);
		}

	//////////////////////////////////////////////////////////
		virtual bool putC(unsigned char c)
		{
			if (!m_fp) return false;
			return (bool)(fputc(c, m_fp) == c);
		}

	//////////////////////////////////////////////////////////
		virtual int	getC()
		{
			if (!m_fp) return EOF;
			return getc(m_fp);
		}

	//////////////////////////////////////////////////////////
		virtual char *	getS(char *string, int n)
		{
			if (!m_fp) return nullptr;
			return fgets(string,n,m_fp);
		}

	//////////////////////////////////////////////////////////
		virtual int	scanf(const char *format, void* output)
		{
			if (!m_fp) return EOF;
			return fscanf_s(m_fp, format, output);
		}

	//////////////////////////////////////////////////////////
	protected:
		FILE *m_fp;
		bool m_bCloseFile;
	};
}


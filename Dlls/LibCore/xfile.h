#pragma once

/*
 * File:	xfile.h
 * Purpose:	General Purpose File Class 
 */
/*
  --------------------------------------------------------------------------------

	COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:

	CxFile (c)  11/May/2002 Davide Pizzolato - www.xdp.it
	CxFile version 2.00 23/Aug/2002
	CxFile version 2.10 16/Dec/2007
	
	Special thanks to Chris Shearer Cooper for new features, enhancements and bugfixes

	Covered code is provided under this license on an "as is" basis, without warranty
	of any kind, either expressed or implied, including, without limitation, warranties
	that the covered code is free of defects, merchantable, fit for a particular purpose
	or non-infringing. The entire risk as to the quality and performance of the covered
	code is with you. Should any covered code prove defective in any respect, you (not
	the initial developer or any other contributor) assume the cost of any necessary
	servicing, repair or correction. This disclaimer of warranty constitutes an essential
	part of this license. No use of any covered code is authorized hereunder except under
	this disclaimer.

	Permission is hereby granted to use, copy, modify, and distribute this
	source code, or portions hereof, for any purpose, including commercial applications,
	freely and without fee, subject to the following restrictions: 

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source distribution.
  --------------------------------------------------------------------------------
 */

#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <stdlib.h>

namespace avs
{
	class LIBCORE_API xFile
	{
	public:
		xFile(void) { };
		virtual ~xFile() { };

		virtual bool	close() = 0;
		virtual size_t	read(void *buffer, size_t size, size_t count) = 0;
		virtual size_t	write(const void *buffer, size_t size, size_t count) = 0;
		virtual bool	seek(int offset, int origin) = 0;
		virtual int		tell() = 0;
		virtual int		size() = 0;
		virtual bool	flush() = 0;
		virtual bool	eof() = 0;
		virtual int		error() = 0;
		virtual bool	putC(unsigned char c)
		{
			// Default implementation
			size_t nWrote = write(&c, 1, 1);
			return (bool)(nWrote == 1);
		}
		virtual int	getC() = 0;
		virtual char *	getS(char *string, int n) = 0;
		virtual int	scanf(const char *format, void* output) = 0;
	};

}


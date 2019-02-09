#include "TextDocument.h"

TextDocument::TextDocument()
{
	buffer = nullptr;
	linebuffer = nullptr;
	length = 0;
	numlines = 0;
}


TextDocument::~TextDocument()
{
	if (buffer)
		delete buffer;

	if (linebuffer)
		delete linebuffer;
}

bool TextDocument::init(char *filename)
{
	HANDLE hFile;
	hFile = CreateFile((LPCSTR)filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	
	return init(hFile);
}

bool TextDocument::init(HANDLE hFile)
{
	ULONG numread;

	if ((length = GetFileSize(hFile, 0)) == -1)
		return false;

	if (!(buffer = new char[length])) {
		return false;
	}

	ReadFile(hFile, (LPVOID)buffer, length, &numread, 0);

	init_linebuffer();

	CloseHandle(hFile);
	return true;
}

bool TextDocument::clear()
{
	if (buffer)
	{
		delete buffer;
		buffer = 0;
		length = 0;
	}

	if (linebuffer)
	{
		delete linebuffer;
		linebuffer = 0;
		numlines = 0;
	}

	return true;
}

ULONG TextDocument::getline(ULONG lineno, char * buf, size_t len)
{
	ULONG pos = linebuffer[lineno];

	ULONG linelen = linebuffer[lineno + 1] - linebuffer[lineno];

	strncpy(buf, buffer + pos, min(linelen, len));
	return min(linelen, len);
}

ULONG TextDocument::linecount()
{
	return numlines;
}

bool TextDocument::init_linebuffer()
{
	if (!(linebuffer = new ULONG[length])) 
		return false;

	ULONG linestart = 0;

	for (ULONG i = 0; i < length; )
	{
		if (buffer[i++] == '\r')
		{
			if (buffer[i] == '\n')
			{
				i++;
			}

			linebuffer[numlines++] = linestart;
			linestart = i;
		}
	}

	if (length)
		linebuffer[numlines++] = linestart;

	linebuffer[numlines] = length;
	return true;
}

#pragma once
#include <Windows.h>

class TextDocument
{
public:
	TextDocument();
	~TextDocument();

	bool init(char *filename);
	bool init(HANDLE hFile);
	bool clear();

	ULONG getline(ULONG lineno, char *buf, size_t len);
	ULONG linecount();

private:
	bool init_linebuffer();
	char * buffer;
	ULONG *linebuffer;
	ULONG length;
	ULONG numlines;
};


#ifndef TEXTVIEW_INTERNAL_INCLUDED
#define TEXTVIEW_INTERNAL_INCLUDED

#include "TextDocument.h"
#define MAX_LINELEN 1000

class TextView
{
public:

	TextView(HWND hwnd);
	~TextView();
	HWND m_hWnd;
	int	m_nFontHeight;
	int m_nFontWidth;
	int m_nLineCount;

	int x;

	LONG OpenFile(TCHAR *szFileName);
	LONG ClearFile();

	LRESULT WINAPI OnPaint();
	void TabbedExtTextOut(HDC hdc, RECT *rect, TCHAR *buf, int len);
	void PaintLine(HDC hdc, ULONG nLineno);
	COLORREF TextView::GetTextViewColor(UINT idx);

private:
	TextDocument *m_pTextDocument;
};

#endif
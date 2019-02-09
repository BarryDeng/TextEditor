#include <Windows.h>
#include <tchar.h>
#include "TextView.h"
#include "TextViewInternal.h"

void TextView::TabbedExtTextOut(HDC hdc, RECT *rect, TCHAR *buf, int len)
{
	int  tab = 4 * m_nFontWidth;
	int  width;
	RECT fill = *rect;

	// Draw line and expand tabs
	width = TabbedTextOut(hdc, rect->left, rect->top, buf, len, 1, &tab, rect->left);

	// Erase the rest of the line with the background colour
	fill.left += LOWORD(width);
	ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &fill, 0, 0, 0);
}

void TextView::PaintLine(HDC hdc, ULONG nLineno)
{
	TCHAR buf[MAX_LINELEN];
	ULONG len;

	RECT rect;
	GetClientRect(m_hWnd, &rect);

	rect.top = nLineno * m_nFontHeight;
	rect.bottom = rect.top + m_nFontHeight;

	if (nLineno >= m_nLineCount)
	{
		SetBkColor(hdc, GetTextViewColor(HVC_BACKGROUND));
		ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, 0, 0, 0);
		return;
	}

	len = m_pTextDocument->getline(nLineno, buf, MAX_LINELEN);

	TabbedExtTextOut(hdc, &rect, buf, len);
}

//
//	Painting procedure for TextView objects
//
LRESULT WINAPI TextView::OnPaint()
{
	HDC			hdc;
	PAINTSTRUCT ps;
	RECT		rect;
	TEXTMETRIC	tm;
	char		*text = _T("Hello World!");

	HANDLE		hOldFont;
	HFONT		hFont;

	hdc = BeginPaint(m_hWnd, &ps);

	hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
	hOldFont = SelectObject(hdc, hFont);

	GetTextMetrics(hdc, &tm);

	m_nFontHeight = tm.tmHeight;
	m_nFontWidth = tm.tmAveCharWidth;

	GetClientRect(m_hWnd, &rect);

	ULONG first = ps.rcPaint.top / m_nFontHeight,
		last = ps.rcPaint.bottom / m_nFontHeight;

	for (ULONG i = first; i <= last; ++i)
	{
		PaintLine(ps.hdc, i);
	}

	// ExtTextOut(hdc, 10, 10, ETO_OPAQUE, &rect, text, lstrlen(text), 0);

	SelectObject(hdc, hOldFont);

	EndPaint(m_hWnd, &ps);

	return 0;
}

COLORREF TextView::GetTextViewColor(UINT idx)
{
	switch (idx)
	{
		case HVC_BACKGROUND: 
			return GetSysColor(COLOR_WINDOW);
		case HVC_FOREGROUND: 
			return GetSysColor(COLOR_WINDOWTEXT);
		default:			 
			return 0;
	}
}
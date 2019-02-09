#include <Windows.h>
#include <tchar.h>
#include "TextView.h"
#include "TextViewInternal.h"

LONG TextView::OpenFile(TCHAR* filename)
{
	ClearFile();

	m_pTextDocument->init(filename);
	m_nLineCount = m_pTextDocument->linecount();

	InvalidateRect(m_hWnd, NULL, FALSE);
	return TRUE;
}

LONG TextView::ClearFile()
{
	if (m_pTextDocument)
		m_pTextDocument->clear();

	m_nLineCount = m_pTextDocument->linecount();

	InvalidateRect(m_hWnd, NULL, FALSE);
	return TRUE;
}
//
//	MODULE:		TextView.cpp
//
//	PURPOSE:	Implementation of the TextView control
//
//	NOTES:		www.catch22.net
//

#include <windows.h>
#include <tchar.h>
#include "TextView.h"
#include "TextViewInternal.h"

//
//	Win32 TextView window procedure.
//
LRESULT WINAPI TextViewWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TextView *ptv = (TextView *)GetWindowLong(hwnd, 0);

	switch(msg)
	{
	// First message received by any window - make a new TextView object
	// and store pointer to it in our extra-window-bytes
	case WM_NCCREATE:

		if((ptv = new TextView(hwnd)) == 0)
			return FALSE;

		SetWindowLong(hwnd, 0, (LONG)ptv);
		return TRUE;

	// Last message received by any window - delete the TextView object
	case WM_NCDESTROY:

		delete ptv;
		return 0;

	// Draw contents of TextView whenever window needs updating
	case WM_PAINT:
		return ptv->OnPaint();

	case TXM_OPENFILE:
		return ptv->OpenFile((TCHAR *)lParam);

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//
//	Register the TextView window class
//
BOOL InitTextView()
{
	WNDCLASSEX	wcx;

	//Window class for the main application parent window
	wcx.cbSize			= sizeof(wcx);
	wcx.style			= 0;
	wcx.lpfnWndProc		= TextViewWndProc;
	wcx.cbClsExtra		= 0;
	wcx.cbWndExtra		= sizeof(TextView *);
	wcx.hInstance		= GetModuleHandle(0);
	wcx.hIcon			= 0;
	wcx.hCursor			= LoadCursor (NULL, IDC_IBEAM);
	wcx.hbrBackground	= (HBRUSH)0;		//NO FLICKERING FOR US!!
	wcx.lpszMenuName	= 0;
	wcx.lpszClassName	= TEXTVIEW_CLASS;	
	wcx.hIconSm			= 0;

	return RegisterClassEx(&wcx) ? TRUE : FALSE;
}

//
//	Create a TextView control!
//
HWND CreateTextView(HWND hwndParent)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, 
		TEXTVIEW_CLASS, _T(""), 
		WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, 
		hwndParent, 
		0, 
		GetModuleHandle(0), 
		0);
}

TextView::TextView(HWND hwnd) : m_hWnd(hwnd) 
{
	m_pTextDocument = new TextDocument();
	m_nLineCount = 0;
}

TextView::~TextView()
{
	if (m_pTextDocument)
		delete m_pTextDocument;
}
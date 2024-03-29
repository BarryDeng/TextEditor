//
//	TextView public interface - include this file
//	when you want a TextView edit control
//
#ifndef TEXTVIEW_INCLUDED
#define TEXTVIEW_INCLUDED

//
//	TextView API declared here
//
BOOL InitTextView();
HWND CreateTextView(HWND hwndParent);

//
//	TextView Window Messages defined here
//
#define TXM_BASE (WM_USER)

#define TXM_OPENFILE (TXM_BASE + 0)

#define TextView_OpenFile(hwndTV, szFile) \
	SendMessage((hwndTV), TXM_OPENFILE, 0, (LPARAM)(szFile))

//
//	TextView colours
//
#define HVC_BACKGROUND		0			// normal background colour
#define HVC_FOREGROUND		1			// normal foreground colour

#define HVC_MAX_COLOURS		2			// keep this updated!

//
//	TextView Macros defined here
//
#define TEXTVIEW_CLASS _T("TextView32")

#endif
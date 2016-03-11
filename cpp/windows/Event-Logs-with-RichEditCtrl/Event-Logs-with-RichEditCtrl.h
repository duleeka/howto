
// Event-Logs-with-RichEditCtrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CEventLogswithRichEditCtrlApp:
// See Event-Logs-with-RichEditCtrl.cpp for the implementation of this class
//

class CEventLogswithRichEditCtrlApp : public CWinApp
{
public:
	CEventLogswithRichEditCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CEventLogswithRichEditCtrlApp theApp;
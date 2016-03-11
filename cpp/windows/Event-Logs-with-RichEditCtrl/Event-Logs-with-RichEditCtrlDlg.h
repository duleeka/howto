
// Event-Logs-with-RichEditCtrlDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "RichEditEventLogger.h"

// CEventLogswithRichEditCtrlDlg dialog
class CEventLogswithRichEditCtrlDlg : public CDialogEx
{
// Construction
public:
	CEventLogswithRichEditCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EVENTLOGSWITHRICHEDITCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_EventViewer;
	RichEditEventLogger m_EventLogger;

	afx_msg void OnBnClickedBtnAddLog();
	afx_msg void OnBnClickedBtnAddLogWithData();
	afx_msg void OnBnClickedBtnClearLog();
};

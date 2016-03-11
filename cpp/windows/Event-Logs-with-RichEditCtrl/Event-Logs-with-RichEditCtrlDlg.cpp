
// Event-Logs-with-RichEditCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Event-Logs-with-RichEditCtrl.h"
#include "Event-Logs-with-RichEditCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEventLogswithRichEditCtrlDlg dialog



CEventLogswithRichEditCtrlDlg::CEventLogswithRichEditCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEventLogswithRichEditCtrlDlg::IDD, pParent),
	m_EventLogger(&m_EventViewer)
{
	m_EventLogger.SetLogLevel(Debug);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEventLogswithRichEditCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT2_EVENT_LOG, m_EventViewer);
}

BEGIN_MESSAGE_MAP(CEventLogswithRichEditCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD_LOG, &CEventLogswithRichEditCtrlDlg::OnBnClickedBtnAddLog)
	ON_BN_CLICKED(IDC_BTN_ADD_LOG_WITH_DATA, &CEventLogswithRichEditCtrlDlg::OnBnClickedBtnAddLogWithData)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LOG, &CEventLogswithRichEditCtrlDlg::OnBnClickedBtnClearLog)
END_MESSAGE_MAP()


// CEventLogswithRichEditCtrlDlg message handlers

BOOL CEventLogswithRichEditCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEventLogswithRichEditCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEventLogswithRichEditCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEventLogswithRichEditCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEventLogswithRichEditCtrlDlg::OnBnClickedBtnAddLog()
{
	m_EventLogger.AddToLog(Debug, _T("This is a sample event %08X.\n"), 10);
}

void CEventLogswithRichEditCtrlDlg::OnBnClickedBtnAddLogWithData()
{
	unsigned char data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
		0x11, 0x12 };

	m_EventLogger.AddToLog(Debug, data, sizeof(data), _T("This is a sample event with data."));
}

void CEventLogswithRichEditCtrlDlg::OnBnClickedBtnClearLog()
{
	m_EventLogger.Clear();
}

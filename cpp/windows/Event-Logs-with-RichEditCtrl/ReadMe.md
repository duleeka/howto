# Show Event Logs with Rich Edit Control 

### Prerequisites
* When RichEditCtrl is used, the [**AfxInitRichEdit2**](https://msdn.microsoft.com/en-us/library/h6hweatz.aspx) has to be invoked load the required DLLs. 
In the example, this is invoked within CEventLogswithRichEditCtrlApp::InitInstance() function in Event-Logs-with-RichEditCtrl.cpp file.

### Integraion

* Add **RichEditEventLogger.h** and **RichEditEventLogger.cpp** source files to the project.
```cpp
    #include "RichEditEventLogger.h"
```
* Add a **Rich Edit 2.0 Control** to the project
    * Set the **Multiline** property to **True**.
    * Set **Vertical Scroll** property  to **True**.
    * Set **Read Only** property to **True** to prevent user from typing or editing text in the control.
* Link the **Rich Edit 2.0 Control** with a **CRichEditCtrl** type variable. (Example: **m_EventViewer** in **CEventLogswithRichEditCtrlDlg.h**)
* Declare **RichEditEventLogger** type variable.
```
    public:
    	CRichEditCtrl m_EventViewer;
    	RichEditEventLogger m_EventLogger;
```

* When **RichEditEventLogger** is constructed, inject the declared **CRichEditCtrl**. It will be used as the user interface component for the formatted output.
* Set the Log Level (if required) to filter out entries above a specified severity.

```cpp
    CEventLogswithRichEditCtrlDlg::CEventLogswithRichEditCtrlDlg(CWnd* pParent /*=NULL*/)
    	: CDialogEx(CEventLogswithRichEditCtrlDlg::IDD, pParent),
    	m_EventLogger(&m_EventViewer)
    {
    	m_EventLogger.SetLogLevel(Debug);
    	...
    }
```
* use the functions given in **RichEditEventLogger** to set / reset the content which appears on the **Rich Edit Control**.
```cpp
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
```





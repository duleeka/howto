// RawInputTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#define WINDOW_CLASS (_T("RawInputListener"))
#define WINDOW_NAME (_T("Raw Input Listener"))
#define HARDWARE_VID (0x09DA)
#define DEVICE_USAGE_PAGE (1) //Mpuse
#define DEVICE_USAGE      (2) //Mouse

HWND hWnd = NULL;
RAWINPUTDEVICELIST rawInputDeviceList;

static void ProcessRawInputMouse(RAWINPUT * pRawInput)
{
	printf("X: %i Y:  %i\n", pRawInput->data.mouse.lLastX,
		                     pRawInput->data.mouse.lLastY);
}

static void ProcessRawInputKeyboard(RAWINPUT * pRawInput)
{
	FILE * f = fopen("a", "A");
}

static void ProcessRawInput(HRAWINPUT hRawInput)
{
	UINT iSize;
	UINT result = GetRawInputData(hRawInput, RID_INPUT, NULL, &iSize, sizeof(RAWINPUTHEADER));
	LPBYTE lpInput = new BYTE[iSize];
	result = GetRawInputData(hRawInput, RID_INPUT, lpInput, &iSize, sizeof(RAWINPUTHEADER));
	RAWINPUT * pInput = (RAWINPUT *)lpInput;

	if (rawInputDeviceList.hDevice == pInput->header.hDevice)
	{
		switch (pInput->header.dwType)
		{
		case RIM_TYPEMOUSE:
			ProcessRawInputMouse(pInput);
			break;
		case RIM_TYPEKEYBOARD:
			ProcessRawInputKeyboard(pInput);
			break;
		case RIM_TYPEHID:
			break;
		default:
			break;
		}
	}
	delete [] lpInput;
}

static LRESULT CALLBACK AppWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INPUT:
		if (wParam == RIM_INPUT)
		{   //Input occurred while the application was in the foreground.
			printf("Input occurred while the application was in the foreground.\n");			
		}
		else if (wParam == RIM_INPUTSINK)
		{ //Input occurred while the application was not in the foreground. 
			printf("Input occurred while the application was not in the foreground. \n");
		}
		ProcessRawInput((HRAWINPUT)lParam);
		/* 
		 * The application must call DefWindowProc so the system can perform cleanup.
		 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms645590(v=vs.85).aspx
		 */
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	case WM_CLOSE:	//If the window is closed, signal message loop to terminate.
		::PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return TRUE;
}


static BOOL CreateAppWindow() 
{ 
	BOOL ret = FALSE;
    WNDCLASSEX wcx; 
  
    wcx.cbSize        = sizeof(wcx);        // size of structure 
    wcx.style         = CS_OWNDC;
    wcx.lpfnWndProc   = AppWndProc;			// points to window procedure 
    wcx.cbClsExtra    = 0;					// no extra class memory 
    wcx.cbWndExtra    = 0;					// no extra window memory 
    wcx.hInstance     = NULL;				// handle to instance 
    wcx.hIcon         = NULL;
    wcx.hCursor       = NULL;               // predefined arrow 
    wcx.hbrBackground = NULL;               // white background brush 
    wcx.lpszMenuName  =  NULL;				// name of menu resource 
    wcx.lpszClassName = WINDOW_CLASS;		// name of window class 
    wcx.hIconSm       = NULL;				// small class icon 

    // Register the window class. 
    ret = (RegisterClassEx(&wcx) != 0); 
	if (ret != FALSE)
	{
		hWnd = CreateWindow( WINDOW_CLASS, 
							 WINDOW_NAME, 
							 WS_VISIBLE,	// Disable window to test background and foreground events.
							 CW_USEDEFAULT, 
							 CW_USEDEFAULT, 
							 CW_USEDEFAULT, 
							 0, NULL, NULL, NULL, NULL); 
		ret = (hWnd != NULL);
	}
	
	return ret;
} 

static void DeleteAppWindow()
{
	if (hWnd != NULL)
	{
		DestroyWindow(hWnd);
		UnregisterClass(WINDOW_CLASS, NULL);
		hWnd = NULL;
	}
}

static BOOL RegisterForRawInputs()
{
	BOOL result = FALSE;
	PRAWINPUTDEVICELIST pRawInputDeviceList = NULL;
	do
	{
		BYTE data[2048];
		UINT dataSize;
		UINT nDevices;
		TCHAR vidStr[10];
		RAWINPUTDEVICE rawInputDevice;	
		
		if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) < 0)
		{
			printf("GetRawInputDeviceList failed to get device count. Error code 0x%08X.\n", GetLastError());		
			break;
		}

		pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices);
		if (NULL == pRawInputDeviceList)
		{
			printf("Malloc failed for pRawInputDeviceList.\n");	
			break;
		}

		nDevices = GetRawInputDeviceList(pRawInputDeviceList, (PUINT)&nDevices, sizeof(RAWINPUTDEVICELIST));
		if (nDevices < 0)
		{
			printf("GetRawInputDeviceList failed to get device list. Error code 0x%08X.\n", GetLastError());	
			break;
		}

		_stprintf_s(vidStr, sizeof(vidStr) / sizeof(TCHAR), _T("%04X"), HARDWARE_VID);
		for (UINT i = 0; i < nDevices; i++)
		{
			dataSize = 0;
			GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, data, &dataSize);
			GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, data, &dataSize);
			data[dataSize] = '\0';
			if ((_tcsstr((TCHAR*)data, vidStr) > 0))
			{	
				memcpy(&rawInputDeviceList, &pRawInputDeviceList[i], sizeof(rawInputDeviceList));
				break;
			}
		}

		memset(&rawInputDevice, 0, sizeof(rawInputDevice));
		rawInputDevice.dwFlags = RIDEV_INPUTSINK;
		rawInputDevice.hwndTarget = hWnd;
	
		/* Set "Usage" and "Usage Page" for mouse
         * https://msdn.microsoft.com/en-us/library/windows/hardware/ff543477(v=vs.85).aspx
		 */
		rawInputDevice.usUsagePage = DEVICE_USAGE_PAGE;
		rawInputDevice.usUsage     = DEVICE_USAGE;

		if (RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)))
		{
			result = TRUE;
			printf("Registered for raw inputs\n");
		}
		else
		{			
			printf("Registered for raw inputs failed. Error code 0x%08X.\n", GetLastError());
		}

	} while (false);

	if (NULL != pRawInputDeviceList)
	{
		free(pRawInputDeviceList);
	}
	
	return result;
}

static BOOL UnregisterForRawInputs()
{
	RAWINPUTDEVICE rawInputDevice;
	rawInputDevice.dwFlags     = RIDEV_REMOVE;
	rawInputDevice.hwndTarget  = NULL;
	rawInputDevice.usUsagePage = DEVICE_USAGE_PAGE;
	rawInputDevice.usUsage     = DEVICE_USAGE;		
	return RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice));
} 

int _tmain(int argc, _TCHAR* argv[])
{		
	if (CreateAppWindow())
	{
		if (RegisterForRawInputs()) 
		{
			//Run the message loop for the window.
			MSG msg;
			BOOL ret;
			while (ret = GetMessage(&msg, hWnd, 0, 0))
			{	
				if (ret == -1)
				{
					//printf("Failed to retrieve message.\n");
				}
				else
				{
					TranslateMessage(&msg); 
					DispatchMessage(&msg); 
				}
			}
			UnregisterForRawInputs();
		}
		DeleteAppWindow();
	}	
	return 0;
}
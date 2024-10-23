#include <windows.h>
#include <strsafe.h>

#define WM_USER_SHELLICON (WM_USER + 1)

NOTIFYICONDATA N_ICONDATA;


void GetNotifyIconData(HWND hwnd) {
	N_ICONDATA.cbSize = sizeof(NOTIFYICONDATA);
	N_ICONDATA.hWnd = hwnd;
	N_ICONDATA.uID = 1;
	N_ICONDATA.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	N_ICONDATA.uCallbackMessage = WM_APP + 1;
	N_ICONDATA.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	StringCchCopy(N_ICONDATA.szTip, ARRAYSIZE(N_ICONDATA.szTip), TEXT("CAPS binder"));
	N_ICONDATA.uVersion = NOTIFYICON_VERSION_4;
}

void AddIconInTray(HWND hwnd)
{
	GetNotifyIconData(hwnd);
	if (!Shell_NotifyIcon(NIM_ADD, &N_ICONDATA))
	{
		MessageBox(hwnd, L"Oops, Icon was not add to tray", L"Oops", MB_OK);
		return;
	}
}

void DeleteIconFromTray() {
	Shell_NotifyIcon(NIM_DELETE, &N_ICONDATA);
}

void ShowPopupMenu(HWND hwnd)
{
	HMENU popupMenu = CreatePopupMenu();
	AppendMenu(popupMenu, MF_STRING, 10, L"Exit");

	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(hwnd);
	int cmdId = TrackPopupMenu(popupMenu, TPM_RETURNCMD | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL);

	switch (cmdId)
	{
	case 10:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	DestroyMenu(popupMenu);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_APP + 1)
	{
		if (lParam == WM_RBUTTONUP)
		{
			ShowPopupMenu(hwnd);
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
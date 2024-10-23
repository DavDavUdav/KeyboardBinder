#include "KeyboardHook.h"
#include <string>
#include <strsafe.h>
#include "WindowCreator.h"
#include "Tray.h"
#include <Windows.h>

/// <summary>
/// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
/// 
/// _In_ - обязательный входной параметр 
/// _In_opt_ - обязательный входной параметр с допусканием null
/// </summary>
/// <param name="hInstance"> - Дескриптор текущего приложения. </param>
/// <param name="hPrevInstance"> - Дескриптор предыдущего экземпляра приложения. </param>
/// <param name="lpCmdLine"> - Аргументы командной строки без приложения. </param>
/// <param name="nShowCmd"> - Управление отображением окна. </param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	const HWND hwnd = CreateMainHiddenWindow(hInstance);
	AddIconInTray(hwnd);
	SetWindowsHook(hInstance);

	MSG message;
	BOOL bRet;
	while ((bRet = GetMessage(&message,NULL, 0,0)) != 0)
	{
		if (bRet == -1)
		{

		}
		else
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	DeleteIconFromTray();
	UnsetWindowsHook();
}




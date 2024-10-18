#include <Windows.h>

// Global variable.
HHOOK KeyboardHook;


LRESULT CALLBACK LLKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
		if (p->vkCode == VK_CAPITAL && wParam == WM_KEYDOWN)
		{
			INPUT inputs[4] = {};

			inputs[0].type = INPUT_KEYBOARD;
			inputs[0].ki.wVk = VK_LWIN;

			inputs[1].type = INPUT_KEYBOARD;
			inputs[1].ki.wVk = VK_SPACE;

			inputs[2].type = INPUT_KEYBOARD;
			inputs[2].ki.wVk = VK_LWIN;
			inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

			inputs[3].type = INPUT_KEYBOARD;
			inputs[3].ki.wVk = VK_SPACE;
			inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

			SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
			return 1;
		}
	}
	// Null тк автоматически берется текущий хук.
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

/// <summary>
/// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
/// </summary>
/// <param name="hInstance"> - Дескриптор текущего приложения. </param>
/// <param name="hPrevInstance"> - Дескриптор предыдущего экземпляра приложения. </param>
/// <param name="lpCmdLine"> - Аргументы командной строки без приложения. </param>
/// <param name="nShowCmd"> - Управление отображением окна. </param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Указываем тип хука, куда передаем управление хуком, указываем инстанс приложения чтобы система знала кто ставит хук, и NULL для установки хука глобально.
	KeyboardHook = SetWindowsHookExW(WH_KEYBOARD_LL, LLKeyboardHook, hInstance, NULL);

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
	UnhookWindowsHookEx(KeyboardHook);
}
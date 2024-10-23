#include "KeyboardHook.h"
#include <string>

// Global variable.
HHOOK KeyboardHook;

void SetWindowsHook(HINSTANCE hInstance)
{
	// ”казываем тип хука, куда передаем управление хуком, указываем инстанс приложени€ чтобы система знала кто ставит хук, и NULL дл€ установки хука глобально.
	KeyboardHook = SetWindowsHookExW(WH_KEYBOARD_LL, LLKeyboardHook, hInstance, NULL);
}

void UnsetWindowsHook() 
{ 
	UnhookWindowsHookEx(KeyboardHook); 
}

LRESULT CALLBACK LLKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
		
		auto key = p->vkCode;
		
		std::wstring strValue = std::to_wstring(key);
		LPCWSTR str = strValue.c_str();

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
	// Null тк автоматически беретс€ текущий хук.
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
#include <Windows.h>
#include "Tray.h"

HWND CreateMainHiddenWindow(HINSTANCE hInstance) {
	// инициализация структуры нолями;
	WNDCLASSEX wc = {sizeof(WNDCLASSEX)};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"CapsBinderWindow";
	RegisterClassEx(&wc);
	return CreateWindowEx(0, L"CapsBinderWindow", L"Caps Binder", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
}
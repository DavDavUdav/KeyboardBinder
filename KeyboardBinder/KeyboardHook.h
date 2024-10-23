#pragma once
#include <Windows.h>

void SetWindowsHook(HINSTANCE hInstance);
void UnsetWindowsHook();

LRESULT CALLBACK LLKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);

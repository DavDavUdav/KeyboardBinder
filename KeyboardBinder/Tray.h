#pragma once
#include <Windows.h>

void AddIconInTray(HWND hwnd);
void DeleteIconFromTray();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
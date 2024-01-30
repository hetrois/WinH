#pragma once
#define WinData_Class_H
#include<string>
#include "SizeMode.h"
#include "CallbackTypes.h"

namespace WinH
{
	struct WinData
	{
		WindowSizeMode SizeMode = SmallWindow;
		ErrorCallback ErrCallback = nullptr;

		std::wstring Name = L"WinH Window";
		std::wstring ClassName = L"WinH Class Window";

		int PosX = -1, PosY = -1;
		int SizeX, SizeY;

		bool Active = false;

		bool TakeDefaultInStartup = true;

#ifdef _WINDOWS_
		HINSTANCE hInstance;
		WNDCLASSEX WC;
		HWND hwnd;
		MSG msg = { };
#endif // _WINDOWS_
	};
}

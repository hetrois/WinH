#define Win_Class_CPP

#include <Windows.h>
#include <iostream>
#include "Win.h"

LRESULT CALLBACK WindowMsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//std::wstring StrTowchar_t(const std::string& txt);
void GetError(ErrorCallback CallBack);

WinH::Win::Win(WinData& data) : Data(data)
{
    try
    {
        Data.hInstance = GetModuleHandle(0);

        Data.WC.lpfnWndProc = WindowMsgHandler;
        Data.WC.hInstance = Data.hInstance;
        Data.WC.cbSize = sizeof(&Data.WC);
        Data.WC.lpszClassName = Data.ClassName.c_str();

        auto x = RegisterClassEx(&Data.WC);

        // Create the window.
        HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            Data.ClassName.c_str(),                     // Window class
            Data.Name.c_str(),    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,       // Parent window    
            NULL,       // Menu
            Data.hInstance,  // Instance handle
            NULL        // Additional application data
        );

        if (hwnd == NULL)
        {
            GetError(Data.ErrCallback);
        }

        ShowWindow(hwnd, 5);

        // Run the message loop.


    }
    catch (char* err)
    {
        std::cout << "[ERROR] " << err;
    }
}

bool WinH::Win::GetIsWorking()
{
    return GetMessage(&Data.msg, NULL, 0, 0);
}

void WinH::Win::CheckEvents()
{
    TranslateMessage(&Data.msg);
    DispatchMessage(&Data.msg);
}

WinH::Win::~Win()
{
    DestroyWindow(Data.hwnd);
}

LRESULT CALLBACK WindowMsgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)RGB(255, 0, 0));
        COLORREF color = RGB(255, 0, 0);
        SetBkColor(hdc, color);

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void GetError(ErrorCallback CallBack)
{

    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return;
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    //std::cout << message << std::endl;

    if (!message.empty())
    {
        if (CallBack == nullptr)
        {
            throw(message);
        }
        else
        {
            CallBack(message.c_str());
        }
    }
}
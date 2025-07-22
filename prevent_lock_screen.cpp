#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Set the execution state to prevent display timeout, screensaver, and system sleep
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);

    // Create a message-only window (invisible) to keep the app running with a message loop
    // This allows the app to process messages without a visible UI
    MSG msg;
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "InvisibleWindowClass";

    if (RegisterClassEx(&wc)) {
        CreateWindowEx(0, "InvisibleWindowClass", NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
    }

    // Message loop to keep the app alive indefinitely (exit via Task Manager if needed)
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup (reset execution state on exit)
    SetThreadExecutionState(ES_CONTINUOUS);

    return 0;
}
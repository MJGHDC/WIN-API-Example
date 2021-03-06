// ListBox.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "ListBox.h"

#define ID_LISTBOX 100

HINSTANCE g_hInst;

const TCHAR *Items[] = { TEXT("Apple"),TEXT("Orange"),TEXT("Melon"),TEXT("Grape"),TEXT("Strawberry") };
HWND hList;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int i;
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | //LBS_MULTIPLESEL |
			LBS_NOTIFY, 10, 10, 100, 200, hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		for (i = 0; i<5; i++) {
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_LISTBOX:
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);
				break;
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	g_hInst = hInstance;
	wchar_t my_class_name[] = TEXT("MyListBox");
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = g_hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, TEXT("MyListBox"),
		WS_OVERLAPPEDWINDOW, 800, 300, 800, 800, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


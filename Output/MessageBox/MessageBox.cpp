// MessageBox.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MessageBox.h"
#include <assert.h>

void analyze_string(char * string)
{
	assert(string != NULL);        // Cannot be NULL  
	assert(*string != '\0');       // Cannot be empty  
	assert(strlen(string) > 2);  // Length must exceed 2  
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (MessageBox(hWnd, TEXT("에러입니다."), TEXT("에러박스"), MB_YESNO) == IDYES)
		{
			HDC hdc = GetDC(hWnd);
			char *test = nullptr;
			analyze_string(test);
			TextOut(hdc, 100, 100, TEXT("gkgk"), lstrlen(TEXT("gkgk")));
		}
		return 0;
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	TCHAR my_class_name[] = TEXT("GraphOut");

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = my_class_name;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, my_class_name, WS_OVERLAPPEDWINDOW, 800, 400, 400, 350, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);


	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
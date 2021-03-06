// Output.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GraphOut.h"

void Line(HDC h_dc, int x1, int y1, int x2, int y2)
{
	MoveToEx(h_dc, x1, y1, nullptr);
	LineTo(h_dc, x2, y2);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		HDC h_dc = GetDC(hWnd);

		
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		SetPixel(hdc, 10, 10, RGB(255, 0, 0));
		Line(hdc, 50, 50, 200, 90);
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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	WNDCLASS wc;

	TCHAR my_class_name[] = TEXT("GraphOut");
	
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OUTPUT));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = my_class_name;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, my_class_name, WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);


    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}




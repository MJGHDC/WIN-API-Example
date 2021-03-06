// Omok.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Omok.h"

//#include "gameCheckControll.h"

HINSTANCE hInst;   

int horizontalCheck(int _x, int _y, int _g_step)
{
	int x, y;
	int count;

	x = _x;
	y = _y;
	count = 0;

	while (g_dol[_y][x - 1] == _g_step && x > 0)
	{
		x--;
	}

	while (g_dol[_y][x++] == _g_step && x <= X_COUNT)
	{
		count++;
	}

	if (count == 5)
	{
		return _g_step;
	}

	return 0;
}

int verticalCheck(int _x, int _y, int _g_step)
{
	int x, y;
	int count;

	x = _x;
	y = _y;
	count = 0;

	while (g_dol[y - 1][_x] == _g_step && y > 0)
	{
		y--;
	}
	while (g_dol[y++][_x] == _g_step && y <= Y_COUNT)
	{
		count++;
	}

	if (count == 5)
	{
		return _g_step;
	}

	return 0;
}

int rightDiagonalCheck(int _x, int _y, int _g_step)
{
	int x, y;
	int count;

	x = _x;
	y = _y;
	count = 0;

	while (g_dol[y - 1][x - 1] == _g_step && x > 0 && y > 0)
	{
		y--;
		x--;
	}
	while (g_dol[y++][x++] == _g_step && x <= X_COUNT && y <= Y_COUNT)
	{
		count++;
	}

	if (count == 5)
	{
		return _g_step;
	}

	return 0;
}

int leftDiagonalCheck(int _x, int _y, int _g_step)
{
	int x, y;
	int count;

	x = _x;
	y = _y;
	count = 0;

	while (g_dol[y - 1][x + 1] == _g_step && x < X_COUNT && y > 0)
	{
		x++;
		y--;
	}
	while (g_dol[y++][x--] == _g_step && x >= 0 && y <= 18)
	{
		count++;
	}

	if (count == 5)
	{
		return _g_step;
	}

	return 0;
}
int check(int _x, int _y, int _g_step)
{
	if (horizontalCheck(_x, _y, _g_step) ||
		verticalCheck(_x, _y, _g_step) ||
		rightDiagonalCheck(_x, _y, _g_step) ||
		leftDiagonalCheck(_x, _y, _g_step))
	{
		return _g_step;
	}
	return 0;
}

void clear(HWND ah_Wnd)
{
	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			g_dol[y][x] = 0;
		}
	}
	InvalidateRect(ah_Wnd, NULL, TRUE);
}

void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(ah_wnd, &ps);

	for (int x = 0; x < X_COUNT; x++) {
		MoveToEx(hdc, XPOS(x), YPOS(0), NULL);
		LineTo(hdc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++) {
		MoveToEx(hdc, XPOS(0), YPOS(y), NULL);
		LineTo(hdc, XPOS(X_COUNT - 1), YPOS(y));
	}

	if (g_step == 0)
	{
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, 15, 15, 40, 40);
	}
	else
	{
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		Ellipse(hdc, 15, 15, 40, 40);
	}

	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			if (g_dol[y][x] > 0)
			{
				if (g_dol[y][x] == 1)
				{
					SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				}
				else
				{
					SelectObject(hdc, GetStockObject(WHITE_BRUSH));
				}
				Ellipse(hdc, XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL,
							XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL);
			}
		}
	}


	EndPaint(ah_wnd, &ps);
}

void OnLButtonDown(HWND ah_Wnd, int a_x, int a_y)
{
	int winner = 0;

	if (a_x > (XPOS(0) - HALF_INTERVAL) && 
		a_y > (YPOS(0) - HALF_INTERVAL) && 
		a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL) && 
		a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL))
	{
		int x = (a_x - START_X + HALF_INTERVAL) / INTERVAL;
		int y = (a_y - START_Y + HALF_INTERVAL) / INTERVAL;
		
		if (g_dol[y][x] == 0)
		{
			g_dol[y][x] = g_step + 1;

			InvalidateRect(ah_Wnd, NULL, TRUE);

			winner = check(x, y, g_step + 1);
			if (winner == 1)
			{
				MessageBox(ah_Wnd, TEXT("검은돌 승리"), TEXT("게임 종료"), MB_OK);
				clear(ah_Wnd);
			}
			else if (winner == 2)
			{
				MessageBox(ah_Wnd, TEXT("백돌 승리"), TEXT("게임 종료"), MB_OK);
				clear(ah_Wnd);
			}

			g_step = !g_step;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		OnLButtonDown(hWnd, x, y);
	}
	break;
	case WM_PAINT:
	{
		OnPaint(hWnd);
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

	hInst = hInstance; 

	HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OMOK));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = h_bk_brush;
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_OMOK);
	wc.lpszClassName = TEXT("Omok");

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(TEXT("Omok"), TEXT("Omok"), WS_OVERLAPPEDWINDOW,
		750, 250, 580, 630, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}




// AllocTest.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "AllocTest.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("AllocTest");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

#define MAXALLOC 10000
void *arHeap[MAXALLOC];
void *arVirt[MAXALLOC];

void DeallocAll()
{
	int i;

	SetCursor(LoadCursor(NULL, IDC_WAIT));
	for (i = 0; i<MAXALLOC; i++) {
		if (arHeap[i]) {
			HeapFree(GetProcessHeap(), 0, arHeap[i]);
			arHeap[i] = NULL;
		}
	}
	for (i = 0; i<MAXALLOC; i++) {
		if (arVirt[i]) {
			VirtualFree(arVirt[i], sizeof(int), MEM_DECOMMIT);
			VirtualFree(arVirt[i], 0, MEM_RELEASE);
			arVirt[i] = NULL;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR *Mes = TEXT("왼쪽 버튼 = 힙에서 할당, 오른쪽 버튼 = 가상 메모리에서 할당");
	int i;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		// 힙에서 할당시 : 40K만큼의 힙 소요
		DeallocAll();
		for (i = 0; i<MAXALLOC; i++) {
			arHeap[i] = HeapAlloc(GetProcessHeap(), 0, sizeof(int));
		}
		return 0;
	case WM_RBUTTONDOWN:
		// 가상 메모리에서 할당시 : 40M만큼의 가상 메모리 소요. 주소 공간은 660M 소요
		DeallocAll();
		for (i = 0; i<MAXALLOC; i++) {
			arVirt[i] = VirtualAlloc(NULL, sizeof(int), MEM_RESERVE | MEM_COMMIT,
				PAGE_READWRITE);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeallocAll();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

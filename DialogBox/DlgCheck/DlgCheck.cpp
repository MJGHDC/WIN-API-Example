// DlgCheck.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DlgCheck.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
int x;
int y;
TCHAR str[128];


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	g_hInst = hInstance;
	wchar_t my_class_name[] = L"InfoDlg";
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

	HWND hWnd = CreateWindow(my_class_name, L"InfoDlg",
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

int GetCheckedRadioButton(HWND hDlg, int First, int Last)
{
	for (int id = First; id <= Last; id++) 
	{
		if (IsDlgButtonChecked(hDlg, id) == BST_CHECKED)
		{
			return id;
		}			
	}
	return -1;
}

BOOL bMale;
enum tag_Major { MANAGE = 0, KOREAN, ENGLISH, LAW } Major;
const TCHAR *arMajor[] = { TEXT("경영학과"),TEXT("국문학과"),TEXT("영문학과"),TEXT("법학과") };
BOOL CALLBACK MajorDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_MALE, bMale ? BST_CHECKED : BST_UNCHECKED);
		CheckRadioButton(hDlg, IDC_MAJOR1, IDC_MAJOR4, IDC_MAJOR1 + Major);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			bMale = (IsDlgButtonChecked(hDlg, IDC_MALE) == BST_CHECKED);
			Major = tag_Major(GetCheckedRadioButton(hDlg, IDC_MAJOR1, IDC_MAJOR4) - IDC_MAJOR1);
			/*if (IsDlgButtonChecked(hDlg, IDC_MAJOR1) == BST_CHECKED) Major = MANAGE;
			else if (IsDlgButtonChecked(hDlg, IDC_MAJOR2) == BST_CHECKED) Major = KOREAN;
			else if (IsDlgButtonChecked(hDlg, IDC_MAJOR3) == BST_CHECKED) Major = ENGLISH;
			else if (IsDlgButtonChecked(hDlg, IDC_MAJOR4) == BST_CHECKED) Major = LAW;*/
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[128];

	switch (iMessage) {
	case WM_CREATE:
		bMale = TRUE;
		Major = KOREAN;
		return 0;
	case WM_LBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1),
			hWnd, MajorDlgProc) == IDOK) {
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		wsprintf(str, TEXT("성별 = %s"), bMale ? TEXT("남자") : TEXT("여자"));
		TextOut(hdc, 10, 10, str, lstrlen(str));
		wsprintf(str, TEXT("전공 = %s"), arMajor[Major]);
		TextOut(hdc, 10, 30, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


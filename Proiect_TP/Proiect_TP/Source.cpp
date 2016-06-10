#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#define IDM_ABOUT 1900
#define IDM_M_QUIT 1901
#define IDC_BUTTON1 1902
#define IDC_BUTTON2 1903

//Variabile globale Win32
HINSTANCE  _hinstance;
HWND tab1, tab2, tab3, tab4, tab_err;
int _ncmd;

void CreeareButoane(HWND hwnd){
	CreateWindowW(L"BUTTON", L"Generare Mesaj", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 1360, 748, 135, 30, hwnd, (HMENU)IDC_BUTTON2, GetModuleHandle(NULL), NULL);


	CreateWindowW(L"static", L"Data 1:", WS_CHILD | WS_VISIBLE, 80, 300, 58, 26, hwnd, (HMENU)1, NULL, NULL);
	tab1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 298, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	CreateWindowW(L"static", L"Data 2:", WS_CHILD | WS_VISIBLE, 80, 350, 58, 26, hwnd, (HMENU)1, NULL, NULL);
	tab2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 348, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	CreateWindowW(L"static", L"Data 3:", WS_CHILD | WS_VISIBLE, 80, 400, 58, 26, hwnd, (HMENU)1, NULL, NULL);
	tab3 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 398, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	CreateWindowW(L"static", L"Data 4:", WS_CHILD | WS_VISIBLE, 80, 450, 58, 26, hwnd, (HMENU)1, NULL, NULL);
	tab4 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 448, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);

	CreateWindowW(L"static", L"Pozitia de pe care vom corecta eroarea (0 -> 7):", WS_CHILD | WS_VISIBLE, 950, 750, 375, 26, hwnd, (HMENU)1, NULL, NULL);
	tab_err = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 1330, 750, 25, 25, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
	CreateWindowW(L"static", L"Mesajul receptionat:", WS_CHILD | WS_VISIBLE, 950, 780, 500, 26, hwnd, (HMENU)1, NULL, NULL);
}
void AdaugaImagine(HWND hwnd){
	//Fundal
	HANDLE hBitmap = LoadImageW(NULL, L"space.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HWND hsti = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, 0, 0, 1500, 843, hwnd, (HMENU)1, NULL, NULL);
	SendMessage(hsti, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	//Satelit 1
	hBitmap = LoadImageW(NULL, L"Sat1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hsti = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, 120, 450, 345, 255, hwnd, (HMENU)1, NULL, NULL);
	SendMessage(hsti, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	//Satelit 2
	hBitmap = LoadImageW(NULL, L"Sat2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hsti = CreateWindowW(L"Static", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, 1000, 430, 371, 312, hwnd, (HMENU)1, NULL, NULL);
	SendMessage(hsti, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
}
void AdaugaMeniuTab(HWND hwnd) {
	HMENU hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();
	//Creem un TabMenu
	AppendMenuW(hMenu, MF_STRING, IDM_ABOUT, L"&About");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, IDM_M_QUIT, L"&EXIT");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Referinte");
	SetMenu(hwnd, hMenubar);
}
LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//Imaginile de pe fundal
		AdaugaImagine(hwnd);
		//Tabul
		AdaugaMeniuTab(hwnd);
		//Adaugam Ferestrele de inserare
		CreeareButoane(hwnd);
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_hinstance = hInstance;
	_ncmd = nCmdShow;

	MSG Msg;
	WNDCLASSEX wc;
	//Fereastra principala
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = MainProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(NULL));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName = MAKEINTRESOURCE(NULL);
	wc.lpszClassName = "MainWnd";
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(NULL), IMAGE_ICON, 16, 16, 0);

	RegisterClassEx(&wc);
	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "MainWnd", "Codarea BCH", WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 1522, 894, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}



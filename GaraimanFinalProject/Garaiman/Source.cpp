#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

//Variabile globale Win32
HINSTANCE  _hinstance;
HWND tab1, tab2, tab3, tab4, tab_err;
int _ncmd;

//Variabile globale pentru BCH
int m = 4, n, length = 8, k, t = 1, d;
char buffer_sol[1000];
int p[21];
int alpha_to[1048576], index_of[1048576], g[548576];
int recd[1048576], bb[548576];
int numerr = 1, errpos, decerror = 0;
int data_transmisie[4];	//Datele pe care vrem sa le transmitem se vor salval in acest vector
void Initializare_BCH_criptare();


void CreeareButoane(HWND hwnd){
	CreateWindowW(L"static", L"  Transmitem un mesaj codat BCH", WS_CHILD | WS_VISIBLE, 600, 600, 275, 23, hwnd, (HMENU)1, NULL, NULL);
	CreateWindowW(L"BUTTON", L"Transmite Mesaj", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 670, 628, 150, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
	CreateWindowW(L"BUTTON", L"Generare Mesaj", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 1360, 748, 135, 30, hwnd, (HMENU)IDC_BUTTON2, GetModuleHandle(NULL), NULL);


	CreateWindowW(L"static", L"+Vom initializa un program de transmitere a unor date intre sateliti.", WS_CHILD | WS_VISIBLE, 100, 100, 528, 23, hwnd, (HMENU)1, NULL, NULL);
	CreateWindowW(L"static", L"+Pentru a genera codul receptionat alegem pozitia erorii.", WS_CHILD | WS_VISIBLE, 100, 130, 450, 23, hwnd, (HMENU)1, NULL, NULL);
	CreateWindowW(L"static", L"Introduceti datele:", WS_CHILD | WS_VISIBLE, 10, 260, 157, 25, hwnd, (HMENU)1, NULL, NULL);
	CreateWindowW(L"static", L"* (0 -> 65536)", WS_CHILD | WS_VISIBLE, 120, 498, 105, 25, hwnd, (HMENU)1, NULL, NULL);


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
		case IDC_BUTTON1:
		{
			char buf1[20], buf2[20], buf3[20], buf4[20];
			for (int i = 0; i <= 19; i++)
				buf1[i] = '\0', buf2[i] = '\0', buf3[i] = '\0', buf4[i] = '\0';
			SendMessage(tab1, WM_GETTEXT, sizeof(buf1) / sizeof(char), reinterpret_cast<LPARAM>(buf1));
			SendMessage(tab2, WM_GETTEXT, sizeof(buf2) / sizeof(char), reinterpret_cast<LPARAM>(buf2));
			SendMessage(tab3, WM_GETTEXT, sizeof(buf3) / sizeof(char), reinterpret_cast<LPARAM>(buf3));
			SendMessage(tab4, WM_GETTEXT, sizeof(buf4) / sizeof(char), reinterpret_cast<LPARAM>(buf4));
			
			data_transmisie[0] = atoi(buf1);
			data_transmisie[1] = atoi(buf2);
			data_transmisie[2] = atoi(buf3);
			data_transmisie[3] = atoi(buf4);

			//Golim datele din chenare
			DestroyWindow(tab1);
			DestroyWindow(tab2);
			DestroyWindow(tab3);
			DestroyWindow(tab4);
			tab1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 298, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			tab2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 348, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			tab3 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 398, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			tab4 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 150, 448, 66, 28, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
			
		}
			break;
		case IDC_BUTTON2:
		{
			//Alegem pozitia Erorii
			char buff[5];
			for (int i = 0; i <= 4; i++)
				buff[i]='\0';
			SendMessage(tab_err, WM_GETTEXT, sizeof(buff) / sizeof(char), reinterpret_cast<LPARAM>(buff));
			errpos = atoi(buff);

			DestroyWindow(tab_err);
			tab_err = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, 1330, 750, 25, 25, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);

			Initializare_BCH_criptare();
			//MessageBox(hwnd, buffer_sol, "Errrr", MB_ICONEXCLAMATION | MB_OK);
			CreateWindow("static", buffer_sol, WS_CHILD | WS_VISIBLE, 1150, 780, 200, 26, hwnd, (HMENU)1, NULL, NULL);
		}
			break;
		case IDM_M_QUIT:
			PostQuitMessage(0);
			break;
		case IDM_ABOUT:
			MessageBox(hwnd, "All rights reserved\n     Garaiman", "About", MB_ICONWARNING);
			break;
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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//-----------------------------
//-----------BCH---------------
//-----------------------------
//Vom alege ca valori predefinite m=4, gradul polinomului
//lenght = 8 lungimea codului
//t=1, corectam o singura eroare
//numerr=1 o singura eroare de corectat
void Declarare_Polinom()
{
	int	i, ninf;

	for (i = 1; i<m; i++)
		p[i] = 0;
	p[0] = p[m] = 1;
	//Pentru m=4 alegem forma polinomului
	p[1] = 1;

	n = 1;
	for (i = 0; i <= m; i++)
		n *= 2;

	n = n / 2 - 1;
	ninf = (n + 1) / 2 - 1;

	//Alegem lenght = 8 initializat la inceput
}
void Generare_GF()
{
	int i, mask;

	mask = 1;
	alpha_to[m] = 0;
	for (i = 0; i < m; i++) {
		alpha_to[i] = mask;
		index_of[alpha_to[i]] = i;
		if (p[i] != 0)
			alpha_to[m] ^= mask;
		mask <<= 1;
	}
	index_of[alpha_to[m]] = m;
	mask >>= 1;
	for (i = m + 1; i < n; i++) {
		if (alpha_to[i - 1] >= mask)
			alpha_to[i] = alpha_to[m] ^ ((alpha_to[i - 1] ^ mask) << 1);
		else
			alpha_to[i] = alpha_to[i - 1] << 1;
		index_of[alpha_to[i]] = i;
	}
	index_of[0] = -1;
}
void Generare_Polinom()
{
	int	ii, jj, ll, kaux;
	int	test, aux, nocycles, root, noterms, rdncy;
	int cycle[1024][21], size[1024], min[1024], zeros[1024];

	cycle[0][0] = 0;
	size[0] = 1;
	cycle[1][0] = 1;
	size[1] = 1;
	jj = 1;
	do {
		ii = 0;
		do {
			ii++;
			cycle[jj][ii] = (cycle[jj][ii - 1] * 2) % n;
			size[jj]++;
			aux = (cycle[jj][ii] * 2) % n;
		} while (aux != cycle[jj][0]);
		ll = 0;
		do {
			ll++;
			test = 0;
			for (ii = 1; ((ii <= jj) && (!test)); ii++)
				for (kaux = 0; ((kaux < size[ii]) && (!test)); kaux++)
					if (ll == cycle[ii][kaux])
						test = 1;
		} while ((test) && (ll < (n - 1)));
		if (!(test)) {
			jj++;
			cycle[jj][0] = ll;
			size[jj] = 1;
		}
	} while (ll < (n - 1));
	nocycles = jj;

	//Capacitatea de corectare a erorii e de o eroare

	d = 2 * t + 1;

	kaux = 0;
	rdncy = 0;
	for (ii = 1; ii <= nocycles; ii++) {
		min[kaux] = 0;
		test = 0;
		for (jj = 0; ((jj < size[ii]) && (!test)); jj++)
			for (root = 1; ((root < d) && (!test)); root++)
				if (root == cycle[ii][jj])  {
			test = 1;
			min[kaux] = ii;
				}
		if (min[kaux]) {
			rdncy += size[min[kaux]];
			kaux++;
		}
	}
	noterms = kaux;
	kaux = 1;
	for (ii = 0; ii < noterms; ii++)
		for (jj = 0; jj < size[min[ii]]; jj++) {
		zeros[kaux] = cycle[min[ii]][jj];
		kaux++;
		}

	k = length - rdncy;//Mereu va fi 4 pentru valorile prestabilite

	g[0] = alpha_to[zeros[1]];
	g[1] = 1;
	for (ii = 2; ii <= rdncy; ii++) {
		g[ii] = 1;
		for (jj = ii - 1; jj > 0; jj--)
			if (g[jj] != 0)
				g[jj] = g[jj - 1] ^ alpha_to[(index_of[g[jj]] + zeros[ii]) % n];
			else
				g[jj] = g[jj - 1];
		g[0] = alpha_to[(index_of[g[0]] + zeros[ii]) % n];
	}
}
void Codare_BCH()
{
	int i, j;
	int feedback;

	for (i = 0; i < length - k; i++)
		bb[i] = 0;
	for (i = k - 1; i >= 0; i--) {
		feedback = data_transmisie[i] ^ bb[length - k - 1];
		if (feedback != 0) {
			for (j = length - k - 1; j > 0; j--)
				if (g[j] != 0)
					bb[j] = bb[j - 1] ^ feedback;
				else
					bb[j] = bb[j - 1];
			bb[0] = g[0] && feedback;
		}
		else {
			for (j = length - k - 1; j > 0; j--)
				bb[j] = bb[j - 1];
			bb[0] = 0;
		}
	}
}
void Initializare_BCH_criptare()
{
	int i;

	Declarare_Polinom();
	Generare_GF();
	Generare_Polinom();

	/*for (i = 0; i < k; i++)
	{
		printf("\n Enter the data[%d]: ", i + 1);
		scanf("%d", &data_transmisie[i]);
	}*/
	Codare_BCH();

	for (i = 0; i < length - k; i++)
		recd[i] = bb[i];
	for (i = 0; i < k; i++)
		recd[i + length - k] = data_transmisie[i];
	/*printf("Code polynomial:\nc(x) = ");
	for (i = 0; i < length; i++) {
		printf("%1d", recd[i]);
		if (i && ((i % 50) == 0))
			printf("\n");
	}
	printf("\n");*/

	//Avem o singur eroare de corectat numerr=1
	//printf("Enter error locations (integers between");
	//printf(" 0 and %d): ", length - 1);


	//!!!!!!!!!!!
	//errpos = 1;

	if (numerr)
			recd[errpos] ^= 1;

	//printf("r(x) = ");
	for (int kl = 0; kl < 999; kl++)
		buffer_sol[kl] = '\0';
	for (i = 0; i < length; i++) 
		sprintf(buffer_sol,"%s%d",buffer_sol, recd[i]);
}
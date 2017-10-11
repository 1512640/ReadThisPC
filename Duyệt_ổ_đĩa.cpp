// Duyệt_ổ_đĩa.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <CommCtrl.h>
#include <shellapi.h>
#include <time.h>
#include "resource.h"
#pragma comment(lib, "comctl32.lib")
#include "Duyệt_ổ_đĩa.h"

#define ID_cay 333
#define ID_list 777
#define MAX_LOADSTRING 100
void Add_List(WCHAR* s, WCHAR *duongDan, int cap);
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DUYT__A, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DUYT__A));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DUYT__A));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DUYT__A);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
HWND tree;
HWND list;
WCHAR* lay_thoi_gian(WIN32_FIND_DATA f32)
{
	ULARGE_INTEGER ula;
	FILETIME  a = f32.ftLastWriteTime;
	ula.LowPart = a.dwLowDateTime;
	ula.HighPart = a.dwHighDateTime;
	time_t baygio = ula.QuadPart / 10000000ULL - 11644473600ULL;
	time_t k = time(NULL);
	tm *ltm = localtime( &baygio);
	WCHAR* tam = new WCHAR[50];
	wsprintf(tam, L"%d/%d/%d %d:%d", ltm->tm_mday, ltm->tm_mon, ltm->tm_year + 1900, ltm->tm_min, ltm->tm_hour);*/
	return NULL;
}

void list_thu_muc(WCHAR* cha)
{
	WIN32_FIND_DATA f32;
	WCHAR thuMuc[MAX_PATH];
	int cap=0;
	wsprintf(thuMuc, L"%s\\*.*", cha);
	HANDLE tim = FindFirstFile(thuMuc, &f32);
	if (tim != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((f32.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == false)
			{
				if (wcscmp(f32.cFileName, L".") && wcscmp(f32.cFileName, L".."))
				{
					WCHAR *duongDan = new WCHAR [100];
					wsprintf(duongDan, L"%s\\%s", cha, f32.cFileName);
					
					Add_List(f32.cFileName, duongDan, cap,lay_thoi_gian(f32));
					cap++;
				}
			}
		} while (FindNextFile(tim, &f32));
		FindClose(tim);
	}
}
void Add_List(WCHAR* s, WCHAR *duongDan, int cap, WCHAR* thoigian)
{
	LVITEM cot = { 0 };
	cot.cchTextMax = 50;
	//cot.iImage = 0;
	cot.iItem = cap;
	//cot.iSubItem = 0;
	cot.lParam = (LPARAM)duongDan;
	cot.pszText = s;
	cot.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	ListView_InsertItem(list, &cot);
	ListView_SetItemText (list, cap, 1, thoigian);
}
void Add_tree(WCHAR* s, int cap, WCHAR* duongDan)
{
	static HTREEITEM h[100];
	static HTREEITEM truoc = TVI_FIRST;
	InitCommonControls();
	TVINSERTSTRUCT tv;
	if (cap == 1)
	{
		tv.hParent = TVI_ROOT;
	}
	else 
	{
		tv.hParent = h[cap - 1];
	}
	tv.hInsertAfter = truoc;
	tv.item.cchTextMax = 50;
	tv.item.pszText = s;
	tv.item.iImage = 0;
	tv.item.iSelectedImage = 0;
	tv.item.lParam = (LPARAM)duongDan;
	tv.item.mask = TVIF_IMAGE | TVM_SELECTITEM | TVIF_TEXT | TVIF_PARAM;
	truoc = (HTREEITEM)SendMessage(tree, TVM_INSERTITEM, 0,(LPARAM) &tv);
	h[cap] = truoc;
}
void thu_muc(WCHAR *goc, int cap)
{
	WIN32_FIND_DATA f32;
	WCHAR thuMuc[MAX_PATH];
	cap++;
	wsprintf(thuMuc, L"%s\\*.*", goc);
	HANDLE tim = FindFirstFile(thuMuc, &f32);
	if (tim != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (f32.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (wcscmp(f32.cFileName, L".") && wcscmp(f32.cFileName, L".."))
				{
					WCHAR con[MAX_PATH];
					wsprintf(con,L"%s\\%s" ,goc, f32.cFileName);
					Add_tree(f32.cFileName, cap, con);
					thu_muc(con, cap);
				}
			}
			else
			{
				WCHAR ten[1000];
				ten[wcslen(goc)] = '\0';
				wsprintf(ten, L"%s\\%s", goc, f32.cFileName);
				Add_tree(f32.cFileName, cap, ten);
			}
		} while (FindNextFile(tim, &f32));
		FindClose(tim);
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static HIMAGELIST himl;
	RECT rect;
	HBITMAP bitmap;
	GetClientRect(hWnd, &rect);
	switch (message)
	{
	case WM_SIZE:
		//GetClientRect(hWnd, &rect);
		/*tree = CreateWindow(WC_TREEVIEW, 0, WS_VISIBLE | WS_CHILD | WS_BORDER |
			WS_HSCROLL | ES_AUTOHSCROLL | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
			0, 0, rect.right * 3 / 10, rect.bottom, hWnd, 0, 0, 0);*/
		break;
	case WM_CREATE:
	{
		InitCommonControls();
		tree = CreateWindow(WC_TREEVIEW, 0, WS_VISIBLE | WS_CHILD | WS_BORDER |
			 TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
			0, 0, rect.right * 3 / 10, rect.bottom, hWnd, (HMENU)ID_cay, 0, 0);
	//	HIMAGELIST hImage = ImageList_Create(16, 16, ILC_COLOR16, 2, 10);
	//	bitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	//	ImageList_Add(hImage, bitmap, NULL);
	//	SendMessage(tree, TVM_SETIMAGELIST, 0, (LPARAM)hImage);
		Add_tree(L"D:", 1, L"D:");
		thu_muc(L"D:", 1);
		list = CreateWindow(WC_LISTVIEW, 0,LVS_REPORT| WS_VISIBLE | WS_CHILD | WS_BORDER ,
			rect.left+rect.right*3/10, 0,rect.right*7/10 , rect.bottom, hWnd, (HMENU)ID_list, 0, 0);
		LVCOLUMN cot;
		cot.cchTextMax = 50;
		cot.pszText = L"NAME";
		cot.cx = 200;
		cot.iSubItem = 0;
		cot.mask = LVCF_FMT | LVCF_TEXT |LVCF_WIDTH;
		cot.fmt = LVCFMT_LEFT;
		ListView_InsertColumn(list, 0, &cot);

		cot.pszText = L"DATE";
		cot.cx = 100;
		ListView_InsertColumn(list, 1, &cot);

		cot.pszText = L"TYPE";
		cot.cx = 100;
		ListView_InsertColumn(list, 2, &cot);

		cot.pszText = L"SIZE";
		cot.cx = 100;
		ListView_InsertColumn(list, 3, &cot);
		Add_List(L"D:", L"D:", 0,L"");
		//Add_List(L"TUAN 1", 0, 1);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
	{	
		if (wParam == ID_cay)
		{
			if (((LPNMHDR)lParam)->code == NM_DBLCLK)
			{
				WCHAR A[100];
				TVITEM HTREE;
				HTREE.cchTextMax = 100;
				HTREE.hItem = TreeView_GetSelection(tree);
				HTREE.pszText = A;
				HTREE.mask = TVIF_TEXT;
				SendMessage(tree, TVM_GETITEM, 0, (LPARAM)&HTREE);
				MessageBoxW(0, HTREE.pszText, 0, 0); //ten anh
			}
		}
		if (wParam == ID_list)
		{
			if (((LPNMHDR)lParam)->code == NM_DBLCLK)
			{
				LVITEM l;
				l.iItem = ListView_GetNextItem(list, -1, LVNI_SELECTED);
				ListView_GetItem(list, &l);
				//MessageBoxW(0,(WCHAR *) l.lParam, 0, 0); //ten anh
				list_thu_muc((WCHAR*)l.lParam);
			}
		}
	}
	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


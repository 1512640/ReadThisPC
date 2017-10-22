// Duyệt_ổ_đĩa.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include <CommCtrl.h>
#include <time.h>
#include "resource.h"
#include "1512640.h"

#include <Windows.h>
#include <Shobjidl.h>
#include <Shellapi.h>
#include <shlwapi.h>
#include <Shlobj.h>


#pragma comment(lib, "comctl32.lib")
#pragma comment (lib,"Shell32.lib")
#pragma comment(lib, "shlwapi.lib")
#define ENTIRE_STRING NULL
#define ID_cay 333
#define ID_list 777
#define MAX_LOADSTRING 100
#define KB 1
#define MB 2
#define GB 3
#define TB 4
#define RADIX 10
void Add_tree(WCHAR* s, int cap, WCHAR* duongDan);
void Add_List(WCHAR* s, WCHAR *duongDan, int cap, WCHAR* thoigian,WCHAR* kichthuoc,WCHAR* loai);
void list_thu_muc(WCHAR* cha);
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND tree;
HWND list;
HWND head;
HWND status;
int wtree = 222;
int xbatdau;
bool check = FALSE;
HIMAGELIST hImage;
HIMAGELIST hil;
static WCHAR* B = new WCHAR[100];												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DuyetFile(LPSHELLFOLDER cha, LPITEMIDLIST condautien, int dem, int cap)
{
	//if (dem == 6) return;
	LPSHELLFOLDER con = NULL;
	cha->BindToObject(condautien, NULL, IID_IShellFolder, (LPVOID*)&con);// ép thành cha
	if (con == NULL)
		return;
	LPENUMIDLIST danhsach = NULL;
	HRESULT hr = con->EnumObjects(NULL, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS, &danhsach);
	if (danhsach == NULL)
		return;
	LPITEMIDLIST dungdeduyet = NULL;
	cap++;
	while (1)
	{
		hr = danhsach->Next(1, &dungdeduyet, NULL);
		if (hr != S_OK)
			break;
		WCHAR chuoi[1000];
		chuoi[0] = 0;
		WCHAR chuoitenfile[1000];
		STRRET xuat;
		con->GetDisplayNameOf(dungdeduyet, SHGDN_NORMAL, &xuat);

		StrRetToBuf(&xuat, dungdeduyet, chuoitenfile, 1000);
		wcscat(chuoi, chuoitenfile);
		if (wcscmp(chuoi, L"") != 0)
		{
			//wprintf(L"  %s\n", chuoi);
			Add_tree(chuoi, cap, L" ");
		}
		DuyetFile(con, dungdeduyet, dem+1 ,cap);
	}
}
void DuyetDestop()
{
	//wsprintf(L"ThisPC: \n",L" ",0);
	LPSHELLFOLDER destop;
	SHGetDesktopFolder(&destop);
	LPENUMIDLIST tam = NULL;
	destop->EnumObjects(NULL, SHCONTF_FOLDERS, &tam);
	LPITEMIDLIST duyet = NULL;
	HRESULT hr = NULL;
	int dem = 0;
	//do
	{
		hr = tam->Next(1, &duyet, NULL);
		WCHAR *chuoi = new WCHAR[255];
		chuoi[0] = 0;
		STRRET xuat;
		destop->GetDisplayNameOf(duyet, SHGDN_NORMAL, &xuat);
		StrRetToBuf(&xuat, duyet, chuoi, 255);
		Add_tree(chuoi, 1, L" "); //Them vao tree
		if (wcscmp(chuoi, L"") != 0)
		{
			//if (dem == 0)
			{
				dem++;
				DuyetFile(destop, duyet, 0 ,1);			
			}
		}
	} //while (hr == S_OK);
	 
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	
	// Initialize global strings
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DUYT__A);
	wcex.lpszClassName = L"FILE";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(L"FILE",L"Đọc ổ đĩa", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
LPWSTR Loai(const WIN32_FIND_DATA &fd)
{
	int nDotPos = StrRStrI(fd.cFileName, ENTIRE_STRING, _T(".")) - fd.cFileName;
	int len = wcslen(fd.cFileName);

	if (nDotPos < 0 || nDotPos >= len) //Nếu không tìm thấy
		return _T("");

	TCHAR *szExtension = new TCHAR[len - nDotPos + 1];
	int i;

	for (i = nDotPos; i < len; ++i)
		szExtension[i - nDotPos] = fd.cFileName[i];
	szExtension[i - nDotPos] = NULL; //Kí tự kết thúc chuỗi

	if (!StrCmpI(szExtension, _T(".htm")) || !StrCmpI(szExtension, _T(".html")))
	{
		return _T("Web page");
	}
	TCHAR pszOut[256];
	HKEY hKey;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 256;

	//Kiếm handle của extension tương ứng trong registry
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, szExtension, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("");
	}

	if (RegQueryValueEx(hKey, NULL, NULL, &dwType, (PBYTE)pszOut, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("");
	}
	RegCloseKey(hKey);

	//Kiếm mô tả về thông tin của extension thông qua handle của key tương ứng trong registry
	TCHAR *pszPath = new TCHAR[1000];
	dwSize = 1000;
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, pszOut, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("");
	}

	if (RegQueryValueEx(hKey, NULL, NULL, &dwType, (PBYTE)pszPath, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("");
	}
	RegCloseKey(hKey);

	return pszPath;
}
LPWSTR kich_thuoc( const WIN32_FIND_DATA &f32)
{
	DWORD nSize = f32.nFileSizeLow;
	int nType = 0; //Bytes

	while (nSize >= 1048576) //
	{
		nSize /= 1024;
		++nType;
	}

	__int64 nRight;

	if (nSize >= 1024)
	{
		//Lấy một chữ số sau thập phân của nSize chứa trong nRight
		nRight = nSize % 1024;

		while (nRight > 99)
			nRight /= 10;

		nSize /= 1024;
		++nType;
	}
	else
		nRight = 0;

	TCHAR *buffer = new TCHAR[11];
	buffer[0] = '\0';
	if (nSize != 0) _itow_s(nSize, buffer, 11, RADIX);
	if (nRight != 0 && nType > KB)
	{
		StrCat(buffer, _T("."));
		TCHAR *right = new TCHAR[3];
		_itow_s(nRight, right, 3, RADIX);
		StrCat(buffer, right);
	}
	if (nSize != 0)
	{
		switch (nType)
		{
		case 0://Bytes
			StrCat(buffer, _T(" bytes"));
			break;
		case KB:
			StrCat(buffer, _T(" KB"));
			break;
		case MB:
			StrCat(buffer, _T(" MB"));
			break;
		case GB:
			StrCat(buffer, _T(" GB"));
			break;
		case TB:
			StrCat(buffer, _T(" TB"));
			break;
		}
	}
	return buffer;
}
void Mo_file(WCHAR* kt)
{
	WIN32_FIND_DATA f32;
	GetFileAttributesEx(kt, GetFileExInfoStandard, &f32);
	if (f32.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		ListView_DeleteAllItems(list);
		list_thu_muc(kt);
		return;
	}
	
	ShellExecute(NULL, L"open", kt, NULL, NULL, SW_SHOWNORMAL);
}
WCHAR* lay_thoi_gian(WIN32_FIND_DATA f32)
{
	ULARGE_INTEGER ula;
	FILETIME  a = f32.ftLastWriteTime;
	ula.LowPart = a.dwLowDateTime;
	ula.HighPart = a.dwHighDateTime;
	time_t baygio = ula.QuadPart / 10000000ULL - 11644473600ULL;
	time_t k = time(NULL);
	tm *ltm = localtime(&baygio);
	WCHAR* tam = new WCHAR[50];
	wsprintf(tam, L"%d/%d/%d %d:%d", ltm->tm_mday, ltm->tm_mon, ltm->tm_year + 1900, ltm->tm_min, ltm->tm_hour);
	return tam;
}
void list_thu_muc(WCHAR* cha)
{
	WIN32_FIND_DATA f32;
	WCHAR thuMuc[MAX_PATH];
	int cap = 0;
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
					WCHAR *duongDan = new WCHAR[100];
					wsprintf(duongDan, L"%s\\%s", cha, f32.cFileName);
					Add_List(f32.cFileName, duongDan, cap, lay_thoi_gian(f32),kich_thuoc(f32),Loai(f32));
					cap++;
				}
			}
		} while (FindNextFile(tim, &f32));
		FindClose(tim);
	}
}
void Add_List(WCHAR* s, WCHAR *duongDan, int cap, WCHAR * thoigian,WCHAR* kichthuoc,WCHAR* loai)
{
	LVITEM cot = { 0 };
	cot.cchTextMax = 100;
	cot.iItem = cap;
	cot.lParam = (LPARAM)duongDan;
	cot.pszText = s;
	cot.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	ListView_InsertItem(list, &cot);
	ListView_SetItemText(list, cap, 1,thoigian);
	ListView_SetItemText(list, cap, 3, kichthuoc);
	ListView_SetItemText(list, cap, 2, loai);
}
void Add_tree(WCHAR* s, int cap, WCHAR* duongDan)
{
	static HTREEITEM h[100];
	static HTREEITEM truoc = TVI_FIRST;
	InitCommonControls();
	TVINSERTSTRUCT tv;
	if (cap == 0)
	{
		tv.hParent = TVI_ROOT;
	}
	else
	{
		tv.hParent = h[cap - 1];
	}
	tv.hInsertAfter = truoc;
	tv.item.cchTextMax = 100;
	tv.item.pszText = s;
	tv.item.iImage = 0;
	tv.item.iSelectedImage = 0;
	tv.item.lParam = (LPARAM)duongDan;
	tv.item.mask = TVIF_IMAGE  | TVIF_TEXT | TVIF_PARAM;
	truoc = (HTREEITEM)SendMessage(tree, TVM_INSERTITEM, 0, (LPARAM)&tv);
	h[cap] = truoc;
}
void thu_muc(WCHAR *goc, int cap)
{
	WIN32_FIND_DATA f32;
	WCHAR thuMuc[MAX_PATH];
	cap++;
	int dem = 0;
	wsprintf(thuMuc, L"%s\\*.*", goc);
	HANDLE tim = FindFirstFile(thuMuc, &f32);
	if (tim != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((f32.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == false) // an thung rac
			{
				if (f32.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (wcscmp(f32.cFileName, L".") && wcscmp(f32.cFileName, L".."))
					{
						WCHAR* con = new WCHAR[MAX_PATH];
						wsprintf(con, L"%s\\%s", goc, f32.cFileName);
						Add_tree(f32.cFileName, cap, con);
						thu_muc(con, cap);
					}
				}
			}
		} while (FindNextFile(tim, &f32));
		FindClose(tim);
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	RECT rect;
	HBITMAP bitmap;
	B[0] = '\0';
	GetClientRect(hWnd, &rect);
	char temp[100];
	int test = GetLogicalDriveStrings(100, (LPWSTR)temp);
	if (test == 0) 
		MessageBox(hWnd, L"Khong tim thay o dia nao", L"Error", MB_OK | MB_ICONERROR);
	int i = 0;
	int cap = 1;
	
	switch (message)
	{
	
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		MoveWindow(tree, 3, 30, wtree,rect.bottom -80,1);
		MoveWindow(list, wtree + 7, 30, rect.right - wtree - 13, rect.bottom - 80, 1);
		MoveWindow(status, 3, rect.bottom - 20, rect.right - 3, 40, 1);
		MoveWindow(head, wtree + 7, 0, rect.right - wtree - 13, 30, 1);
		break;
	case WM_CREATE:
	{
		InitCommonControls();
		tree = CreateWindow(WC_TREEVIEW, 0, WS_VISIBLE | WS_CHILD | WS_BORDER |
			TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
			0, 0, 200, 400, hWnd, (HMENU)ID_cay, 0, 0);

		
		list = CreateWindow(WC_LISTVIEW, 0, LVS_REPORT | WS_VISIBLE | WS_CHILD | WS_BORDER|LVS_ICON ,
			200,0,300,400, hWnd, (HMENU)ID_list, 0, 0);
	

		status = CreateWindow(STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, hWnd,NULL, hInst, NULL);
		int size[] = { 200,400,600,-1 };
		SendMessage(status, SB_SETPARTS, 4, (LPARAM)&size);
		SendMessage(status, SB_SETMINHEIGHT, 40, 0);
		
		head =  CreateWindow(WC_EDIT, L"",  WS_VISIBLE | WS_CHILD|WS_BORDER ,
								0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		//Insert photo
		hImage = ImageList_Create(20, 20, ILC_COLOR16, 2, 10);
		bitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		ImageList_Add(hImage, bitmap, NULL);
		SendMessage(tree, TVM_SETIMAGELIST, 0, (LPARAM)hImage);
	
		
		Add_tree(L"PC", 0, L"PC ");
		thu_muc(L"PC", 0);
		 
		do  //duyet o dia
		{
			WCHAR* dia = new WCHAR[100];
			dia[0] = temp[i];
			dia[1] = ':';
			dia[2] = '\0';
			Add_tree(dia, cap, dia);
			thu_muc(dia, cap);
			Add_List(dia, dia, 0, L"", L"", L"");
			i = i + 8;
		} while (temp[i] != NULL);

		LVCOLUMN cot;
		cot.cchTextMax = 100;
		cot.pszText = L"TÊN";
		cot.cx = 200;
		cot.iSubItem = 0;
		cot.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		cot.fmt = LVCFMT_LEFT;
		ListView_InsertColumn(list, 0, &cot);

		cot.pszText = L"NGÀY";
		cot.cx = 200;
		ListView_InsertColumn(list, 1, &cot);

		cot.pszText = L"LOẠI";
		cot.cx = 150;
		ListView_InsertColumn(list, 2, &cot);

		cot.pszText = L"KÍCH THƯỚC";
		cot.cx = rect.right -13-550-wtree;
		ListView_InsertColumn(list, 3, &cot);
		break;
	}
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (x >= wtree  && x <= wtree + 10);
		{
			SetCursor(LoadCursor(NULL,IDC_SIZEWE));
		}
		if (check == true)
		{
			wtree = wtree + x - xbatdau;
			SendMessage(hWnd, WM_SIZE, 0, 0);
		}
		xbatdau = x;
		break;
	}
	case WM_LBUTTONDOWN:
	{
	
		xbatdau = LOWORD(lParam);
		if (xbatdau >= wtree - 10 && xbatdau <= wtree + 5)
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			check = true;
			SetCapture(hWnd);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		check = false;
		ReleaseCapture();
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
				WCHAR* A = new WCHAR[100];
				TVITEM HTREE;
				HTREE.cchTextMax = 100;
				HTREEITEM a = (HTREEITEM)TreeView_GetSelection(tree);
				if (a == NULL) break;
				HTREE.hItem = a;
				HTREE.pszText = A;
				HTREE.mask = TVIF_TEXT;
				SendMessage(tree, TVM_GETITEM, 0, (LPARAM)&HTREE);
				ListView_DeleteAllItems(list);
				list_thu_muc((LPWSTR)HTREE.lParam);
			}
			break;
		}
		if (wParam == ID_list)
		{
			if (((LPNMHDR)lParam)->code == NM_DBLCLK)
			{
				LVITEM l;
				l.iItem = ListView_GetNextItem(list, -1, LVNI_SELECTED);
				if (l.iItem >= 0)
				{
					ListView_GetItem(list, &l);
					Mo_file((WCHAR*)l.lParam);
				}
				break;
			}
			if (((LPNMHDR)lParam)->code == NM_CLICK)
			{
				LVITEM l;
				l.iItem = ListView_GetNextItem(list, -1, LVNI_SELECTED);
				if (l.iItem >= 0)
				{
					WIN32_FIND_DATA f;
					ListView_GetItem(list, &l);
					SendMessage(head, WM_SETTEXT, 0, (LPARAM)l.lParam);
					WCHAR thuMuc[MAX_PATH];
					HANDLE tim = FindFirstFile((LPWSTR)l.lParam, &f);
					if (tim != INVALID_HANDLE_VALUE)
					{
						WORD a;
						FindNextFile(tim, &f);
						//Ghi vao thanh status bar
						SendMessage(status, SB_SETICON, 0, (LPARAM)ExtractAssociatedIconW(hInst, (LPWSTR)l.lParam, &a));
						SendMessage(status, SB_SETTEXT, 1, (LPARAM)f.cFileName);
						SendMessage(status, SB_SETTEXT, 2, (LPARAM)kich_thuoc(f));
					}
				}
			}
			break;
		}
	}
	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


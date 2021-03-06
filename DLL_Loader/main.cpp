#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Windowsx.h>
#include <Commctrl.h>
#include <Shlwapi.h>
#include <tlhelp32.h>
#include <Gdiplus.h>
#include <psapi.h>
#include "SQLite/sqlite3.h"
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Psapi.lib")
//using namespace Gdiplus;

LCID UserLanguage;
int __stdcall BuildDevicesList(HWND hWnd);
int __stdcall BuildDllList(HWND hWnd);
int __stdcall DeleteDeviceList(HWND hWnd);
int __stdcall DeleteModuleList(HWND hWnd);
wchar_t *LocateIniFile();
#define ULOAD_EXTERNAL_COMMAND	(WM_USER + 0x0019)

#define NT_ST

#include "main.h"
#include "helper.h"
#include "lang.h"
#ifdef NT_ST
#include "ntstatus.h"
#endif 
#include "netstatus.h"
#include "SysControl.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Shlwapi.lib") 
////////////////////////////////////////////////////////////
int tray_initialized = 0;
wchar_t *DLL_PATH;
wchar_t *OsInfo;
wchar_t *PEBlock;
wchar_t *CurrentModule;
wchar_t AllInfo[1024];
HANDLE DebugCatcherThreadHandle;
////////////////////////////////////////////////////////////
TV_ITEM tvi;
HTREEITEM Selected;
TV_INSERTSTRUCT tvinsert;
HTREEITEM Parent;
HTREEITEM Before; 
HTREEITEM Root; 
HIMAGELIST hImageList;
HBITMAP hBitMap;
////////////////////////////////////////////////////////////
TV_INSERTSTRUCT dll_tvinsert;
HTREEITEM dll_Parent;
HTREEITEM dll_Before; 
HTREEITEM dll_Root; 
HTREEITEM dll_BeforeEx; 
////////////////////////////////////////////////////////////
// http://www.codeproject.com/KB/system/SimpleSetup.aspx
// http://www.codeguru.com/forum/showthread.php?t=355688
int __stdcall BuildDevicesList(HWND hWnd){
LPTSTR devices = NULL;
DWORD len = 1024;
LPTSTR pos;
LPTSTR buffer = (LPTSTR)malloc(len * sizeof(TCHAR));
devices = (LPTSTR)malloc(len * sizeof(TCHAR));
	if(devices == NULL){
		printf("shit happenz xD\n");
        return -1;           
	}    
     while(TRUE)
        { /* expand values */
         DWORD result = QueryDosDevice(NULL, buffer, len);
         if(result == 0)
            { /* failed */
             DWORD err = GetLastError();
             if(err == ERROR_INSUFFICIENT_BUFFER)
                { /* reallocate */
                 len *= 2;
                 buffer = (LPTSTR)realloc(buffer, len * sizeof(TCHAR));
                 continue;
                } /* reallocate */
             else
                { /* other failure */
                 free(buffer);
                 return FALSE;
                } /* other failure */
            } /* failed */
         break;
        } /* expand values */
     pos = buffer;
     while(wcslen(pos) > 0)
        { /* add each */
        wchar_t szNtDeviceName[MAX_PATH];
        QueryDosDeviceW (pos, szNtDeviceName, MAX_PATH);

//		token = wcstok(crap, L"#");

  //      printf("[+] %s\n", szNtDeviceName);
			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText=szNtDeviceName;
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=1;
			Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE1,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			if(LoaderOptions.resolve_module_names){
				Root=Parent;
				Before=Parent;
				tvinsert.hParent=Parent; 
				tvinsert.hInsertAfter=TVI_LAST;
				tvinsert.item.pszText=pos; // szNtDeviceName
				Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE1,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			}
        memset(&szNtDeviceName, 0x00, sizeof(szNtDeviceName));
        pos += wcslen(pos) + 1;
        } /* add each */
     free(buffer);
     return TRUE;
}

int __stdcall BuildDllList(HWND hWnd){
	wchar_t me[1024] = {0};
	HANDLE hTest;
	BYTE *hMod;
	IMAGE_NT_HEADERS *pnt;
	IMAGE_EXPORT_DIRECTORY *exp;
	DWORD *dwFunctions, *dwAddresses, ctr;
	DWORD pPEB = GetPEB ();
	DWORD PEB_LDR_DATA = (unsigned long)*(DWORD*)(pPEB+0x0C);
	DWORD InLoadOrderModuleListHead = (unsigned long)*(DWORD*)(PEB_LDR_DATA+0x0C);
	DWORD ModuleFileName = (unsigned long)*(PDWORD*)(InLoadOrderModuleListHead+0x28);
	int a = 255;
	char functions[MAX_PATH];
	wchar_t functionsW[MAX_PATH];
	GetModuleFileNameW(0, me, sizeof me);
	while (*(DWORD*)(InLoadOrderModuleListHead) != (unsigned long)*(PDWORD*)(PEB_LDR_DATA+0x0C)){
		wchar_t mod_base[MAX_PATH] = {0};
		wchar_t mod_path[1024] = {0};
//		Clear(mod_base); Clear(mod_path);
		ModuleFileName = (unsigned long)*(PDWORD*)(InLoadOrderModuleListHead+0x28);
		InLoadOrderModuleListHead = *(DWORD*)(InLoadOrderModuleListHead);
			if(wcscmp((LPCWSTR)ModuleFileName, me) == 0) continue;
			dll_tvinsert.hParent=NULL;			// top most level no need handle
			dll_tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            dll_tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        dll_tvinsert.item.pszText=PathFindFileNameW((LPWSTR)ModuleFileName);
			dll_tvinsert.item.iImage=0;
			dll_tvinsert.item.iSelectedImage=1;
			dll_Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE2,TVM_INSERTITEM,0,(LPARAM)&dll_tvinsert);	// insert module name

		//	if(LoaderOptions.dll_resolve_path == 1){
				swprintf(mod_path, 1024, L"Path: %s", (LPWSTR)ModuleFileName);
				dll_Root=dll_Parent;
				dll_Before=dll_Parent;
				dll_tvinsert.hParent=dll_Parent; 
				dll_tvinsert.hInsertAfter=TVI_LAST;
				dll_tvinsert.item.pszText=mod_path;
				dll_Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE2,TVM_INSERTITEM,0,(LPARAM)&dll_tvinsert);
		//	}
			//	if(LoaderOptions.dll_resolve_base == 1){
					swprintf(mod_base, MAX_PATH, L"Base: 0x%08x", (DWORD)ModuleFileName);
					dll_tvinsert.hParent=dll_Before; 
					dll_tvinsert.hInsertAfter=TVI_LAST;
					dll_tvinsert.item.pszText=mod_base;
					dll_Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE2,TVM_INSERTITEM,0,(LPARAM)&dll_tvinsert);
			//	}
					if(LoaderOptions.dll_resolve_exports == 1){
						dll_tvinsert.hParent=dll_Before;
						dll_tvinsert.hInsertAfter=TVI_LAST;
						dll_tvinsert.item.pszText=L"Exports";
						dll_Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE2,TVM_INSERTITEM,0,(LPARAM)&dll_tvinsert);
						dll_BeforeEx=dll_Parent;
						hTest = GetModuleHandle(PathFindFileNameW((LPWSTR)ModuleFileName));
						hMod = (BYTE*)hTest; 
						pnt = (IMAGE_NT_HEADERS*)&hMod[PIMAGE_DOS_HEADER(hMod)->e_lfanew];
						exp = (IMAGE_EXPORT_DIRECTORY*)&hMod[pnt->OptionalHeader.DataDirectory->VirtualAddress];
						dwFunctions = (DWORD*)&hMod[exp->AddressOfNames];
						dwAddresses = (DWORD*)&hMod[exp->AddressOfFunctions];
						for (ctr = 0; ctr < exp->NumberOfNames; ctr++) {
							sprintf(functions, "[%d]:%s:[%xh]\r\n", ctr, (char*)&hMod[dwFunctions[ctr]], &hMod[dwAddresses[ctr]]);
							MultiByteToWideChar(CP_ACP, 0, functions, -1, functionsW, sizeof(functionsW));
							dll_tvinsert.hParent=dll_BeforeEx;
							dll_tvinsert.hInsertAfter=TVI_LAST;
							dll_tvinsert.item.pszText=functionsW;
							dll_Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE2,TVM_INSERTITEM,0,(LPARAM)&dll_tvinsert);
							Clear(functions);
						}
					}
	}
return 0;
}

int __stdcall DeleteDeviceList(HWND hWnd){
	int i;
	int TreeCount=TreeView_GetCount(GetDlgItem(hWnd,IDC_TREE1));
	for(i=0;i<TreeCount;i++)
			TreeView_DeleteAllItems(GetDlgItem(hWnd,IDC_TREE1));
return 0;
}

int __stdcall DeleteModuleList(HWND hWnd){
	int i;
	int TreeCount=TreeView_GetCount(GetDlgItem(hWnd,IDC_TREE2));
	for(i=0;i<TreeCount;i++)
			TreeView_DeleteAllItems(GetDlgItem(hWnd,IDC_TREE2));
return 0;
}

int __stdcall GetMenuOffset(){
	int Offset;
	if(LoaderOptions.vista_glass == STATUS_NO_GLASS){
		Offset = 0;
	} else if(LoaderOptions.vista_glass == STATUS_VISTA_GLASS){
		Offset = 15;
	}

	return Offset;
}

static BOOL MainDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
if(tray_initialized == 0){
g_hwnd = hWnd;
hMainIn = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
WM_TASKBARCREATED = RegisterWindowMessageA("TaskbarCreated");
	if(WM_TASKBARCREATED == 0){
		MessageBoxW(0, L"Hide to Tray disabled!", L"WARNING", MB_ICONWARNING);
	}
InitNotifyIconData();
	if( !IsWindowVisible( g_hwnd ) )
	{
    Shell_NotifyIcon(NIM_DELETE, &g_notifyIconData);
	}
tray_initialized = 1;
}

/***************************************************/
if(load_dll_mode == 1){
	CheckDlgButton(hWnd, IDC_RADIO1, BST_CHECKED);
} else {
	CheckDlgButton(hWnd, IDC_RADIO1, BST_UNCHECKED);
}
if(injection_mode == 0){
	CheckDlgButton(hWnd, IDC_RADIO4, BST_CHECKED);
} else {
	CheckDlgButton(hWnd, IDC_RADIO4, BST_UNCHECKED);
}
if(unload_file_option == 1){
	CheckDlgButton(hWnd, IDC_CHECK1, BST_CHECKED);
} else if(unload_file_option == 0){
	CheckDlgButton(hWnd, IDC_CHECK1, BST_UNCHECKED);
}
if(delete_file_option == 1){
	CheckDlgButton(hWnd, IDC_CHECK2, BST_CHECKED);
} else if(delete_file_option == 0){
	CheckDlgButton(hWnd, IDC_CHECK2, BST_UNCHECKED);
}
/***************************************************/

  if ( uMsg==WM_TASKBARCREATED && !IsWindowVisible( g_hwnd ) )
  {
    Minimize();
    return 0;
  }
	HMENU hDialMenu = GetMenu(hWnd);
	int MENU_OFFSET = GetMenuOffset();
	switch(uMsg){
	   
	case WM_ACTIVATE:	// nothing
	   break;

   case WM_ERASEBKGND:	// nothing
		break;

		   case WM_INITDIALOG:
		   {
		   HINSTANCE hIn;
		   RECT lpRect;
		   GetClientRect(hWnd, &lpRect);
		   ClientResize(hWnd, lpRect.right, lpRect.bottom - 245 - MENU_OFFSET);
		   ShowHideBottomPanel(hWnd, true);
		   hidden = 1;
		   if(UserLanguage == 0x0415) {
			   MakePolish(hWnd);
			   MakeTooltips(hWnd, PL);
	//		   CheckDlgButton(hWnd, IDC_RADIO8, BST_CHECKED);
		   } else if(UserLanguage == 0x0419) {
			   MakeRussian(hWnd);
			   MakeTooltips(hWnd, RU);
	//		   CheckDlgButton(hWnd, IDC_RADIO9, BST_CHECKED);
		   } else if(UserLanguage == 0x0422) {
			   MakeRussian(hWnd);
			   MakeTooltips(hWnd, RU);
	//		   CheckDlgButton(hWnd, IDC_RADIO9, BST_CHECKED);
		   } else {
				MakeTooltips(hWnd, EN);
	//			CheckDlgButton(hWnd, IDC_RADIO7, BST_CHECKED);
		   }
			hMainUpperMenu = GetMenu(hWnd);
		   hIn = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
		   SetClassLong(hWnd, GCL_HICON, (LONG)LoadIcon(hIn, (LPCTSTR)IDI_ICON1));
		   g_menu = CreatePopupMenu();
		   AppendMenu(g_menu, MF_STRING, ID_TRAY_EXIT_CONTEXT_MENU_ITEM,  TEXT( "Exit" ) );
		   RegisterHotKey(hWnd, TERMINATE_HOT_KEY, MOD_WIN , 'Q');
		   RegisterHotKey(hWnd, TRAY_HOT_KEY, MOD_WIN , 'A');
		   RegisterHotKey(hWnd, FROMTRAY_HOT_KEY, MOD_WIN , 'Z');

			if(LoaderOptions.vista_glass == STATUS_NO_GLASS){
				hStatus = CreateStatusBar(hWnd, OsInfo, PEBlock, CurrentModule);
			}

//			hImageList=ImageList_Create(16,16,ILC_COLOR16,2,10);
//			hBitMap=LoadBitmap(hIn,MAKEINTRESOURCE(IDB_BITMAP1));
//			ImageList_Add(hImageList,hBitMap,NULL);	
//			DeleteObject(hBitMap);	
//			SendDlgItemMessage(hWnd,IDC_TREE1,TVM_SETIMAGELIST,0,(LPARAM)hImageList);
			BuildDevicesList(hWnd);
			BuildDllList(hWnd);
			SetButtonIcon(hWnd, IDC_RADIO1, IDI_ICON2);
			SetButtonIcon(hWnd, IDC_RADIO2, IDI_ICON3);
			SetButtonIcon(hWnd, IDC_CHECK1, IDI_ICON3);
			SetButtonIcon(hWnd, IDC_CHECK2, IDI_ICON4);
			SetButtonIcon(hWnd, IDC_RADIO3, IDI_ICON6);
			SetButtonIcon(hWnd, IDC_RADIO4, IDI_ICON5);

			SetButtonIcon(hWnd, IDOK, IDI_ICON8);
			SetButtonIcon(hWnd, IDC_BUTTON4, IDI_ICON10);
			SetButtonIcon(hWnd, IDCANCEL, IDI_ICON9);
			SetButtonIcon(hWnd, IDC_BUTTON3, IDI_ICON7);

			SetButtonIcon(hWnd, IDC_BUTTON2, IDI_ICON11);
			SetButtonIcon(hWnd, IDC_BUTTON5, IDI_ICON12);
			SetButtonIcon(hWnd, IDC_BUTTON6, IDI_ICON13);
			SetButtonIcon(hWnd, IDC_BUTTON7, IDI_ICON14);

			SetButtonIcon(hWnd, IDC_RADIO7, IDI_ICON15);	// set eng flag icon
			SetButtonIcon(hWnd, IDC_RADIO8, IDI_ICON16);	// set pl flag icon
			SetButtonIcon(hWnd, IDC_RADIO9, IDI_ICON17);	// set ru flag icon

			SetStyleEx(hWnd, IDC_TREE1);
			SetStyleEx(hWnd, IDC_TREE2);
			SetStyleEx(hWnd, IDC_LIST1);

			if(LoaderOptions.auto_buffer_clear == 1)CheckDlgButton(hWnd, IDC_CHECK6, BST_CHECKED);
			if(LoaderOptions.dll_resolve_exports == 1)CheckDlgButton(hWnd, IDC_CHECK3, BST_CHECKED);
			if(LoaderOptions.dll_resolve_base == 1)CheckDlgButton(hWnd, IDC_CHECK4, BST_CHECKED);
			if(LoaderOptions.dll_resolve_path == 1)CheckDlgButton(hWnd, IDC_CHECK5, BST_CHECKED);
			if(LoaderOptions.nt_api == 1)CheckDlgButton(hWnd, IDC_RADIO5, BST_CHECKED);
			else CheckDlgButton(hWnd, IDC_RADIO6, BST_CHECKED);
			if(LoaderOptions.resolve_module_names == 1)CheckDlgButton(hWnd, IDC_CHECK7, BST_CHECKED);

			HWND hWndList = GetDlgItem(hWnd, IDC_COMBO2);
			SendMessageW(hWndList, CB_ADDSTRING, 0, (LPARAM)L"Default Look");
			SendMessageW(hWndList, CB_ADDSTRING, 0, (LPARAM)L"Glamour Style");
	//		SendMessageW(hWndList, CB_SETCURSEL, 0, 0);

			HWND hWndList2 = GetDlgItem(hWnd, IDC_COMBO3);
			SendMessageW(hWndList2, CB_ADDSTRING, 0, (LPARAM)L"English");
			SendMessageW(hWndList2, CB_ADDSTRING, 0, (LPARAM)L"Polski");
			SendMessageW(hWndList2, CB_ADDSTRING, 0, (LPARAM)L"Русский");

			if(LoaderOptions.vista_glass == STATUS_NO_GLASS){
				SendMessage(hWndList, CB_SETCURSEL, 0, 0);
			} else if(LoaderOptions.vista_glass == STATUS_VISTA_GLASS){
				SendMessage(hWndList, CB_SETCURSEL, 1, 0);
			}

			if(LoaderOptions.user_default_lang == EN)
				SendMessage(hWndList2, CB_SETCURSEL, 0, 0);
			else if(LoaderOptions.user_default_lang == PL)
				SendMessage(hWndList2, CB_SETCURSEL, 1, 0);
			else if(LoaderOptions.user_default_lang == RU)
				SendMessage(hWndList2, CB_SETCURSEL, 2, 0);

			InsertMenu(GetSystemMenu (hWnd, FALSE), 0xfff,
                        MF_BYCOMMAND | MF_SEPARATOR, 0,  L"-");
			InsertMenu(GetSystemMenu (hWnd, FALSE), SYS_ABOUT_INFO,
                        MF_BYCOMMAND | MF_STRING, SYS_ABOUT_INFO,  L"About");
			InsertMenu(GetSystemMenu (hWnd, FALSE), SYS_QUIT,
                        MF_BYCOMMAND | MF_STRING, SYS_QUIT,  L"Quit");
			InsertMenu(GetSystemMenu (hWnd, FALSE), 0xfff,
                        MF_BYCOMMAND | MF_SEPARATOR, 0,  L"-");
			InsertMenu(GetSystemMenu (hWnd, FALSE), SYS_REBOOT,
                        MF_BYCOMMAND | MF_STRING, SYS_REBOOT,  L"Reboot");
			InsertMenu(GetSystemMenu (hWnd, FALSE), SYS_SHUTDOWN,
                        MF_BYCOMMAND | MF_STRING, SYS_SHUTDOWN,  L"Shutdown");
			InsertMenu(GetSystemMenu (hWnd, FALSE), 0xfff,
                        MF_BYCOMMAND | MF_SEPARATOR, 0,  L"-");
			InsertMenu(GetSystemMenu (hWnd, FALSE), SYS_CATCH_W32DEBUG,
                        MF_BYCOMMAND | MF_STRING, SYS_CATCH_W32DEBUG,  L"Capture Win32 Debug");
	//		InsertMenu(GetSystemMenu (hWnd, FALSE), SYS_CATCH_VKRNLDEBUG,
      //                  MF_BYCOMMAND | MF_STRING, SYS_CATCH_VKRNLDEBUG,  L"Capture (>= NT6) Kernel Debug");

			InitTreeViewHeader(hWnd, IDC_LIST1);
				if(LoaderOptions.vista_glass == STATUS_VISTA_GLASS){
					int shit = InitGlass(hWnd, true, OsInfo, PEBlock, CurrentModule);
				}

		   }
		   return TRUE;

		   case WM_PAINT:
			   {
				   PAINTSTRUCT ps; // Ultima Loader™
				   RECT lpRect;
				   GetClientRect(hWnd, &lpRect);
				   HDC hdc = BeginPaint(hWnd, &ps);
					if(LoaderOptions.vista_glass == STATUS_VISTA_GLASS){
						EraseTopBottom(Marg.Top, Marg.Bottom, hWnd, hdc);
						if(LoaderOptions.show_os_info == 1){
							OutputGlowingText(hWnd, hdc, AllInfo, (RECTHEIGHT(lpRect)-20), 0);
						} else {
							OutputGlowingText(hWnd, hdc, L"www.machinized.com", (RECTHEIGHT(lpRect)-20), 0);
						}
					}
					SetBkgImage(hWnd, hdc, IDB_PNG1, 5, 0, 128, 128);
			//		SetBkgImage(hWnd, hdc, IDB_PNG2, 135, 60, 20, 20);
			//		SetBkgImage(hWnd, hdc, IDB_PNG3, 155, 0, 128, 128);
					PrintUIText(hdc, hWnd, 14, 0, 0, 0, 0, L"Ultima Loader", 0x0, 135, 50);
					PrintUIText(hdc, hWnd, 20, 0, 0, 0, 0, L"FTW!", 0x0, 150, 80);
			//		PrintUIText(hdc, hWnd, 10, 0, 0, 0, 0, L"...just makin' life easier..", 0x0, 165, 10);
					EndPaint(hWnd, &ps);
			   }
		   break;

  case WM_TRAYICON:
    {
      switch(wParam)
      {
      case ID_TRAY_APP_ICON:
        break;
      }

      if (lParam == WM_LBUTTONUP){
        Restore();
      } else if (lParam == WM_RBUTTONDOWN){
        POINT curPoint;
		unsigned int clicked;
        GetCursorPos( &curPoint ) ;
        SetForegroundWindow(hWnd); 

        clicked = TrackPopupMenu(g_menu, TPM_RETURNCMD | TPM_NONOTIFY,
								 curPoint.x, curPoint.y, 0, hWnd, NULL);

        if (clicked == ID_TRAY_EXIT_CONTEXT_MENU_ITEM){
          KillSelf();
        }
      }
    }
    break;

	case WM_TIMER:	// expand and collapse animations go here
		{
			RECT lpRect;
			GetClientRect(hWnd, &lpRect);
			switch(LOWORD(wParam)){
				case ANIMATION_TIMER:
				{
					DestroyWindow(hStatus);
					if (++m_nAnimationCount > (EXPAND_MAX_STEPS / 2)){
						KillTimer(hWnd, ANIMATION_TIMER);
		//				ClientResize(hWnd, lpRect.right, lpRect.bottom - 45);
						DestroyWindow(hStatus);
						hStatus = CreateStatusBar(hWnd, OsInfo, PEBlock, CurrentModule);
					} else {
						ClientResize(hWnd, lpRect.right, lpRect.bottom + (15*2) - 5);
					}						
				}
				break;

				case ANIMATION_COLLASE:
				{
					if (++n_nAnimationCount > (EXPAND_MAX_STEPS / 2)){
						KillTimer(hWnd, ANIMATION_COLLASE);
		//				ClientResize(hWnd, lpRect.right, lpRect.bottom + 45);
						DestroyWindow(hStatus);
						hStatus = CreateStatusBar(hWnd, OsInfo, PEBlock, CurrentModule);
					} else {
						ClientResize(hWnd, lpRect.right, lpRect.bottom - (15*2) + 5);
					}
				}
				break;
			}
		}
	break;
			case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					{
					LPTSTR lpszString; 
					int nCurSel;
					nCurSel = SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETCURSEL, 0, 0);
					if (nCurSel != -1){
						lpszString = (LPTSTR)HeapAlloc(GetProcessHeap(), 
									  HEAP_ZERO_MEMORY, 
									  sizeof(TCHAR)*(SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETLBTEXTLEN, nCurSel, 0) + 1));
						if (lpszString != NULL){
							SendDlgItemMessage(hWnd, IDC_COMBO1, CB_GETLBTEXT, nCurSel, (LPARAM)lpszString);
						} else {
							lpszString = NULL;
						}
					} else {
						lpszString = NULL;
					}

					Run(load_dll_mode, 
						injection_mode, 
						unload_file_option, 
						delete_file_option, 
						DLL_PATH, 
						lpszString, 
						hWnd);
					
					HeapFree(GetProcessHeap(), 0, (LPVOID)lpszString);
					}
					break;
				case IDCANCEL:
					Minimize();
					break;
				case IDC_BUTTON3:	// quit button
					__asm call KillSelf;
					break;

				case IDC_BUTTON1:
					DLL_PATH = GetDLL((void*)hWnd);
					break;
				case IDC_BUTTON4:
					{
						ClearAllBuffer(hWnd, IDC_LIST1);
					}
					break;

				case IDC_CHECK1:
					{
					if(unload_file_option == 1) unload_file_option = 0;
					else unload_file_option = 1;
					}
					break;
				case IDC_CHECK2:
					{
					if(delete_file_option == 1) delete_file_option = 0;
					else delete_file_option = 1;
					}
					break;
				case IDC_RADIO1:
					{
					load_dll_mode = 1;
					unload_dll_mode = 0;
					}
					break;
				case IDC_RADIO2:
					{
					load_dll_mode = 0;
					unload_dll_mode = 1;
					}
					break;
				case IDC_RADIO3:
					{
					HWND hWndList;
					HANDLE hTmp;
					PROCESSENTRY32 pe32 = {0};
					injection_mode = 1;
					not_injection_mode = 0;
					hWndList = GetDlgItem(hWnd, IDC_COMBO1);
					hTmp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
					pe32.dwSize = sizeof(PROCESSENTRY32);
					Process32First(hTmp, &pe32);
					do {
						SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM)pe32.szExeFile);
						proc_list++;
					} while (Process32Next(hTmp, &pe32));
					if ( hTmp != INVALID_HANDLE_VALUE )CloseHandle(hTmp);
					SendMessage(hWndList, CB_SETCURSEL, 1, 0);
					}
					break;
				case IDC_RADIO4:
					{
					HWND hWndList;
					injection_mode = 0;
					not_injection_mode = 1;
					hWndList = GetDlgItem(hWnd, IDC_COMBO1);
					while(proc_list > 0){
						SendMessage(hWndList, CB_DELETESTRING, 0, (LPARAM)0);
						proc_list--;
					}
					}
					break;

				case ID_INFO_GENERAL:
						ProgInfo();
					break;

				case ID_FILE_QUIT:
						__asm call KillSelf;
					break;

				case ID_FILE_REBOOT:
						NtReboot(hWnd, FALSE);
					break;

				case ID_FILE_SHUTDOWN:
						NtReboot(hWnd, TRUE);
					break;

				case ID_STATUS_NTSTATUSPARSER:
#ifdef NT_ST
					DialogBoxParam(	GetModuleHandle(NULL), 
									MAKEINTRESOURCE(IDD_DIALOG2), 
									NULL, 
									(DLGPROC)NtStatusDialogProc, 
									0);
#endif 
					break;

				case ID_STATUS_WINSTATUSPARSER:
					DialogBoxParam(	GetModuleHandle(NULL), 
									MAKEINTRESOURCE(IDD_DIALOG3), 
									NULL, 
									(DLGPROC)NetStatusDialogProc, 
									0);
					break;

				case ID_HOOKFUNCTIONS_DBGPRINT:	// hDialMenu
					{
						if(GetMenuState(hDialMenu, ID_HOOKFUNCTIONS_DBGPRINT, 0) == MF_CHECKED){
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_DBGPRINT, MF_UNCHECKED);
						} else {
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_DBGPRINT, MF_CHECKED);
						}
					}
					break;

				case ID_HOOKFUNCTIONS_DBGPRINTEX:
					{
						if(GetMenuState(hDialMenu, ID_HOOKFUNCTIONS_DBGPRINTEX, 0) == MF_CHECKED){
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_DBGPRINTEX, MF_UNCHECKED);
						} else {
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_DBGPRINTEX, MF_CHECKED);
						}
					}
					break;

				case ID_HOOKFUNCTIONS_VDBGPRINTEX:
					{
						if(GetMenuState(hDialMenu, ID_HOOKFUNCTIONS_VDBGPRINTEX, 0) == MF_CHECKED){
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_VDBGPRINTEX, MF_UNCHECKED);
						} else {
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_VDBGPRINTEX, MF_CHECKED);
						}
					}
					break;

				case ID_HOOKFUNCTIONS_VDBGPRINTEXWITHPREFIX:
					{
						if(GetMenuState(hDialMenu, ID_HOOKFUNCTIONS_VDBGPRINTEXWITHPREFIX, 0) == MF_CHECKED){
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_VDBGPRINTEXWITHPREFIX, MF_UNCHECKED);
						} else {
							CheckMenuItem(hDialMenu, ID_HOOKFUNCTIONS_VDBGPRINTEXWITHPREFIX, MF_CHECKED);
						}
					}
					break;
/*
				case ID_KRNLOUTPUT_DEPLOYDRIVER:
						NtUnpackDriver(hWnd);
					break;

				case ID_KRNLOUTPUT_REMOVEDRIVER:
					{
						wchar_t buffer[1024];
						int Status;
						DWORD dwRet;
						size_t len = sizeof(buffer);
						NtZeroMemory(buffer, len);
						dwRet = GetCurrentDirectoryW(len, buffer);
						if(dwRet > len){
							InsertBufferStatus(hWnd, L"[-] Fatal Error! Aborting.\r\n");
							return -1;
						} else {
							wcscat(buffer, L"\\");
							wcscat(buffer, ULTIMA_LOADER_HOOK_DRIVER);
							Status = NtRemoveFile(buffer, hWnd);
						}
					}
					break;

				case ID_KRNLOUTPUT_LOADDRIVER:
					{
						wchar_t buffer[1024];
						int Status;
						DWORD dwRet;
						size_t len = sizeof(buffer);
						NtZeroMemory(buffer, len);
						dwRet = GetCurrentDirectoryW(len, buffer);
						if(dwRet > len){
							InsertBufferStatus(hWnd, L"[-] Fatal Error! Aborting.\r\n");
							return -1;
						} else {
							wcscat(buffer, L"\\");
							wcscat(buffer, ULTIMA_LOADER_HOOK_DRIVER);
							Status = NativeLoadDriver(buffer, hWnd);
						}
					}
					break;

				case ID_KRNLOUTPUT_UNLOADDRIVER:
					{
						wchar_t buffer[1024];
						int Status;
						DWORD dwRet;
						size_t len = sizeof(buffer);
						NtZeroMemory(buffer, len);
						dwRet = GetCurrentDirectoryW(len, buffer);
						if(dwRet > len){
							InsertBufferStatus(hWnd, L"[-] Fatal Error! Aborting.\r\n");
							return -1;
						} else {
							wcscat(buffer, L"\\");
							wcscat(buffer, ULTIMA_LOADER_HOOK_DRIVER);
							Status = NativeUnloadDriver(buffer, hWnd);
						}					
					}
					break;

				case ID_KRNLOUTPUT_INITHOOK:
					{
							HANDLE hDevice = NtOpenDevice(ULTIMA_LOADER_HOOK_DEVICE, hWnd);
							if(hDevice == NULL){
								InsertBufferStatus(hWnd, L"[-] Unable to open transliterator device!\r\n");
								return -1;
							} else {
							// Implementation of IOCTL code to start kbd alternation 
								InsertBufferStatus(hWnd, L"[+] Transliterator device opened.\r\n");
								ULONG InBuf[1];
						//		HWND hW = GetHandle(L"Project1.exe");
								//CLIENT_ID ClientID;
								//hDummyThread = StartDummyThread(hWnd, &ClientID);
								InBuf[0] = (ULONG)hWnd;
				//				InBuf[1] = (ULONG)((DWORD_PTR)ApcHandler);
								int Status = NtControlTranslitDevice(IOCTL_DBGPRINT_HOOK, (LPVOID)InBuf, sizeof(InBuf), hWnd);
								if(Status == -1){
									InsertBufferStatus(hWnd, L"[-] Cannot open control device!\r\n");
									return -1;
								} else if(Status == -2){
									InsertBufferStatus(hWnd, L"[-] NtDeviceIoControlFile failed!\r\n");
									return -1;
								} else {
									InsertBufferStatus(hWnd, L"[+] Driver contacted!\r\n");
								}
							}
						}
					break;

				case ID_KRNLOUTPUT_DEINITHOOK:
					break;
*/ 
/*
				case IDC_CHECK6:	// autocleaner settings
					{
						LoaderOptions.auto_buffer_clear = 
							SwitchParams(	LoaderOptions.auto_buffer_clear,
											L"AutoClearBuffer",
											hWnd,
											IDC_CHECK6,
											false	);
					}
				break;
*/ 
				case IDC_CHECK3:	// resolve dll exports
					{
						LoaderOptions.dll_resolve_exports = 
							SwitchParams(	LoaderOptions.dll_resolve_exports,
											L"DllResolveExports",
											hWnd,
											IDC_CHECK3,
											false	);
						DeleteModuleList(hWnd);
						BuildDllList(hWnd);
					}
				break;
/*
				case IDC_CHECK4:	// resolve dll base address
					{
						LoaderOptions.dll_resolve_base = 
							SwitchParams(	LoaderOptions.dll_resolve_base,
											L"DllResolveBase",
											hWnd,
											IDC_CHECK4,
											false	);
						DeleteModuleList(hWnd);
						BuildDllList(hWnd);
					}
				break;
*/ 
				/*
				case IDC_CHECK5:	// resolve dll path
					{
						LoaderOptions.dll_resolve_path = 
							SwitchParams(	LoaderOptions.dll_resolve_path,
											L"DllResolvePath",
											hWnd,
											IDC_CHECK5,
											false	);
						DeleteModuleList(hWnd);
						BuildDllList(hWnd);
					}
				break;
*/ 
				case IDC_CHECK7:
					{
						LoaderOptions.resolve_module_names = 
							SwitchParams(	LoaderOptions.resolve_module_names,
											L"SysResolveNames",
											hWnd,
											IDC_CHECK7,
											false	);
						DeleteDeviceList(hWnd);
						BuildDevicesList(hWnd);
					}
				break;

				case IDC_RADIO5:
					{
						WritePrivateProfileStringW(L"NTAPI", L"value", L"TRUE", LocateIniFile());
						LoaderOptions.nt_api = 1;
					}
				break;

				case IDC_RADIO6:
					{
						WritePrivateProfileStringW(L"NTAPI", L"value", L"FALSE", LocateIniFile());
						LoaderOptions.nt_api = 0;
					}
				break;

				case IDC_BUTTON2:	// ntstatus codes lookup
					{
#ifdef NT_ST
					DialogBoxParam(	GetModuleHandle(NULL), 
									MAKEINTRESOURCE(IDD_DIALOG2), 
									NULL, 
									(DLGPROC)NtStatusDialogProc, 
									0);
#endif 
					}
				break;

				case IDC_BUTTON5:	// windows startd error codes lookup
					{
					DialogBoxParam(	GetModuleHandle(NULL), 
									MAKEINTRESOURCE(IDD_DIALOG3), 
									NULL, 
									(DLGPROC)NetStatusDialogProc, 
									0);
					}
				break;

				case IDC_BUTTON6:	// expand gui
					{
						if(hidden == 0){	// hide bottom panel
							ShowHideBottomPanel(hWnd, true);
							if(LoaderOptions.vista_glass == STATUS_VISTA_GLASS){
								RECT lpRect;
								GetClientRect(hWnd, &lpRect);
								ClientResize(hWnd, lpRect.right, lpRect.bottom - (15*20) + 45);
								InvalidateRect(hWnd, &lpRect, TRUE);
								UpdateWindow(hWnd);
							} else if(LoaderOptions.vista_glass == STATUS_NO_GLASS){
								n_nAnimationCount = 0;
								SetTimer(hWnd, ANIMATION_COLLASE, 1, NULL);
							}
							hidden = 1;
						} else if(hidden == 1){	// show bottom panel
							ShowHideBottomPanel(hWnd, false);
							if(LoaderOptions.vista_glass == STATUS_VISTA_GLASS){
								RECT lpRect;
								GetClientRect(hWnd, &lpRect);
								ClientResize(hWnd, lpRect.right, lpRect.bottom + (15*20) - 45);
								InvalidateRect(hWnd, &lpRect, TRUE);
								UpdateWindow(hWnd);
							} else if(LoaderOptions.vista_glass == STATUS_NO_GLASS){
								m_nAnimationCount = 0;
								SetTimer(hWnd, ANIMATION_TIMER, 1, NULL);
							}
							hidden = 0;
						}
					}
				break;

				case IDC_BUTTON7:	// refresh lists
					{
						DeleteDeviceList(hWnd);
						DeleteModuleList(hWnd);
						BuildDevicesList(hWnd);
						BuildDllList(hWnd);
					}
				break;

				case IDC_COMBO2:
					{
						if ( HIWORD(wParam) == CBN_SELCHANGE ){
							RECT lpRect;
							GetClientRect(hWnd, &lpRect);
							//qmb(L"lol", L"lol");
							LPTSTR lpszString; 
							int nCurSel;
							nCurSel = SendDlgItemMessage(hWnd, IDC_COMBO2, CB_GETCURSEL, 0, 0);
							if (nCurSel != -1){
								lpszString = (LPTSTR)HeapAlloc(GetProcessHeap(), 
									  HEAP_ZERO_MEMORY, 
									  sizeof(TCHAR)*(SendDlgItemMessage(hWnd, IDC_COMBO2, CB_GETLBTEXTLEN, nCurSel, 0) + 1));
								if (lpszString != NULL){
									SendDlgItemMessage(hWnd, IDC_COMBO2, CB_GETLBTEXT, nCurSel, (LPARAM)lpszString);
									if(wcscmp(lpszString, L"Default Look") == 0) {
										LoaderOptions.vista_glass = InitGlass(hWnd, false, OsInfo, PEBlock, CurrentModule);
										RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
										WritePrivateProfileStringW(L"VistaGlass", L"value", L"FALSE", LocateIniFile());
									} else if(wcscmp(lpszString, L"Glamour Style") == 0){
										LoaderOptions.vista_glass = InitGlass(hWnd, true, OsInfo, PEBlock, CurrentModule);
										RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
										WritePrivateProfileStringW(L"VistaGlass", L"value", L"TRUE", LocateIniFile());
									}
								}
								HeapFree(GetProcessHeap(), 0, (LPVOID)lpszString);
							}
						}
					}
				break;

				case IDC_COMBO3:
					{
					if ( HIWORD(wParam) == CBN_SELCHANGE ){
						wchar_t *Text = GetComboText(IDC_COMBO3, hWnd);
						if(wcscmp(Text, L"English") == 0) {
							LoaderOptions.user_default_lang = EN;
							WritePrivateProfileStringW(	L"DefaultUserLanguage", 
														L"value", 
														L"EN", 
														LocateIniFile());
							MakeEnglish(hWnd);
							DestroyTooltips();
							MakeTooltips(hWnd, LoaderOptions.user_default_lang);
						} else if(wcscmp(Text, L"Polski") == 0){
							LoaderOptions.user_default_lang = PL;
							WritePrivateProfileStringW(	L"DefaultUserLanguage", 
														L"value", 
														L"PL", 
														LocateIniFile());
							MakePolish(hWnd);
							if(!DestroyTooltips()){
								qmb(L"lol", L"tools are there");
							}
							MakeTooltips(hWnd, LoaderOptions.user_default_lang);
						} else if(wcscmp(Text, L"Русский") == 0){
							LoaderOptions.user_default_lang = RU;
							WritePrivateProfileStringW(	L"DefaultUserLanguage", 
														L"value", 
														L"RU", 
														LocateIniFile());
							MakeRussian(hWnd);
							DestroyTooltips();
							MakeTooltips(hWnd, LoaderOptions.user_default_lang);
						} else {
							OutputDebugStringW(L"This is just wrooooong...");
						}
					}
					}
				break;

				case IDC_RADIO7:	// eng selected
					{
						WritePrivateProfileStringW(L"DefaultUserLanguage", L"value", L"EN", LocateIniFile());
					}
				break;

				case IDC_RADIO8:	// pl selected
					{
						WritePrivateProfileStringW(L"DefaultUserLanguage", L"value", L"PL", LocateIniFile());
					}
				break;

				case IDC_RADIO9:	// ru selected
					{
						WritePrivateProfileStringW(L"DefaultUserLanguage", L"value", L"RU", LocateIniFile());
					}
				break;
			}
			return TRUE;

			case WM_SYSCOMMAND:
				switch (LOWORD(wParam)) {
					case SYS_ABOUT_INFO:
						{
							ProgInfo();
						}
					break;

					case SYS_QUIT:
						{
							__asm call KillSelf;
						}
					break;

					case SYS_REBOOT:
						{
							NtReboot(hWnd, FALSE);
						}
					break;

					case SYS_SHUTDOWN:
						{
							NtReboot(hWnd, TRUE);
						}
					break;

					case SYS_CATCH_W32DEBUG:
						{
							if(GetMenuState(GetSystemMenu (hWnd, FALSE), SYS_CATCH_W32DEBUG, 0) == MF_CHECKED){
								CheckMenuItem(GetSystemMenu (hWnd, FALSE), SYS_CATCH_W32DEBUG, MF_UNCHECKED);
								CloseHandle(bufferready); 
								CloseHandle(dataready); 
								UnmapViewOfFile(str); 
								CloseHandle(buffer); 
								NtTerminateThread(DebugCatcherThreadHandle, 0);
								InsertBufferStatus((HWND)hWnd, L"[+] Debug Monitor Stopped\n"); 
							} else {
								CheckMenuItem(GetSystemMenu (hWnd, FALSE), SYS_CATCH_W32DEBUG, MF_CHECKED);
								RtlCreateUserThread(((HANDLE)-1), NULL, FALSE, 0, 0, 0, 
											(LPTHREAD_START_ROUTINE)OutputDebugStringCatch, 
											(LPVOID)hWnd, &DebugCatcherThreadHandle, 0);
							}
						}
					break;
				}
				break;

			case WM_HOTKEY:
				if(LOWORD(wParam) == TERMINATE_HOT_KEY){
					KillSelf();
				} else if(LOWORD(wParam) == TRAY_HOT_KEY){
					Minimize();
				} else if(LOWORD(wParam) == FROMTRAY_HOT_KEY){
					Restore();
				}
				break;

			case ULOAD_EXTERNAL_COMMAND:
					qmb(L"Test command received!", L"Test command received!");
				break;

			case WM_LBUTTONDOWN:
				{
					ReleaseCapture();
					SendMessage(hWnd,WM_NCLBUTTONDOWN,HTCAPTION,0); 
				}
				break;

			case WM_NOTIFY:
				{
					switch(LOWORD(wParam)){
			case IDC_LIST1:
				{
					POINT curPoint;
					unsigned int clicked;
					if(((LPNMHDR)lParam)->code == NM_DBLCLK){
						NMITEMACTIVATE *nmia = (NMITEMACTIVATE *)lParam;
						if (nmia->iItem != -1){
							wchar_t item[1024] = {0};
							wchar_t debug[1024] = {0};
							int iPos = ListView_GetNextItem(GetDlgItem(hWnd, IDC_LIST1), -1, LVNI_SELECTED);
							LVITEM lvi = {0};
							lvi.cchTextMax=1024;
							lvi.iSubItem=0;
							lvi.pszText=item;
							SendMessageW(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)iPos, (LPARAM)&lvi);
							swprintf(debug, 1024, L"Status time: \n%s\n\n", lvi.pszText);
							memset(&lvi, 0x00, sizeof(lvi)); memset(&item, 0x00, sizeof(item));
							lvi.cchTextMax=1024;
							lvi.iSubItem=1;
							lvi.pszText=item;
							SendMessageW(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)iPos, (LPARAM)&lvi);
							wcscat(debug, L"Status description: \n");
							wcscat(debug, lvi.pszText);
							MessageBoxW(0, debug, L"INFO", MB_ICONINFORMATION);
							memset(&item, 0x00, sizeof(item));
							memset(&debug, 0x00, sizeof(debug));
						}
					}

					if(((LPNMHDR)lParam)->code == NM_RCLICK){
						NMITEMACTIVATE *nmia = (NMITEMACTIVATE *)lParam;
						if (nmia->iItem != -1){
							HMENU hPopupMenu = CreatePopupMenu();
							AppendMenu(hPopupMenu, MF_STRING, ERROR_LOOKUP, L"Error Lookup");
							GetCursorPos( &curPoint ) ;
							SetForegroundWindow(hWnd);
							clicked = TrackPopupMenu(hPopupMenu,
													TPM_RETURNCMD | TPM_NONOTIFY,
													curPoint.x, curPoint.y,
													0, hWnd, NULL);
							if(clicked == ERROR_LOOKUP){
								int iPos = ListView_GetNextItem(GetDlgItem(hWnd, IDC_LIST1), -1, LVNI_SELECTED);
								LVITEM lvi;
								lvi.cchTextMax=512;
								lvi.iSubItem=1;
								wchar_t item[512];
								lvi.pszText=item;
								SendMessageW(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)iPos, (LPARAM)&lvi);
								qmb(L"suka", lvi.pszText);
								memset(&item, 0x00, sizeof(item));
							}
						}
					}
				}
			break;
				case IDC_TREE1:
					{
						POINT curPoint;
						unsigned int clicked;
						if(((LPNMHDR)lParam)->code == NM_DBLCLK){
						
						}

						if(((LPNMHDR)lParam)->code == NM_RCLICK){
		//					NMITEMACTIVATE *nmia = (NMITEMACTIVATE *)lParam;
		//					if (nmia->iItem != -1){
		//						HMENU hPopupMenu = CreatePopupMenu();
		//						AppendMenu(hPopupMenu, MF_STRING, SYS_SEND_CUSTOM_IOCTL, L"Send Custom IOCTL");
		//						POINT curPoint ;
		//						GetCursorPos( &curPoint ) ;
		//						SetForegroundWindow(hWnd);
		//						clicked = TrackPopupMenu(hPopupMenu,
		//													  TPM_RETURNCMD | TPM_NONOTIFY,
		//													  curPoint.x, curPoint.y,
		//													  0, hWnd, NULL);
		//			//			qmb(L"lol", L"lol");
		//					}
						}
					}	// tree1 end
					break;

				case IDC_TREE2:
					{
						unsigned int clicked;
						POINT curPoint;
						if(((LPNMHDR)lParam)->code == NM_DBLCLK){

						}

						if(((LPNMHDR)lParam)->code == NM_RCLICK){
							NMITEMACTIVATE *nmia = (NMITEMACTIVATE *)lParam;
							if (nmia->iItem != -1){
								wchar_t *t, *token[1024];
								HMENU hPopupMenu = CreatePopupMenu();
								HWND list = GetDlgItem(hWnd, IDC_TREE2);
								wchar_t Text[1024] = {0};
								wchar_t Function[MAX_PATH] = {0};
								TV_ITEM tv; 
								int i;
								HTREEITEM Parent; 
								wchar_t TextEx[1024] = {0}; 

								Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE2,TVM_GETNEXTITEM,TVGN_CARET,(LPARAM)NULL); 

								tv.mask=TVIF_TEXT|TVIF_HANDLE; 
								tv.pszText=TextEx; 
								tv.cchTextMax=255; 
								tv.hItem=Parent; 

								SendDlgItemMessage(hWnd, IDC_TREE2, TVM_GETITEM,TVGN_CARET,(LPARAM)&tv);
							//	qmb(tv.pszText, tv.pszText);
								if(wcsstr(tv.pszText, L"]:")){
					//				t = wcstok(tv.pszText, L":");
					//				for(i = 0; t; t = wcstok(NULL, L":"), i++)token[i] = t;
					//				wcscpy(Function, token[1]);
					//				swprintf(Text, 1024, L"Call '%s'", Function);
					//				AppendMenu(hPopupMenu, MF_STRING, DLL_CALL_FUNCTION,  Text );
					//				AppendMenu(hPopupMenu, MF_STRING, DLL_FUNCTION_DETAILS,  L"Function Details");
					//				AppendMenu(hPopupMenu, MF_STRING, DLL_FUNC_ADD_DETAILS,  L"Add Details");
					//				AppendMenu(hPopupMenu, MF_STRING, DLL_FUNC_MOD_DETAILS,  L"Modify Details");
					//				AppendMenu(hPopupMenu, MF_STRING, DLL_FUNCTION_TRASH_IT,  L"Trash it");

								} else if(wcsstr(tv.pszText, L"Exports")){
									/* nothing here */
								} else if(wcsstr(tv.pszText, L"Base")){
									/* nothing here */
								} else if(wcsstr(tv.pszText, L"Path")){
									AppendMenu(hPopupMenu, MF_STRING, DLL_UNLOAD_MODULE,  TEXT( "Unload Module" ) );
									AppendMenu(hPopupMenu, MF_STRING, DLL_UNLOAD_DELETE_MODULE,  TEXT( "Unload and Delete Module" ) );
								} else {
									AppendMenu(hPopupMenu, MF_STRING, DLL_UNLOAD_MODULE,  TEXT( "Unload Module" ) );
								}

								GetCursorPos( &curPoint ) ;
								SetForegroundWindow(hWnd);
								clicked = TrackPopupMenu(hPopupMenu,
															  TPM_RETURNCMD | TPM_NONOTIFY,
															  curPoint.x, curPoint.y,
															  0, hWnd, NULL);
								if (clicked == DLL_UNLOAD_MODULE){
									if(wcsstr(tv.pszText, L"Path")){
										tv.pszText = tv.pszText + 6;
										UnloadDll(tv.pszText, hWnd, 0);
										DeleteModuleList(hWnd);
										BuildDllList(hWnd);
									} else {
										UnloadDll(tv.pszText, hWnd, 0);
										DeleteModuleList(hWnd);
										BuildDllList(hWnd);
									}
								} else if(clicked == DLL_UNLOAD_DELETE_MODULE){
									tv.pszText = tv.pszText + 6;
									UnloadDll(tv.pszText, hWnd, 1);
									DeleteModuleList(hWnd);
									BuildDllList(hWnd);
								}
							}
						}
					} // tree2 end
					}
					break;
				}	
				break;
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd)
{
	DWORD eof, ICC;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	if(LoadNT() != 1){
		qmb(L"This OS is not supported", L"ERROR");
		eof = (DWORD)ExitProcess;
		__asm {
			push 0
			call eof
		}
	}
	MainMutex = CreateMutex(NULL,FALSE, MUTEXRUN);
	if(GetLastError() == ERROR_ALREADY_EXISTS){
		MessageBoxW(0, L"Ultima Loader is already running!", L"ERROR", MB_ICONERROR);
		KillSelf();
	}

	OutputDebugStringW(L"Ultima Loader Initialized.\n");
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	InitSettings();
//	LocateIniFile();
//	NtZeroMemory(&osvi, sizeof(OSVERSIONINFO));
//	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//	GetVersionEx(&osvi);
//	if(osvi.dwMajorVersion > 5) is_vista_alike = 1;
	ICC = GetAddr("InitCommonControls", L"Comctl32.dll");
	__asm call dword ptr ICC;
//	InitCommonControls();
	OsInfo = SysInfoGet(); 
	PEBlock = RetnPEB();
	CurrentModule = RetnCM();
	swprintf(AllInfo, sizeof(AllInfo), L"OS: %s ::: %s ::: %s", OsInfo, PEBlock, CurrentModule);
	UserLanguage = GetLocalLanguage();
	DialogBoxParam( GetModuleHandle(NULL), 
					MAKEINTRESOURCE(IDD_DIALOG1), 
					NULL, 
					(DLGPROC)MainDialogProc, 
					0);
	Gdiplus::GdiplusShutdown(gdiplusToken);
return 0;
}
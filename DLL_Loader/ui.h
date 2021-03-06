#define EN	0
#define PL	1
#define RU	2

HWND hTool1, hTool2, hTool3, hTool4, hTool5, hTool6, hTool7, hTool8, hTool9, hTool10,
	 hTool11, hTool12, hTool13, hTool14, hTool15, hTool16, hTool17, hTool18, hTool19, hTool20,
	 hTool21, hTool22, hTool23, hTool24, hTool25, hTool26, hTool27;
/***********************************************************************/
// tooltips
// 1
wchar_t *tool_file_select[] = {	L"Select a file to load. Driver file or Dll file.", 
								L"Proszę wybrać plik, który me zostać następnie załadowany. Sterownik albo Dll.", 
								L"Выберите файл для дальнейшей загрузки. Драйвер или Длл."};
// 2
wchar_t *tool_mode_load[] = {	L"Your file will be loaded.", 
								L"Plik zostanie załadowany.", 
								L"Файл будет загружен."};
// 3
wchar_t *tool_mode_unload[] = {	L"Your file will be unloaded if it was loaded earlier with Ultima Loader and wasn't unloaded with 'quick unload' option.", 
								L"Plik zostanie wyładowany jeżeli wcześniej został załadowany przez Ultima Loader i nie został wyładowany poprzez opcję szybkiego wyładowania.", 
								L"Файл будет выгружен, если раньше был загружен этой программой и не был выгружен быстрым методом."};
// 4
wchar_t *tool_exita_unload[] = {L"What Ultima Loader should do with a file after loading it? This option will force a quick unload.", 
								L"Zaznaczenie tej opcji spowoduje szybkie wyładowanie pliku odrazu po tym, jak zostanie załadowany.", 
								L"Выгрузка быстрым методом, т.е. сразу после загрузки файла прога его выгрузит. Применять для банальных драйвер и библиотек с одной Hello World! функцией."};
// 5
wchar_t *tool_exita_delete[] = {L"What Ultima Loader should do with a file after loading it? This option will force file removal.", 
								L"Zaznaczenie tej opcji spowoduje usunięcie pliku po tym, jak zostanie on załadowany.", 
								L"После загрузки файл сразу будет удалён."};
// 6
wchar_t *tool_inj_yes[] = {	L"Use injection. File loading / unloading routine will be injected into another process.", 
							L"Wstrzyknąć ładowanie / wyładowanie pliku do innego procesu.", 
							L"Заинжектить процесс загрузки файла в другой процесс."};
// 7
wchar_t *tool_inj_no[] = {	L"Don't use injection. File will be loaded into Ultima Loader's memory.", 
							L"Nie używać wstrzykiwania. Plik zostanie załadowany do pamięci Ultima Loader'a.", 
							L"Не использовать инжект. Файл будет загружен в память нашей проги."};
// 8
wchar_t *tool_targ_proc[] = {	L"Select target process, in which you want to inject file loading routine.", 
								L"Proszę wybrać proces, do którego zostanie wstrzyknięte ładowanie pliku.", 
								L"Выбрать процесс-жертву, куда будем инжектить наш код."};
// 9
wchar_t *tool_execute[] = {	L"Execute!",
							L"Wykonać!",
							L"Паехали!"};
// 10
wchar_t *tool_trash_buffer[] = {L"Clear debug buffer.", 
								L"Oczyścić okno z logami.", 
								L"Почистить отладочный буффер."};
// 11
wchar_t *tool_to_tray[] = {	L"Place app in system tray.", 
							L"Schować aplikację do systemowego tray'a.", 
							L"Запихать прогу в системный трэй."};
// 12
wchar_t *tool_kill_app[] = {L"Kill Ultima Loader.", 
							L"Zakończyć aplikację.", 
							L"Завершить програмку."};
// 13
wchar_t *tool_ntstatus[] = {L"NTSTATUS codes parser, modifier, database, etc. You can add your own codes and stuff. Just check it out.", 
							L"Parser i edytor kodów NTSTATUS.", 
							L"Модуль, работающий с кодами NTSTATUS. Можно править, добавлять свои, удалять итд. Всё храниться в базе даных (uload.db)."};
// 14
wchar_t *tool_winstatus[]= {L"Standard windows error codes lookup util.", 
							L"Moduł dla wyszukiwania standardowych kodów błędów.", 
							L"Парсер стандартных кодов ошибок."};
// 15
wchar_t *tool_expand[] = {	L"Expand / collapse app window and reveal / hide new options", 
							L"Rozwinąć / zwinąć okno programu.", 
							L"Развернуть / свернуть окошко программы и показать / спрятать новые опции."};
// 16
wchar_t *tool_refresh[] = {	L"Refresh devices and modules lists.", 
							L"Odświeżyć liste załadowanych urządzeń oraz bibliotek.", 
							L"Обновить список девайсов и библиотек."};
// 17
wchar_t *tool_ntapi[]= {L"Use NTAPI for every action. For example NtLoadDriver instead of loading a driver with service control manager, or LdrLoadDll instead of LoadLibraryW. NTAPI will be used for injection as well, so you can inject into native windows processes, like csrss.exe or smss.exe.", 
						L"Globalne użycie NTAPI, np. NtLoadDriver zamiast menadżera, itp. Dla wstrzykiwania również, co pozwala na wstrzykiwanie własnego kodu do procesów, działających w podsystemie NT. (csrss.exe , smss.exe).", 
						L"Юзаем NTAPI. NtLoadDriver вместо SCM и так далее. Также для инжекта, вобщем глобально используются только вызовы NTAPI."};
// 18
wchar_t *tool_winapi[] = {	L"Use WINAPI for every action. Use standard lame win api calls. Just don't ... do.. tha..", 
							L"Użycie WINAPI, dla wszystkiego. Bez komentarza.", 
							L"Используем WINAPI как каждый порядочный прогер. Вобщем камменты тут не нужны - и так всё ясно."};
// 19
wchar_t *tool_style[]= {L"Select Ultima Loader style. Normal look (upper menu and status bar @ app bottom) OR Glamour Style (vista glass, extended border, glowin' text, candy look).", 
						L"Wybór stylu dla aplikacji. Styl normalny albo vista glass.", 
						L"Выбор стиля. Или стандартный (ну там, менюшка наверху, статус бар внизу) или гламур (виста гласс кароче)."};
// 20
wchar_t *tool_debug_buffer[] = {L"A window for a debug buffer. Every status produced by U.Loader will be displayed here.", 
								L"Okienko dla logów. Wszyskie statusy będą tu wyświetlone, wszystko poprostu.", 
								L"Отладочный буфер. Сюда идёт всё, что делает прога. Так что если случится ошибка, искать нужно здесь!"};
// 21
wchar_t *tool_lang_en[] = {	L"Change application language to english.", 
							L"Zmienić język programu na angielski.", 
							L"Сменить язык интэрфейса на английский."};
// 22
wchar_t *tool_lang_pl[] = {	L"Change application language to polish.", 
							L"Zmienić język programu na polski.", 
							L"Сменить язык интэрфейса на польский."};
// 23
wchar_t *tool_lang_ru[] = {	L"Change application language to russian.", 
							L"Zmienić język programu na rosyjski.", 
							L"Сменить язык интэрфейса на русский."};
// 24
wchar_t *tool_device_search[]= {L"Type here a device name that i shall search for.", 
								L"Proszę tu wprowadzić nazwę urządzenia, które ma zostać wyszukane.", 
								L"Имя девайса, который нужно найти, сюда вписываем."};
// 25
wchar_t *tool_dll_search[] = {	L"Type here a module name that i shall search for.", 
								L"Proszę tu wprowadzić nazwę biblioteki, która ma zostać wyszukana.", 
								L"Имя библиотеки ДЛЛ, которую нужно найти, сюда вписываем."};
// 26
wchar_t *tool_devices_list[] = {L"Devices list. Basically, all loaded drivers are gathered here.", 
								L"Lista załadowanych urządzeń. Sterowniki.", 
								L"Список всех подгруженных девайсов. Проще говоря, драйверы + их симлинки."};
// 27
wchar_t *tool_modules_list[] = {L"Modules list. All, loaded into our app, dlls are presented here.", 
								L"Lista załadowanych bibliotek do naszego programu.", 
								L"Список подгруженных в нашу прогу библиотек."};
/***********************************************************************/
#define STATUS_VISTA_GLASS	10
#define STATUS_NO_GLASS		20

typedef struct _MARGINS_EX
{
             int Left;
             int Right; 
             int Top; 
             int Bottom; 
} MARGINS_EX; 

MARGINS_EX Marg;

HWND hStatus;
HMENU hMainUpperMenu;

typedef HRESULT(WINAPI *DEFIC)(HWND hWnd, const MARGINS_EX *pMarInset);
typedef HRESULT(WINAPI *DICE)(bool *pfEnabled);

int __stdcall InitTreeViewHeader(HWND hWnd, int CtrlId){
	LVCOLUMN lvC;
	HWND hList;
	int Status;
	hList = GetDlgItem(hWnd, CtrlId);
	ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT);
	memset(&lvC, 0, sizeof(LVCOLUMN));
	lvC.mask		= LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	lvC.iSubItem	= 0;
	
	lvC.cx			= 70;
	lvC.pszText		= L"Time";
	lvC.fmt			= LVCFMT_LEFT;
	Status = ListView_InsertColumn( hList, 0, &lvC );
	
	lvC.cx			= 320;
	lvC.pszText		= L"Status";
	lvC.fmt			= LVCFMT_LEFT;
	Status = ListView_InsertColumn( hList, 1, &lvC );
	return Status;
}

int __stdcall InsertBufferStatus(HWND hWnd, wchar_t *Text, ...){
	LVITEM lvI;
	va_list ap;	// for processing fucking arguments
	int Status;
	SYSTEMTIME SysTime = {0};
	wchar_t buffer[MAX_PATH];	// this shit is for time handling
	
	wchar_t *MSG;
	int MSG_len = sizeof(wchar_t) * wcslen(Text) + MAX_PATH;
	MSG = (wchar_t *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MSG_len);
	va_start(ap, Text);
	_vsnwprintf(MSG, MSG_len, Text, ap);

	GetSystemTime(&SysTime);	// get shitty system time
	swprintf(buffer, MAX_PATH, L"%d:%d:%d", SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	memset(&lvI, 0, sizeof(LVITEM));
	lvI.mask		= LVIF_TEXT;
	lvI.iSubItem	= 0;
	lvI.pszText		= buffer;
	Status = ListView_InsertItem ( GetDlgItem( hWnd, IDC_LIST1 ), &lvI );	// insert fuck time
	ListView_SetItemText( GetDlgItem( hWnd, IDC_LIST1 ), 0, 1, MSG);	// insert fuck message

	va_end(ap);
	memset(&buffer, 0, sizeof(buffer));
	HeapFree(GetProcessHeap(), 0, MSG);
	return Status;
}

BOOL __stdcall ClearAllBuffer(HWND hWnd, int CtrlId){
	BOOL Status;
	int sucz = ListView_GetItemCount(GetDlgItem( hWnd, CtrlId ));
	while(sucz >= 0){
		Status = ListView_DeleteItem(GetDlgItem( hWnd, CtrlId ), sucz);
		sucz--;
	}
	return Status;
}



int __stdcall PrintUIText(HDC hdc,
						  HWND hWnd,		// main windows handle
						  int FontSize,		// font size, like 12, or 15
						  int TextWidth,	// just a text width
						  int TxtRotation,	// first letter goes down
						  int Italic,		// 1 or 0
						  int Underline,	// 1 or 0
						  wchar_t *Text,	// text we want to be printed
						  long rgbColor,	// RGB color value
						  int FromLeft,		// from left border of main window
						  int FromTop)		// from top border of main window
{
	HFONT m_hfArial = NULL;
	HFONT hfOld;
	LOGFONT lfArial = {
		-MulDiv(FontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72), 
		TextWidth, TxtRotation, 0,
		FW_MEDIUM, Italic, Underline, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, TEXT("Georgia")
	};
	m_hfArial = CreateFontIndirect(&lfArial);
	hfOld = SelectFont(hdc, m_hfArial);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, rgbColor);
	TextOut(hdc,FromLeft,FromTop,Text,wcslen(Text));
return 0;
}

int __stdcall SetButtonIcon(HWND hWnd, int ButtonID, int IconID){
	HWND hUpCtl;
	HICON hU;
	hUpCtl = GetDlgItem( hWnd, ButtonID );
	hU = (HICON)LoadImage( GetModuleHandleW(0),
			MAKEINTRESOURCE( IconID ),
			IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR );
	SendMessage( hUpCtl, BM_SETIMAGE, IMAGE_ICON,
			(LPARAM) (DWORD) hU );
	return 0;
}

int __stdcall EraseTopBottom(int Top, int Bottom, HWND hWnd, HDC hdc){
			RECT lpRect;
			if(!GetClientRect(hWnd, &lpRect)) return -1;
			HBRUSH blueBrush=CreateSolidBrush(RGB(0,0,0));
			lpRect.bottom = Top;
			if(FillRect(hdc, &lpRect, blueBrush) == 0) return -1;

			RECT lpRectEx;
			if(!GetClientRect(hWnd, &lpRectEx)) return -1;
			RECT lol;
			lol.left = 0;
			lol.top =  lpRectEx.bottom - Top - (Bottom - Top);
			lol.right = lpRectEx.right - 0 - 0;
			lol.bottom = lpRectEx.bottom;
			if(FillRect(hdc, &lol, blueBrush) == 0) return -1;
		return 0;
}

HWND CreateToolTip(int toolID, HWND hDlg, PTSTR pszText)
{
    if (!toolID || !hDlg || !pszText)
    {
        return FALSE;
    }
	HINSTANCE g_hInst = (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE);
    // Get the window of the tool.
    HWND hwndTool = GetDlgItem(hDlg, toolID);
    
    // Create the tooltip. g_hInst is the global instance handle.
    HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
                              WS_POPUP |TTS_ALWAYSTIP | TTS_BALLOON,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              hDlg, NULL, 
                              g_hInst, NULL);
    
   if (!hwndTool || !hwndTip)
   {
       return (HWND)NULL;
   }                              
                              
    // Associate the tooltip with the tool.
    TOOLINFO toolInfo = { 0 };
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.hwnd = hDlg;
    toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    toolInfo.uId = (UINT_PTR)hwndTool;
    toolInfo.lpszText = pszText;
    SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
	SendMessage(hwndTip, TTM_SETMAXTIPWIDTH, 0, 300);	// set multiline support
    return hwndTip;
}

HWND CreateStatusBar(HWND hParent, wchar_t *text1, wchar_t *text2, wchar_t *text3){
	HLOCAL hloc;
	LPINT lpParts;
	int i, nWidth;
	int Parts = 3;
	RECT lpRect;
	GetClientRect(hParent, &lpRect);
	HINSTANCE hMainInstance = (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE);
	HWND hStatusBar = CreateWindow( 
                        L"msctls_statusbar32", 
                        NULL,
                        WS_CHILD | WS_VISIBLE, 
                        0, 0, 0, 0,
                        hParent, 
                        NULL,
                        hMainInstance, 
                        (LPVOID)NULL);
	hloc = LocalAlloc(LHND, sizeof(int) * Parts);
	lpParts = (LPINT)LocalLock(hloc);
	nWidth = lpRect.right / Parts;
	for (i = 0; i < Parts; i++) {
		lpParts[i] = nWidth;
		nWidth += nWidth;
	}
	SendMessage(hStatusBar, SB_SETPARTS, (WPARAM)(INT) Parts, (LPARAM)lpParts);
	SendMessage(hStatusBar, SB_SETTEXT, (WPARAM)(INT) 0 | 0, (LPARAM)text1);
	SendMessage(hStatusBar, SB_SETTEXT, (WPARAM)(INT) 1 | 0, (LPARAM)text2);
	SendMessage(hStatusBar, SB_SETTEXT, (WPARAM)(INT) 2 | 0, (LPARAM)text3);
	return hStatusBar;
}

Gdiplus::Bitmap *LoadFromResource(LPCTSTR pName, LPCTSTR pType, HMODULE hInst){
	Gdiplus::Bitmap* m_pBitmap;
	HGLOBAL m_hBuffer;
	HRSRC hResource = FindResource(hInst, pName, pType);
	if (!hResource) return NULL;
	DWORD imageSize = SizeofResource(hInst, hResource);
	if (!imageSize) return NULL;
	const void* pResourceData = LockResource(LoadResource(hInst, hResource));
	if (!pResourceData) return NULL;
	m_hBuffer  = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	if (m_hBuffer){
		void* pBuffer = GlobalLock(m_hBuffer);
		if (pBuffer){
			CopyMemory(pBuffer, pResourceData, imageSize);
			IStream* pStream = NULL;
			if (CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK){
				m_pBitmap = Gdiplus::Bitmap::FromStream(pStream);
				pStream->Release();
				if (m_pBitmap){
					if (m_pBitmap->GetLastStatus() == Gdiplus::Ok){
						return m_pBitmap;
					} else {
						delete m_pBitmap;
						m_pBitmap = NULL;
					}
				}
			} else {
				GlobalUnlock(m_hBuffer);
			}
		} else {
			GlobalFree(m_hBuffer);
			m_hBuffer = NULL;
		}
	} 
	return NULL;
}

int __stdcall SetBkgImage(HWND hWnd,
						  HDC hdc, 
						  int ImgID, 
						  int FromLeft,
						  int FromTop,
						  int Width,
						  int Heigh)
{
	HINSTANCE hIn = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	Gdiplus::Image *image = LoadFromResource(MAKEINTRESOURCE(ImgID), L"PNG", hIn);
	Gdiplus::Rect destRect(FromLeft, FromTop, Width, Heigh);
	Gdiplus::Graphics gr(hdc);
	gr.DrawImage ( image, destRect );
	return 0;
}

int __stdcall InitGlass(HWND hWnd, bool ModeEx, wchar_t *text1, wchar_t *text2, wchar_t *text3){
	unsigned int Status;
//	bool Mode;
	bool glassEnabled = false;
//	TranslitOptions.debug_info == 1 ? Mode = true : Mode = false;
	HMODULE hDwm = LoadLibraryW(L"dwmapi.dll");
	if(!hDwm) {
		OutputDebugStringW(L"Initializing vista glass error! Unable to load dwmapi.dll.\r\n");
		Status = -1;
	}
	else {
		DEFIC pfnDwmExtendFrameIntoClientArea = 
			(DEFIC) GetProcAddress(hDwm, "DwmExtendFrameIntoClientArea");
		DICE pfnDwmIsCompositionEnabled = 
			(DICE) GetProcAddress(hDwm, "DwmIsCompositionEnabled");
		if(!pfnDwmExtendFrameIntoClientArea || !pfnDwmIsCompositionEnabled){
			OutputDebugStringW(L"Initializing vista glass error! Key functions not found.\r\n");
			return -3;
		}
		if(pfnDwmIsCompositionEnabled(&glassEnabled) == S_OK){
			Marg.Left = 0;
			Marg.Right = 0;
			if(ModeEx){
				Marg.Top = 30; 
				Marg.Bottom = 30;
			} else {
				Marg.Top = 0; 
				Marg.Bottom = 0;
			}
			pfnDwmExtendFrameIntoClientArea(hWnd,&Marg);
			if(ModeEx){
				if(hStatus)DestroyWindow(hStatus);
				SetMenu(hWnd, NULL);
				Status = STATUS_VISTA_GLASS;
			} else {
				SetMenu(hWnd, hMainUpperMenu);
				hStatus = CreateStatusBar(hWnd, text1, text2, text3);
				Status = STATUS_NO_GLASS;
			}
		} else {
			OutputDebugStringW(L"Initializing vista glass error! Composition is not enabled.\r\n");
			Status = -2;
		}
	}
	return Status;
}

void ClientResize(HWND hWnd, int nWidth, int nHeight)
{
  RECT rcClient, rcWind;
  POINT ptDiff;
  GetClientRect(hWnd, &rcClient);
  GetWindowRect(hWnd, &rcWind);
  ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
  ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;
  MoveWindow(hWnd,rcWind.left, rcWind.top, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);
}

typedef HANDLE HTHEME;
#define RECTWIDTH(lpRect) ((lpRect).right - (lpRect).left)
#define RECTHEIGHT(lpRect) ((lpRect).bottom - (lpRect).top)
typedef int (WINAPI *DTT_CALLBACK_PROC)(HDC hdc,
										LPWSTR pszText,
										int cchText,
										LPRECT prc,
										UINT dwFlags,
										LPARAM lParam);
typedef struct _DTTOPTS {
  DWORD             dwSize;
  DWORD             dwFlags;
  COLORREF          crText;
  COLORREF          crBorder;
  COLORREF          crShadow;
  int               iTextShadowType;
  POINT             ptShadowOffset;
  int               iBorderSize;
  int               iFontPropId;
  int               iColorPropId;
  int               iStateId;
  BOOL              fApplyOverlay;
  int               iGlowSize;
  DTT_CALLBACK_PROC pfnDrawTextCallback;
  LPARAM            lParam;
} DTTOPTS, *PDTTOPTS;
#define DTT_COMPOSITED (1UL << 13)
#define DTT_GLOWSIZE (1UL << 11)
#define TMT_CAPTIONFONT 0x0321

typedef HTHEME(WINAPI *OPENTD)(HWND hwnd, LPCWSTR pszClassList);	//UxTheme.dll
typedef HRESULT (WINAPI *GETTSF)(HTHEME hTheme, int iFontID, LOGFONTW *plf);
typedef HRESULT  (WINAPI *DRAWTTE)(	__in     HTHEME hTheme,
									__in     HDC hdc,
									__in     int iPartId,
									__in     int iStateId,
									__in     LPCWSTR pszText,
									__in     int iCharCount,
									__in     DWORD dwFlags,
									__inout  LPRECT pRect,
									__in     const DTTOPTS *pOptions);
typedef HRESULT (WINAPI *CLOSETD)(__in  HTHEME hTheme);

int OutputGlowingText(	HWND hWnd, 
						HDC hdc, 
						wchar_t *szTitle, 
						int FromTopBorder,
						int FromLeftBorder)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
	HMODULE hUx = LoadLibraryW(L"UxTheme.dll");
	OPENTD pfnOpenThemeData = 
			(OPENTD) GetProcAddress(hUx, "OpenThemeData");
	GETTSF pfnGetThemeSysFont = 
			(GETTSF) GetProcAddress(hUx, "GetThemeSysFont");
	DRAWTTE pfnDrawThemeTextEx = 
			(DRAWTTE) GetProcAddress(hUx, "DrawThemeTextEx");
	CLOSETD pfnCloseThemeData = 
			(CLOSETD) GetProcAddress(hUx, "CloseThemeData");

    HTHEME hTheme = pfnOpenThemeData(NULL, L"Button");
    if (hTheme){
        HDC hdcPaint = CreateCompatibleDC(hdc);
        if (hdcPaint){
            int cx = RECTWIDTH(rcClient);
            int cy = RECTHEIGHT(rcClient);
			int BIT_COUNT = 32;
            BITMAPINFO dib = { 0 };
            dib.bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
            dib.bmiHeader.biWidth           = cx;
            dib.bmiHeader.biHeight          = -cy;
            dib.bmiHeader.biPlanes          = 1;
            dib.bmiHeader.biBitCount        = BIT_COUNT;
            dib.bmiHeader.biCompression     = BI_RGB;

            HBITMAP hbm = CreateDIBSection(hdc, &dib, DIB_RGB_COLORS, NULL, NULL, 0);
            if (hbm){
                HBITMAP hbmOld = (HBITMAP)SelectObject(hdcPaint, hbm);

                // Setup the theme drawing options.
                DTTOPTS DttOpts = {sizeof(DTTOPTS)};
                DttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
                DttOpts.iGlowSize = 10;
				DttOpts.crText   = RGB(255, 255, 255);
                // Select a font.
                LOGFONT lgFont;
                HFONT hFontOld = NULL;
                if (SUCCEEDED(pfnGetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont))){
                    HFONT hFont = CreateFontIndirect(&lgFont);
                    hFontOld = (HFONT) SelectObject(hdcPaint, hFont);
                }

                // Draw the title.
                RECT rcPaint = rcClient;
				rcPaint.top = FromTopBorder-(RECTHEIGHT(rcClient)-Marg.Bottom);
				rcPaint.left = FromLeftBorder;
                pfnDrawThemeTextEx(hTheme, 
                                hdcPaint, 
                                0, 0, 
                                szTitle, 
                                -1, 
                                DT_CENTER | DT_WORD_ELLIPSIS | DT_SINGLELINE, 
                                &rcPaint, 
                                &DttOpts);

                // Blit text to the frame.
//                BitBlt(hdc, 0, 5, cx, cy, hdcPaint, 0, 0, SRCCOPY);
				BitBlt(hdc, 0, RECTHEIGHT(rcClient)-Marg.Bottom, cx, cy, hdcPaint, 0, 0, SRCCOPY);
                SelectObject(hdcPaint, hbmOld);
                if (hFontOld) SelectObject(hdcPaint, hFontOld);
                DeleteObject(hbm);
            } else return -2; // CreateDIBSection failed
			ReleaseDC(hWnd, hdcPaint);
            DeleteDC(hdcPaint);
        } else return -1; // CreateCompatibleDC failed
        pfnCloseThemeData(hTheme);
    } else return -3; // pfnOpenThemeData failed
return 0;
}


int __stdcall MakeTooltips(HWND hWnd, int Lang){
	hTool1 = CreateToolTip(IDC_BUTTON1, hWnd, tool_file_select[Lang]);
	hTool2 = CreateToolTip(IDC_RADIO1, hWnd, tool_mode_load[Lang]);
	hTool3 = CreateToolTip(IDC_RADIO2, hWnd, tool_mode_unload[Lang]);
	hTool4 = CreateToolTip(IDC_CHECK1, hWnd, tool_exita_unload[Lang]);
	hTool5 = CreateToolTip(IDC_CHECK2, hWnd, tool_exita_delete[Lang]);
	hTool6 = CreateToolTip(IDC_RADIO3, hWnd, tool_inj_yes[Lang]);
	hTool7 = CreateToolTip(IDC_RADIO4, hWnd, tool_inj_no[Lang]);
	hTool8 = CreateToolTip(IDC_COMBO1, hWnd, tool_targ_proc[Lang]);
	hTool9 = CreateToolTip(IDOK, hWnd, tool_execute[Lang]);
	hTool10 = CreateToolTip(IDC_BUTTON4, hWnd, tool_trash_buffer[Lang]);
	hTool11 = CreateToolTip(IDCANCEL, hWnd, tool_to_tray[Lang]);
	hTool12 = CreateToolTip(IDC_BUTTON3, hWnd, tool_kill_app[Lang]);
	hTool13 = CreateToolTip(IDC_BUTTON2, hWnd, tool_ntstatus[Lang]);
	hTool14 = CreateToolTip(IDC_BUTTON5, hWnd, tool_winstatus[Lang]);
	hTool15 = CreateToolTip(IDC_BUTTON6, hWnd, tool_expand[Lang]);
	hTool16 = CreateToolTip(IDC_BUTTON7, hWnd, tool_refresh[Lang]);
	hTool17 = CreateToolTip(IDC_RADIO5, hWnd, tool_ntapi[Lang]);
	hTool18 = CreateToolTip(IDC_RADIO6, hWnd, tool_winapi[Lang]);
	hTool19 = CreateToolTip(IDC_COMBO2, hWnd, tool_style[Lang]);
	hTool20 = CreateToolTip(IDC_LIST1, hWnd, tool_debug_buffer[Lang]);
	hTool21 = CreateToolTip(IDC_RADIO7, hWnd, tool_lang_en[Lang]);
	hTool22 = CreateToolTip(IDC_RADIO8, hWnd, tool_lang_pl[Lang]);
	hTool23 = CreateToolTip(IDC_RADIO9, hWnd, tool_lang_ru[Lang]);
	hTool24 = CreateToolTip(IDC_EDIT1, hWnd, tool_device_search[Lang]);
	hTool25 = CreateToolTip(IDC_EDIT2, hWnd, tool_dll_search[Lang]);
	hTool26 = CreateToolTip(IDC_TREE1, hWnd, tool_devices_list[Lang]);
	hTool27 = CreateToolTip(IDC_TREE2, hWnd, tool_modules_list[Lang]);
	return 0;
}

int __stdcall DestroyTooltips(){
	DestroyWindow(hTool1); DestroyWindow(hTool2); DestroyWindow(hTool3);
	DestroyWindow(hTool4); DestroyWindow(hTool5); DestroyWindow(hTool6);
	DestroyWindow(hTool7); DestroyWindow(hTool8); DestroyWindow(hTool9);
	DestroyWindow(hTool10); DestroyWindow(hTool11); DestroyWindow(hTool12);
	DestroyWindow(hTool13); DestroyWindow(hTool14); DestroyWindow(hTool15);
	DestroyWindow(hTool16); DestroyWindow(hTool17); DestroyWindow(hTool18);
	DestroyWindow(hTool19); DestroyWindow(hTool20); DestroyWindow(hTool21);
	DestroyWindow(hTool22); DestroyWindow(hTool23); DestroyWindow(hTool24);
	DestroyWindow(hTool25); DestroyWindow(hTool26); DestroyWindow(hTool27);
	return 1;
}
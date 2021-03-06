
int __stdcall MakeRussian(HWND hWnd){
	SendDlgItemMessage (hWnd, IDC_RADIO1, WM_SETTEXT, 0, (LPARAM) L"Загрузить файл");
	SendDlgItemMessage (hWnd, IDC_RADIO2, WM_SETTEXT, 0, (LPARAM) L"Выгрузить файл");
	SendDlgItemMessage (hWnd, IDC_RADIO3, WM_SETTEXT, 0, (LPARAM) L"Инжект");
	SendDlgItemMessage (hWnd, IDC_RADIO4, WM_SETTEXT, 0, (LPARAM) L"Без инжекта");
	SendDlgItemMessage (hWnd, IDC_CHECK1, WM_SETTEXT, 0, (LPARAM) L"Выгрузить файл");
	SendDlgItemMessage (hWnd, IDC_CHECK2, WM_SETTEXT, 0, (LPARAM) L"Удалить файл");
	SendDlgItemMessage (hWnd, IDC_BUTTON1, WM_SETTEXT, 0, (LPARAM) L"Выбрать файл для загрузки");
	SendDlgItemMessage (hWnd, IDC_BUTTON2, WM_SETTEXT, 0, (LPARAM) L"Инфо");
	SendDlgItemMessage (hWnd, IDC_BUTTON3, WM_SETTEXT, 0, (LPARAM) L"Выход");
	SendDlgItemMessage (hWnd, IDC_BUTTON4, WM_SETTEXT, 0, (LPARAM) L"Очистить");
	SendDlgItemMessage (hWnd, IDCANCEL, WM_SETTEXT, 0, (LPARAM) L"В трэй");
	SendDlgItemMessage (hWnd, IDOK, WM_SETTEXT, 0, (LPARAM) L"Запуск");
	
	Clear(file_not_selected); Clear(no_proc_for_inj);
	Clear(cannot_open_file); Clear(cannot_check_file);
	Clear(not_win_exe); Clear(dll_detected);
	Clear(sys_detected); Clear(unknown_file);
	Clear(loading_file); Clear(unloading_file);
	Clear(dll_unloaded); Clear(dll_loaded);
	Clear(sys_unloaded); Clear(sys_loaded);
	Clear(file_deleted); Clear(dll_not_found_mem);
	Clear(dll_found_mem); Clear(dll_unload_failed);
	Clear(sys_unload_failed); Clear(sys_load_failed);
	Clear(dll_load_failed);

	Clear(pid_failed); Clear(pid_ok);
	Clear(proc_open_failed); Clear(proc_open_ok);
	Clear(virtmemaloc_failed); Clear(virtmemaloc_ok);
	Clear(virtmemwrite_failed); Clear(virtmemwrite_ok);

	Clear(file_not_found); Clear(load_dll_failed);
	Clear(unload_dll_failed); Clear(dllisnotinmem);
	Clear(injected_ok); Clear(injection_err);
	Clear(firstinj_err);

	wcscpy(file_not_selected, L"[-] Файл не выбран!\r\n");
	wcscpy(no_proc_for_inj, L"[-] Процес для инжекта не выбран!\r\n");
	wcscpy(cannot_open_file, L"[-] Не получается открыть файл!\r\n");
	wcscpy(cannot_check_file, L"[-] Не получается проверить файл!\r\n");
	wcscpy(not_win_exe, L"[-] Это не исполняемый файл!\r\n");
	wcscpy(dll_detected, L"[+] Обнаружена Dll.\r\n");
	wcscpy(sys_detected, L"[+] Обнаружен драйвер.\r\n");
	wcscpy(unknown_file, L"[-] Файл не распознан!\r\n");
	wcscpy(loading_file, L"Загружаем");
	wcscpy(unloading_file, L"Выгружаем");
	wcscpy(dll_unloaded, L"[+] Dll успешно выгружена.\r\n");
	wcscpy(dll_loaded, L"[+] Dll успешно загружена.\r\n");
	wcscpy(sys_unloaded, L"[+] Драйвер успешно выгружен.\r\n");
	wcscpy(sys_loaded, L"[+] Драйвер успешно загружен.\r\n");
	wcscpy(file_deleted, L"[+] Файл успешно удалён.\r\n");
	wcscpy(dll_not_found_mem, L"[-] Dll не обнаружена в памяти процеса.\r\n");
	wcscpy(dll_found_mem, L"[+] Dll обнаружена в памяти процеса.\r\n");
	wcscpy(dll_unload_failed, L"[-] Невозможно выгрузить Dll!\r\n");
	wcscpy(sys_unload_failed, L"[-] Невозможно выгрузить драйвер!\r\n");
	wcscpy(sys_load_failed, L"[-] Невозможно загрузить драйвер!\r\n");
	wcscpy(dll_load_failed, L"[-] Невозможно загрузить Dll!\r\n");

	wcscpy(pid_failed, L"[-] Невозможно получить PID процеса!\r\n");
	wcscpy(pid_ok, L"[+] PID получен.\r\n");
	wcscpy(proc_open_failed, L"[-] Невозможно открыть процес для внедрения!\r\n");
	wcscpy(proc_open_ok, L"[+] Процес для внедрения открыт.\r\n");
	wcscpy(virtmemaloc_failed, L"[-] Невозможно зарезервировать участок виртуальной памяти!\r\n");
	wcscpy(virtmemaloc_ok, L"[+] Участок виртуальной памяти зарезервирован.\r\n");
	wcscpy(virtmemwrite_failed, L"[-] Невозможно записать в виртуальную память!\r\n");
	wcscpy(virtmemwrite_ok, L"[+] Запись в виртуальную память - ОК.\r\n");

	wcscpy(file_not_found, L"DLL не найдена!");
	wcscpy(load_dll_failed, L"Ошибка во время загрузки DLL!");
	wcscpy(unload_dll_failed, L"Ошибка во время выгрузки DLL!");
	wcscpy(dllisnotinmem, L"DLL не найдена в памяти процеса!");
	wcscpy(injected_ok, L"[+] Загрузка заинжектена в процес.\r\n");
	wcscpy(injection_err, L"[-] Инжект провалился. /me сдался.\r\n");
	wcscpy(firstinj_err, L"[-] Инжект провалился. Пробуем заинжектиться иначе..\r\n");
	return 0;
}

int __stdcall MakePolish(HWND hWnd){
	SendDlgItemMessage (hWnd, IDC_RADIO1, WM_SETTEXT, 0, (LPARAM) L"Załadować Plik");
	SendDlgItemMessage (hWnd, IDC_RADIO2, WM_SETTEXT, 0, (LPARAM) L"Wyładować Plik");
	SendDlgItemMessage (hWnd, IDC_RADIO3, WM_SETTEXT, 0, (LPARAM) L"Wstrzyknięcie");
	SendDlgItemMessage (hWnd, IDC_RADIO4, WM_SETTEXT, 0, (LPARAM) L"Normalny Tryb");
	SendDlgItemMessage (hWnd, IDC_CHECK1, WM_SETTEXT, 0, (LPARAM) L"Wyładować Plik");
	SendDlgItemMessage (hWnd, IDC_CHECK2, WM_SETTEXT, 0, (LPARAM) L"Usunąć Plik");
	SendDlgItemMessage (hWnd, IDC_BUTTON1, WM_SETTEXT, 0, (LPARAM) L"Wybrać Plik");
	SendDlgItemMessage (hWnd, IDC_BUTTON2, WM_SETTEXT, 0, (LPARAM) L"Info");
	SendDlgItemMessage (hWnd, IDC_BUTTON3, WM_SETTEXT, 0, (LPARAM) L"Wyjście");
	SendDlgItemMessage (hWnd, IDC_BUTTON4, WM_SETTEXT, 0, (LPARAM) L"Oczyścić");
	SendDlgItemMessage (hWnd, IDCANCEL, WM_SETTEXT, 0, (LPARAM) L"Do tray'a");
	SendDlgItemMessage (hWnd, IDOK, WM_SETTEXT, 0, (LPARAM) L"Wykonać");

	Clear(file_not_selected); Clear(no_proc_for_inj);
	Clear(cannot_open_file); Clear(cannot_check_file);
	Clear(not_win_exe); Clear(dll_detected);
	Clear(sys_detected); Clear(unknown_file);
	Clear(loading_file); Clear(unloading_file);
	Clear(dll_unloaded); Clear(dll_loaded);
	Clear(sys_unloaded); Clear(sys_loaded);
	Clear(file_deleted); Clear(dll_not_found_mem);
	Clear(dll_found_mem); Clear(dll_unload_failed);
	Clear(sys_unload_failed); Clear(sys_load_failed);
	Clear(dll_load_failed);

	Clear(pid_failed); Clear(pid_ok);
	Clear(proc_open_failed); Clear(proc_open_ok);
	Clear(virtmemaloc_failed); Clear(virtmemaloc_ok);
	Clear(virtmemwrite_failed); Clear(virtmemwrite_ok);

	Clear(file_not_found); Clear(load_dll_failed);
	Clear(unload_dll_failed); Clear(dllisnotinmem);
	Clear(injected_ok); Clear(injection_err);
	Clear(firstinj_err);

	wcscpy(file_not_selected, L"[-] Plik nie został wybrany!\r\n");
	wcscpy(no_proc_for_inj, L"[-] Process dla wstrzyknięcia nie został wybrany!\r\n");
	wcscpy(cannot_open_file, L"[-] Nie da się otworzyć plik!\r\n");
	wcscpy(cannot_check_file, L"[-] Nie da się sprawdzić plik!\r\n");
	wcscpy(not_win_exe, L"[-] To nie jest wykonywalny plik!\r\n");
	wcscpy(dll_detected, L"[+] Rozpoznano Dll.\r\n");
	wcscpy(sys_detected, L"[+] Rozpoznano sterownik.\r\n");
	wcscpy(unknown_file, L"[-] Plik nie został rozpoznany!\r\n");
	wcscpy(loading_file, L"Ładujemy");
	wcscpy(unloading_file, L"Wyładowujemy");
	wcscpy(dll_unloaded, L"[+] Dll wyładowana pomyślnie.\r\n");
	wcscpy(dll_loaded, L"[+] Dll załadowana pomyślnie.\r\n");
	wcscpy(sys_unloaded, L"[+] Sterownik wyładowany pomyślnie.\r\n");
	wcscpy(sys_loaded, L"[+] Sterownik załadowany pomyślnie.\r\n");
	wcscpy(file_deleted, L"[+] Plik usunięty pomyślnie.\r\n");
	wcscpy(dll_not_found_mem, L"[-] Dll nie znaleziona w pamięci procesu.\r\n");
	wcscpy(dll_found_mem, L"[+] Dll znaleziona w pamięci procesu.\r\n");
	wcscpy(dll_unload_failed, L"[-] Nie da się wyładować Dll!\r\n");
	wcscpy(sys_unload_failed, L"[-] Nie da się wyładować sterownik!\r\n");
	wcscpy(sys_load_failed, L"[-] Nie da się załadować sterownik!\r\n");
	wcscpy(dll_load_failed, L"[-] Nie da się załadować Dll!\r\n");

	wcscpy(pid_failed, L"[-] Nie udało się otrzymać identyfikator procesu!\r\n");
	wcscpy(pid_ok, L"[+] Identyfikator procesu otrzymany.\r\n");
	wcscpy(proc_open_failed, L"[-] Nie da się otworzyć process dla wstrzyknięcia!\r\n");
	wcscpy(proc_open_ok, L"[+] Process dla wstrzyknięcie otwarty.\r\n");
	wcscpy(virtmemaloc_failed, L"[-] Nie da się przydzielić pamięć wirtualną!\r\n");
	wcscpy(virtmemaloc_ok, L"[+] Pamięć wirtualna przydzielona.\r\n");
	wcscpy(virtmemwrite_failed, L"[-] Nie da się zapisać do pamięci wirtualnej!\r\n");
	wcscpy(virtmemwrite_ok, L"[+] Zapisano do pamięci wirtualnej.\r\n");

	wcscpy(file_not_found, L"Nie odnaleziono DLL!");
	wcscpy(load_dll_failed, L"Błąd podczas ładowania DLL!");
	wcscpy(unload_dll_failed, L"Błąd podczas wyładowania DLL!");
	wcscpy(dllisnotinmem, L"DLL nie odnaleziono w pamięci procesu!");
	wcscpy(injected_ok, L"[+] Ładowanie wstrzyknięto do procesu.\r\n");
	wcscpy(injection_err, L"[-] Wstrzyknięcie nie powiodło się.\r\n");
	wcscpy(firstinj_err, L"[-] Wstrzyknięcie nie powiodło się. Próbujemy inaczej.\r\n");

return 0;
}

int __stdcall MakeEnglish(HWND hWnd){
	SendDlgItemMessage (hWnd, IDC_RADIO1, WM_SETTEXT, 0, (LPARAM) L"Load file");
	SendDlgItemMessage (hWnd, IDC_RADIO2, WM_SETTEXT, 0, (LPARAM) L"Unload file");
	SendDlgItemMessage (hWnd, IDC_RADIO3, WM_SETTEXT, 0, (LPARAM) L"Injection");
	SendDlgItemMessage (hWnd, IDC_RADIO4, WM_SETTEXT, 0, (LPARAM) L"Regular Mode");
	SendDlgItemMessage (hWnd, IDC_CHECK1, WM_SETTEXT, 0, (LPARAM) L"Unload file");
	SendDlgItemMessage (hWnd, IDC_CHECK2, WM_SETTEXT, 0, (LPARAM) L"Delete file");
	SendDlgItemMessage (hWnd, IDC_BUTTON1, WM_SETTEXT, 0, (LPARAM) L"Select file");
	SendDlgItemMessage (hWnd, IDC_BUTTON2, WM_SETTEXT, 0, (LPARAM) L"Info");
	SendDlgItemMessage (hWnd, IDC_BUTTON3, WM_SETTEXT, 0, (LPARAM) L"Quit");
	SendDlgItemMessage (hWnd, IDC_BUTTON4, WM_SETTEXT, 0, (LPARAM) L"CLear");
	SendDlgItemMessage (hWnd, IDCANCEL, WM_SETTEXT, 0, (LPARAM) L"To tray");
	SendDlgItemMessage (hWnd, IDOK, WM_SETTEXT, 0, (LPARAM) L"Execute!");

	Clear(file_not_selected); Clear(no_proc_for_inj);
	Clear(cannot_open_file); Clear(cannot_check_file);
	Clear(not_win_exe); Clear(dll_detected);
	Clear(sys_detected); Clear(unknown_file);
	Clear(loading_file); Clear(unloading_file);
	Clear(dll_unloaded); Clear(dll_loaded);
	Clear(sys_unloaded); Clear(sys_loaded);
	Clear(file_deleted); Clear(dll_not_found_mem);
	Clear(dll_found_mem); Clear(dll_unload_failed);
	Clear(sys_unload_failed); Clear(sys_load_failed);
	Clear(dll_load_failed);

	Clear(pid_failed); Clear(pid_ok);
	Clear(proc_open_failed); Clear(proc_open_ok);
	Clear(virtmemaloc_failed); Clear(virtmemaloc_ok);
	Clear(virtmemwrite_failed); Clear(virtmemwrite_ok);

	Clear(file_not_found); Clear(load_dll_failed);
	Clear(unload_dll_failed); Clear(dllisnotinmem);
	Clear(injected_ok); Clear(injection_err);
	Clear(firstinj_err);

	wcscpy(file_not_selected, L"[-] File not specified!\r\n");
	wcscpy(no_proc_for_inj, L"[-] Injection specified but no process selected!\r\n");
	wcscpy(cannot_open_file, L"[-] Could not open File!\r\n");
	wcscpy(cannot_check_file, L"[-] Could not check file!\r\n");
	wcscpy(not_win_exe, L"[-] Looks like it is not windows executable!\r\n");
	wcscpy(dll_detected, L"[+] DLL Detected.\r\n");
	wcscpy(sys_detected, L"[+] Driver Detected.\r\n");
	wcscpy(unknown_file, L"[-] File format not recognized!\r\n");
	wcscpy(loading_file, L"Loading file");
	wcscpy(unloading_file, L"Unloading file");
	wcscpy(dll_unloaded, L"[+] Dll Successfuly Unloaded.\r\n");
	wcscpy(dll_loaded, L"[+] Dll Successfuly Loaded.\r\n");
	wcscpy(sys_unloaded, L"[+] Driver Successfuly Unloaded.\r\n");
	wcscpy(sys_loaded, L"[+] Driver Successfuly Loaded.\r\n");
	wcscpy(file_deleted, L"[+] File Successfuly Deleted.\r\n");
	wcscpy(dll_not_found_mem, L"[-] DLL not found in process memory.\r\n");
	wcscpy(dll_found_mem, L"[+] DLL found in process memory.\r\n");
	wcscpy(dll_unload_failed, L"[-] Unable to unload DLL!\r\n");
	wcscpy(sys_unload_failed, L"[-] Driver could not be unloaded!\r\n");
	wcscpy(sys_load_failed, L"[-] Driver could not be loaded!\r\n");
	wcscpy(dll_load_failed, L"[-] Loading Dll Failed!\r\n");

	wcscpy(pid_failed, L"[-] Unable to get target process ID!\r\n");
	wcscpy(pid_ok, L"[+] Got proc ID.\r\n");
	wcscpy(proc_open_failed, L"[-] Unable to open target process!\r\n");
	wcscpy(proc_open_ok, L"[+] Target proc opened.\r\n");
	wcscpy(virtmemaloc_failed, L"[-] Unable to alocate virtual memory!\r\n");
	wcscpy(virtmemaloc_ok, L"[+] Virtual memory alocated.\r\n");
	wcscpy(virtmemwrite_failed, L"[-] Unable to write virtual memory!\r\n");
	wcscpy(virtmemwrite_ok, L"[+] Virtual memory written.\r\n");

	wcscpy(file_not_found, L"Dll Not Found!");
	wcscpy(load_dll_failed, L"Dll Loading error!");
	wcscpy(unload_dll_failed, L"Dll unloading error!");
	wcscpy(dllisnotinmem, L"Dll is not in this process's memory!");
	wcscpy(injected_ok, L"[+] Injected.\r\n");
	wcscpy(injection_err, L"[-] Injection failed! Giving up.\r\n");
	wcscpy(firstinj_err, L"[-] First injection attempt failed! Trying another way...\r\n");

return 0;
}
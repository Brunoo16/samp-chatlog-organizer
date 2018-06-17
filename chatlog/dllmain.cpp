#include "dllmain.h"

static void Thread()
{
	static char file_name_and_path[MAX_PATH];

	if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, file_name_and_path) == S_OK)
	{
		strcat(file_name_and_path, "\\GTA San Andreas User Files\\SAMP\\Chatlogs");

		if (CreateDirectoryA(file_name_and_path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			DWORD OldProtect = NULL, offsets[2] = { NULL }, samp = (DWORD)GetModuleHandleA("samp.dll");

			if (*(BYTE*)(samp + 0x129) == 0xF4) // 0.3.7-R1
			{
				offsets[0] = 0x270E88 + 0x4;
				offsets[1] = 0x309E05 + 0x4;
			}
			else if (*(BYTE*)(samp + 0x129) == 0xC) // 0.3.7-R2
			{
				offsets[0] = 0x243F91 + 0x4;
				offsets[1] = 0x25E750 + 0x4;
			}
			else return;
			 
			time_t now = time(0);

			struct tm* current_time = localtime(&now); 

			sprintf(file_name_and_path, "%s\\%d-%.2d-%.2d %.2d.%.2d.%.2d.txt", file_name_and_path, current_time->tm_year + 1900, current_time->tm_mon + 1, current_time->tm_mday, current_time->tm_hour, current_time->tm_min, current_time->tm_sec);

			VirtualProtect((void*)(samp + offsets[0]), 4, PAGE_EXECUTE_READWRITE, &OldProtect);
			VirtualProtect((void*)(samp + offsets[1]), 4, PAGE_EXECUTE_READWRITE, &OldProtect);

			*(DWORD*)(samp + offsets[0]) = (DWORD)&file_name_and_path;
			*(DWORD*)(samp + offsets[1]) = (DWORD)&file_name_and_path;
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
	}
	return 1;
}
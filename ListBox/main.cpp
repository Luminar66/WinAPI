﻿#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdio>
#include "resource.h"

CONST CHAR* g_sz_STRING[] = { "This", "is", "my", "First", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_sz_STRING) / sizeof(g_sz_STRING[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_sz_STRING[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		CHAR sz_message[SIZE] = {};
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали пункт N%i, со значением %s", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}
#include <windows.h>
#include <tchar.h> // for unicode
#include "DxMainWindow.h"

LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);

INT
WINAPI
_tWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPTSTR lpCmdLine,
	INT nCmdShow
) {
	
	DxMainWindow dx(hInst);
	dx.setup();
	return dx.start();
}
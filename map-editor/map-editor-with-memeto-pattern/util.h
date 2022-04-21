#pragma once

#define TO_LAMBDA(self, method, args , shape) \
[self]shape { \
	return self->method args; \
}

#define TO_WINDOW_PROC_LAMBDA(self, method) TO_LAMBDA(self, method, (hWnd, uMsg, wParam, lParam), (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT)


#define SAFE_RELEASE_DELETE(t) { if (t!=0) { t->Release(); delete t; t = 0; } }
#define SAFE_DELETE(t) { if (t!=0) { delete t; t = 0; } }
#define SAFE_RELEASE(t)	{ if (t!=0) { t->Release(); t = 0; } }
#define SAFE_DELETE_ARRAY(arr) { if (arr!=0) { delete[] arr; arr = 0; } }

#define IS_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000) == 0x8000)
#include "Context.h"

HWND const Context::getHandleWindow() {
	return this->hWnd;
}

LPDIRECT3DDEVICE9 const Context::getD3DDevice() {
	return this->d3dDevice;
}

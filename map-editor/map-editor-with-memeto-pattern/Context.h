#pragma once

#include <Windows.h>

#include "d3dx9.h"
#include "d3d9.h"

class Context {
public:
	Context(HWND hWnd, LPDIRECT3DDEVICE9 d3dDevice) : hWnd(hWnd), d3dDevice(d3dDevice) { }

	HWND const getHandleWindow();
	LPDIRECT3DDEVICE9 const getD3DDevice();
protected:
	LPDIRECT3DDEVICE9 d3dDevice;
	HWND hWnd;
};


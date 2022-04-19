#pragma once

#include "d3dx9.h"
#include "d3d9.h"

#pragma comment(lib, "d3d9.lib" )
#pragma comment(lib, "d3dx9.lib" )

#include "MainWindow.h"
#include "Timer.h"

class DxMainWindow : public MainWindow {
public:
	DxMainWindow(HINSTANCE hInst);

	INT start();

protected:
	bool onAttach();
	void onDetach();

	void release();

private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3dDevice;
};


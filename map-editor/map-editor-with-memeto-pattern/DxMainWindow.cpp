#include "DxMainWindow.h"

DxMainWindow::DxMainWindow(HINSTANCE hInst) : MainWindow(hInst), d3d(nullptr), d3dDevice(nullptr) {

}

INT DxMainWindow::start() {
	if (!this->canShowWindow() || !this->onAttach()) {
		return -1;
	}
	this->showWindow();

	while (true) {
		peekingMessage();
		if (needQuit()) {
			break;
		}

		this->d3dDevice->Clear(
			0, 0,
			D3DCLEAR_TARGET,
			D3DCOLOR_XRGB(2, 95, 209),
			1.f, // zbuffer
			0.f // 스텐실 버퍼
		); 

		if (SUCCEEDED(this->d3dDevice->BeginScene())) {
			// TODO: render
			this->d3dDevice->EndScene();
		}

		if (this->d3dDevice->Present(0, 0, 0, 0) == D3DERR_DEVICELOST) {
			// TODO: restore device
		}
	}

	this->onDetach();
	return getPeekedMessage()->wParam;
}

bool DxMainWindow::onAttach() {
	this->d3d = ::Direct3DCreate9(D3D_SDK_VERSION);

	// TODO: 디바이스 초기화 함수는 별도로 제공하는게 나을듯
	D3DPRESENT_PARAMETERS d3dParams;
	::ZeroMemory(&d3dParams, sizeof(d3dParams));

	d3dParams.Windowed = true; // 창모드
	d3dParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dParams.BackBufferWidth = this->width;
	d3dParams.BackBufferHeight = this->height;

	d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		this->hMainWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dParams,
		&this->d3dDevice
	);

	return this->d3dDevice != nullptr;
}

void DxMainWindow::onDetach() {
	this->release();
}

void DxMainWindow::release() {
	SAFE_RELEASE(this->d3dDevice);
	SAFE_RELEASE(this->d3d);
}

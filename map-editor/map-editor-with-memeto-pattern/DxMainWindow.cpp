#include "DxMainWindow.h"

DxMainWindow::DxMainWindow(HINSTANCE hInst) : MainWindow(hInst), d3d(nullptr), d3dDevice(nullptr) {

}

//test
struct TestVertex
{
	float x, y, z;
	DWORD color;
};


INT DxMainWindow::start() {
	if (!this->canShowWindow() || !this->onAttach()) {
		return -1;
	}
	this->showWindow();

	//Test Vertex code - start

	size_t size = sizeof(TestVertex) * 3;
	TestVertex vertexArr[3] =
	{
		{  1.f , -1.f , 0.f , 0xffff0000 },
		{ -1.f , -1.f , 0.f , 0xff00ff00 },
		{  0.f ,  1.f , 0.f , 0xff0000ff },
	};
	LPDIRECT3DVERTEXBUFFER9 vb;

	this->d3dDevice->CreateVertexBuffer(
		size,
		0,
		D3DFVF_XYZ | D3DFVF_DIFFUSE,
		D3DPOOL_MANAGED,
		&vb,
		0
	);

	void* data = nullptr;
	vb->Lock(
		0,
		size,
		&data,
		0
	);
	memcpy(data, vertexArr, size);
	vb->Unlock();
	//Test Vertex code - end 

	while (true) {
		peekingMessage();
		if (needQuit()) {
			break;
		}

		auto dt = Timer::dt();
		// GetAsyncKeyState
		// 1. input manager update
		// 2. input detect update
		// 3. object update
		// 4. render

		this->d3dDevice->Clear(
			0, 0,
			D3DCLEAR_TARGET,
			D3DCOLOR_XRGB(2, 95, 209),
			1.f, // zbuffer
			0.f // 스텐실 버퍼
		); 

		if (SUCCEEDED(this->d3dDevice->BeginScene())) {
			// TODO: render
			//test code - start
			this->d3dDevice->SetStreamSource(0, vb, 0, sizeof(TestVertex));
			this->d3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
			this->d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
			this->d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
			//test code - end

			this->d3dDevice->EndScene();
		}

		if (this->d3dDevice->Present(0, 0, 0, 0) == D3DERR_DEVICELOST) {
			// TODO: restore device
		}

		Timer::tick();
	}

	Timer::release();
	this->onDetach();

	SAFE_RELEASE(vb); // test code - end
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

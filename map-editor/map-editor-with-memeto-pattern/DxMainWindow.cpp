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


	//game object init and lifecycle calling
	Terrain terrain;
	Camera camera;
	GameObjectManager->managing(&terrain);
	GameObjectManager->managing(&camera);

	Context context(this->hMainWnd, this->d3dDevice);


	GameObjectManager->onAttach(&context);
	while (true) {
		peekingMessage();
		if (needQuit()) {
			break;
		}

		// 종료 임시
		if (IS_DOWN(VK_ESCAPE)) {
			::PostMessage(hMainWnd, WM_QUIT, NULL, NULL);
		}

		//TODO: Input Manager, Migrate to DX INPUT

		GameObjectManager->onUpdate();

		// 한글 테스트
		// render scope ===== start
		this->d3dDevice->Clear(
			0, 0,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,// | D3DCLEAR_STENCIL,
			D3DCOLOR_XRGB(2, 95, 209),
			1, // zbuffer
			0 // 스텐실 버퍼 
		); 

		if (SUCCEEDED(this->d3dDevice->BeginScene())) {
			GameObjectManager->onRender();
			this->d3dDevice->EndScene();
		}

		// render scope ===== end

		if (this->d3dDevice->Present(0, 0, 0, 0) == D3DERR_DEVICELOST) {
			// TODO: restore device
		}
		
		Timer->tick();
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
	d3dParams.EnableAutoDepthStencil = true; // 뎁스스텐실 을 사용하겠다
	d3dParams.AutoDepthStencilFormat = D3DFMT_D24S8; //depth = 24bit할당 스텐실 = 8bit 할당

	this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		this->hMainWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dParams,
		&this->d3dDevice
	);


	// TODO: 임시, 렌더 스테이트 부분 멤버 함수로 빼기
	this->d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// TODO: 임시, 라이트 객체로 빼기
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(D3DLIGHT9));

	D3DXVECTOR3 dir = D3DXVECTOR3(0, -1, 1);
	D3DXVec3Normalize(&dir, &dir);

	light.Direction = dir;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	light.Ambient = D3DXCOLOR(1, 1, 1, 1);

	this->d3dDevice->SetLight(0, &light);
	this->d3dDevice->LightEnable(0, true);
	this->d3dDevice->SetRenderState(D3DRS_LIGHTING, true);

	this->d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	this->d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	this->d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	return this->d3dDevice != nullptr;
}

void DxMainWindow::onDetach() {
	GameObjectManager->onDetach();
	singletonRelease();
	this->release();
}

void DxMainWindow::release() {
	SAFE_RELEASE(this->d3dDevice);
	SAFE_RELEASE(this->d3d);
}

void singletonRelease() {
	TimerRelease();
	GameObjectManagerRelease();
}
#include "Terrain.h"

void Terrain::onRender() {
	auto device = this->getContext()->getD3DDevice();
	D3DMATERIAL9 mtrl;
	::ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse = mtrl.Ambient = D3DXCOLOR(1, 1, 1, 1);
	device->SetMaterial(&mtrl);
	device->SetTexture(0, this->texture);

	Mesh::onRender();
}

void Terrain::onUpdate() {
	Mesh::onUpdate();
	auto device = this->getContext()->getD3DDevice();
	device->SetRenderState(D3DRS_FILLMODE, IS_DOWN(VK_SPACE) ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
}

void Terrain::onCreate() {
	Mesh::onCreate();
	auto device = this->getContext()->getD3DDevice();

	D3DXCreateTextureFromFile(
		device,
		_T(".\\..\\..\\terrain-texture.jpg"),
		&this->texture
	);
}

void Terrain::onRelease() {
	Mesh::onRelease();
	SAFE_RELEASE(this->texture);
}



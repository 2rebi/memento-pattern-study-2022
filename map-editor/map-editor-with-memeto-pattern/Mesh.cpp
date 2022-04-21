#include "Mesh.h"


void Mesh::onCreate() {

	// TODO: 임시, 상태 변경 코드로 빼기 
	{
		int width = 300;
		int height = 300;
		double cx = -width / 2.0;
		double cy = height / 2.0;

		
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				this->addVertex(D3DXVECTOR3(cx + x, 0, cy - y));
				this->addNormal(D3DXVECTOR3(0, 1, 0));
				this->addUV(D3DXVECTOR2((double)x / (double)width, (double)y / (double)height));
			}
		}

		int LT = 0;
		int RT = 0;
		int LB = 0;
		int RB = 0;
		for (int x = 0; x < width - 1; x++) {
			for (int y = 0; y < height - 1; y++) {
				LT = y * width + x;
				RT = y * width + x + 1;
				LB = (y + 1) * width + x;
				RB = (y + 1) * width + x + 1;

				this->addIndex(LT, RT, LB);
				this->addIndex(RT, LB, RB);
			}
		}
		
	}

	this->invalidateFVF();

	size_t totalDataSize = this->calcDataSize() * this->vertices.size();
	this->data = new BYTE[totalDataSize];
	::ZeroMemory(this->data, totalDataSize);

	BYTE* cursor = this->data;
	for (int i = 0; i < this->vertices.size(); i++) {
		if (this->fvf & D3DFVF_XYZ) {
			*((D3DXVECTOR3*)cursor) = this->vertices[i];
			cursor += sizeof(D3DXVECTOR3);
		}

		if (this->fvf & D3DFVF_DIFFUSE) {
			*((DWORD*)cursor) = i < colors.size() ? colors[i] : 0xFFFFFFFF;
			cursor += sizeof(DWORD);
		}

		if (this->fvf & D3DFVF_NORMAL) {
			*((D3DXVECTOR3*)cursor) = this->normarls[i];
			cursor += sizeof(D3DXVECTOR3);
		}

		if (this->fvf & D3DFVF_TEX1) {
			*((D3DXVECTOR2*)cursor) = this->arrUV[i];
			cursor += sizeof(D3DXVECTOR2);
		}
	}
}

void Mesh::onUpdate() {
}

void Mesh::onRender() {
	auto device = this->getContext()->getD3DDevice();
	device->SetFVF(this->fvf);
	device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST, 0,
		this->vertices.size(), this->indices.size() / 3,
		(const void*) &indices[0], D3DFMT_INDEX16,
		(const void*) this->data, this->calcDataSize()
	);
}

void Mesh::onRelease() {
	SAFE_DELETE_ARRAY(this->data);
	this->vertices.clear();
	this->indices.clear();
	this->arrUV.clear();
	this->normarls.clear();
	this->colors.clear();
}

const DWORD Mesh::getFVF() const {
	return this->fvf;
}

void Mesh::invalidateFVF() {
	DWORD newFVF = 0;
	if (!this->vertices.empty()) newFVF |= D3DFVF_XYZ;
	if (!this->colors.empty()) newFVF |= D3DFVF_DIFFUSE;
	if (!this->arrUV.empty()) newFVF |= D3DFVF_TEX1;
	if (!this->normarls.empty()) newFVF |= D3DFVF_NORMAL;
	
	this->fvf = newFVF;
}

size_t Mesh::calcDataSize() {
	size_t size = 0;
	if (!this->vertices.empty()) size += sizeof(D3DXVECTOR3);
	if (!this->colors.empty()) size += sizeof(DWORD);
	if (!this->arrUV.empty()) size += sizeof(D3DXVECTOR2);
	if (!this->normarls.empty()) size += sizeof(D3DXVECTOR3);

	return size;
}

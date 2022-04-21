#pragma once

#include <vector>

#include "d3dx9.h"
#include "d3d9.h"
#include "GameObject.h"
#include "util.h"


class Mesh : public GameObject {
public:
	const DWORD getFVF() const;
	void invalidateFVF();

	size_t calcDataSize();

	void onUpdate() override;
	void onRender() override;

protected:
	void onCreate() override;
	void onRelease() override;

	void addVertex(D3DXVECTOR3 vertex) { this->vertices.push_back(vertex);}
	void addNormal(D3DXVECTOR3 normal) { this->normarls.push_back(normal); }
	void addUV(D3DXVECTOR2 uv) { this->arrUV.push_back(uv); }

	void addIndex(WORD i1, WORD i2, WORD i3) {
		this->indices.push_back(i1);
		this->indices.push_back(i2);
		this->indices.push_back(i3);
	}

	
	DWORD fvf;

	// LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	// LPDIRECT3DINDEXBUFFER9 indexBuffer;


	std::vector<D3DXVECTOR3> vertices;
	std::vector<WORD> indices;

	std::vector<D3DXVECTOR2> arrUV;
	std::vector<D3DXVECTOR3> normarls;
	std::vector<DWORD> colors;

	BYTE* data;
};


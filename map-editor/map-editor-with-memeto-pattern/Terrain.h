#pragma once

#include <tchar.h>

#include "Mesh.h"


class Terrain : public Mesh {
public:
	void onRender() override;
	void onUpdate() override;
protected:
	void onCreate() override;
	void onRelease() override;

	LPDIRECT3DTEXTURE9	texture;
};


#pragma once

#include "d3dx9.h"
#include "d3d9.h"

#include "GameObject.h"

class Camera : public GameObject {
	void onUpdate() override;

protected:
	void onCreate() override;

	void updateView();
	void updateProjection();

	const D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0); // fixed

	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookAt;
	D3DXMATRIX view;
	
	FLOAT fov;
	FLOAT aspect;
	FLOAT nearDist;
	FLOAT farDist;
	D3DXMATRIX projection;
	

	// D3DXMATRIX viewProjection;
};


//TODO: 카메라 컨트롤
// 카메라 매니저를 통해
// 1번 카메라, 2번 카메라 가져오는식으로 설계 필요
// 카메라 자체를 인터페이스 추상화 또는 추상 클래스 느낌으로 관리
// 
// 기본 라이프 사이클은 게임 오브젝트를 통해 관리

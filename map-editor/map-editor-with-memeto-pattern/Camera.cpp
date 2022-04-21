#include "Camera.h"

void Camera::onCreate() {

	eye = D3DXVECTOR3(0, 15, 15);
	lookAt = D3DXVECTOR3(0, 0, 0);

	// projection
	fov = D3DXToRadian(89);
	aspect = 1.f;
	nearDist = 0.1f;
	farDist = 1000;

	updateView();
	updateProjection();
}

void Camera::onUpdate() {

}

void Camera::updateView() {
	::D3DXMatrixLookAtLH(
		&this->view,
		&this->eye,
		&this->lookAt,
		&this->up
	);

	this->getContext()->getD3DDevice()->SetTransform(
		D3DTS_VIEW,
		&this->view
	);
}

void Camera::updateProjection() {
	::D3DXMatrixPerspectiveFovLH(
		&this->projection,
		this->fov,
		this->aspect,
		this->nearDist,
		this->farDist
	);

	this->getContext()->getD3DDevice()->SetTransform(
		D3DTS_PROJECTION,
		&this->projection
	);
}
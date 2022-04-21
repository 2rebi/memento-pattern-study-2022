#pragma once

#include <vector>

#include "GameObject.h"
#include "util.h"

class _GameObjectManager : public GameObject {

public:
	static _GameObjectManager* get();
	static void release();

	void managing(GameObject* obj);

	void onAttach(Context* context) override;
	void onDetach() override;

	void onUpdate() override;
	void onRender() override;

private:
	_GameObjectManager() {};
	static _GameObjectManager* instance;

	std::vector<GameObject*> objects;
};

#define GameObjectManager _GameObjectManager::get()
#define GameObjectManagerRelease() _GameObjectManager::release()
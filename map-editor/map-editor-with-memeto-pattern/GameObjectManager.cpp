#include "GameObjectManager.h"

_GameObjectManager* _GameObjectManager::instance = nullptr;

_GameObjectManager* _GameObjectManager::get() {
    if (_GameObjectManager::instance == nullptr) {
        _GameObjectManager::instance = new _GameObjectManager();
    }

    return _GameObjectManager::instance;
}

void _GameObjectManager::release() {
    SAFE_DELETE(_GameObjectManager::instance);
}

void _GameObjectManager::managing(GameObject* obj) {
    this->objects.push_back(obj);
}

void _GameObjectManager::onAttach(Context* context) {
    for (size_t i = 0; i < objects.size(); i++) {
        objects[i]->onAttach(context);
    }
}

void _GameObjectManager::onDetach() {
    for (size_t i = 0; i < objects.size(); i++) {
        objects[i]->onDetach();
    }

    objects.clear();
}


void _GameObjectManager::onUpdate() {
    for (size_t i = 0; i < objects.size(); i++) {
        objects[i]->onUpdate();
    }
}

void _GameObjectManager::onRender() {
    for (size_t i = 0; i < objects.size(); i++) {
        objects[i]->onRender();
    }
}
#include "GameObject.h"

void GameObject::onAttach(Context* context) {
    this->context = context;
    this->onCreate();
}

void GameObject::onDetach() {
    this->onRelease();
    this->context = nullptr;
}

Context* const GameObject::getContext() {
    return this->context;
}

#include "Timer.h"

_Timer* _Timer::instance = nullptr;

_Timer::_Timer() : deltaTime(0), rawDeltaTime(0), prevTime(::GetTickCount64()) { }

_Timer* _Timer::get() {
    if (_Timer::instance == nullptr) {
        _Timer::instance = new _Timer();
    }

    return _Timer::instance;
}

void _Timer::release() {
    SAFE_DELETE(_Timer::instance);
}

void _Timer::tick() {
    ULONGLONG current = ::GetTickCount64();
    this->rawDeltaTime = current - this->prevTime;
    this->deltaTime = this->rawDeltaTime / 1000.0;
    this->prevTime = current;
}

const ULONGLONG _Timer::dt() {
    return this->rawDeltaTime;
}

const double _Timer::normDt() {
    return this->deltaTime;
}

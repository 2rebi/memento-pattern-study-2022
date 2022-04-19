#include "Timer.h"

Timer* Timer::instance = nullptr;

Timer::Timer() : deltaTime(0), rawDeltaTime(0), prevTime(::GetTickCount64()) { }

Timer* Timer::get() {
    if (Timer::instance == nullptr) {
        Timer::instance = new Timer();
    }

    return Timer::instance;
}

void Timer::release() {
    SAFE_DELETE(Timer::instance);
}

void Timer::tick() {
    auto timer = get();
    ULONGLONG current = ::GetTickCount64();
    timer->rawDeltaTime = current - timer->prevTime;
    timer->deltaTime = timer->rawDeltaTime / 1000.0;
    timer->prevTime = current;
}

const ULONGLONG Timer::dt() {
    return get()->rawDeltaTime;
}

const double Timer::normDt() {
    return get()->deltaTime;
}

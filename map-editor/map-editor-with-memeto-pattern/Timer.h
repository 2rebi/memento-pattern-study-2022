#pragma once

#include <Windows.h>
#include "util.h"

class _Timer {
public:
	static _Timer* get();
	static void release();

	void tick();
	const ULONGLONG dt();
	const double normDt();


private:
	_Timer();
	static _Timer* instance;

	double deltaTime;
	ULONGLONG rawDeltaTime;
	ULONGLONG prevTime;
};

#define Timer _Timer::get()
#define TimerRelease() _Timer::release()
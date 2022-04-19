#pragma once

#include <Windows.h>
#include "util.h"

class Timer {
public:
	static Timer* get();
	static void release();

	static void tick();
	static const ULONGLONG dt();
	static const double normDt();

private:
	Timer();
	static Timer* instance;

	double deltaTime;
	ULONGLONG rawDeltaTime;
	ULONGLONG prevTime;
};


#include "timer.h"
#include "raylib.h" // for GetTime()

Timer::Timer(float duration, bool repeat, bool autostart, std::function<void()> func)
    : duration(duration), repeat(repeat), func(func) {
    if (autostart) activate();
}

void Timer::activate() {
    active = true;
    startTime = GetTime();
}

void Timer::deactivate() {
    active = false;
    startTime = 0;
    if (repeat) activate();
}

void Timer::update() {
    if (active && (GetTime() - startTime >= duration)) {
        if (func) func();
        deactivate();
    }
}
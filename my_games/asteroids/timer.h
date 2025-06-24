#pragma once
#include <functional>

struct Timer {
    float duration;
    double startTime = 0;
    bool active = false;
    bool repeat = false;
    std::function<void()> func = nullptr;

    Timer(float duration, bool repeat = false, bool autostart = false, std::function<void()> func = nullptr);

    void activate();
    void deactivate();
    void update();
};
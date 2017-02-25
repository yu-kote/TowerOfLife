#pragma once
#include "cinder/app/AppNative.h"

#define Timer Time::instance()

namespace tol
{
    class Time
    {
    private:
        Time() {}
    public:

        static Time & instance()
        {
            static Time time;
            return time;
        }

        float deltaTime()
        {
            return delta_time;
        }

        void update(const float& elapsed_seconds)
        {
            prev_time = current_time;
            current_time = elapsed_seconds;
            delta_time = current_time - prev_time;
        }

    private:

        float delta_time = 0.0f;
        float prev_time = 0.0f;
        float current_time = 0.0f;

    };
}
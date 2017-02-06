#pragma once
#include "cinder/app/AppNative.h"
#include <iostream>

#define WindowResize tol::Resize::instance()

namespace tol
{
    class Resize
    {
    public:
        static Resize& instance()
        {
            static Resize resize;
            return resize;
        }

        void resize()
        {
            setPerspCameraResize();
            setOrthoCameraResize();
        }

        std::function<void()> setPerspCameraResize = []() {};
        std::function<void()> setOrthoCameraResize = []() {};
    };
}


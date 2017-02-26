#pragma once
#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "../Component.h"

namespace tol
{
    class Color : public Component
    {
    public:

        Color()
        {
            color = ci::ColorA(1.0f, 1.0f, 1.0f);
        }
        Color(ci::ColorA color_)
        {
            color = color_;
        }
        Color(float r, float b, float g)
        {
            color = ci::ColorA(r, g, b);
        }

        void drawBegin()override
        {
            ci::gl::color(color);
        }
        void drawEnd()override
        {

        }

        ci::ColorA getColor() { return color; }
        void setColor(ci::ColorA color_) { color = color_; }
        void setColor(float r, float g, float b, float a = 1.0f) { color = ci::ColorA(r, g, b, a); }

    private:
        ci::ColorA color;

    };

}
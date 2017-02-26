#pragma once

#include "../../../../Utility/Easing/Ease.h"
#include "../../TextureRenderer/TextureRenderer.h"



namespace tol
{
    class FadeIn : public TextureRenderer
    {
    public:

        FadeIn(const ci::ColorA startcolor, const int & fadeframe)
        {
            color->setColor(startcolor);
            fade_frame = fadeframe;
        }

        void setup()override
        {
            alpha = 1;
            Easing.add(alpha, 0, fade_frame, EaseType::CubicIn);
        }

        void update()override
        {
            color->setColor(ci::ColorA(color->getColor().r,
                                       color->getColor().g,
                                       color->getColor().b,
                                       alpha));
        }

        void transLaterDraw()override
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            ci::app::getWindowSize().x,
                                            ci::app::getWindowSize().y));
        }

        bool isFadeEnd()
        {
            return Easing.isEaseEnd(alpha);
        }

    private:
        float alpha;
        int fade_frame;
    };


    class FadeOut : public TextureRenderer
    {
    public:
        FadeOut(const ci::ColorA startcolor, const int & fadeframe)
        {
            color->setColor(startcolor);
            fade_frame = fadeframe;
        }

        void setup()override
        {
            alpha = 0;
            Easing.add(alpha, 1, fade_frame, EaseType::CubicIn);
        }

        void update()override
        {
            color->setColor(ci::ColorA(color->getColor().r,
                                       color->getColor().g,
                                       color->getColor().b,
                                       alpha));
        }

        void laterDraw()override
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            ci::app::getWindowSize().x,
                                            ci::app::getWindowSize().y));
        }

        bool isFadeEnd()
        {
            return Easing.isEaseEnd(alpha);
        }

    private:
        float alpha;
        int fade_frame;
    };
}
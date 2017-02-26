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
            alpha = 1;
            fade_step = 0;
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
        void fadeStart()
        {
            if (fade_step == 0)
            {
                Easing.add(alpha, 0, fade_frame, EaseType::CubicIn);
                fade_step = 1;
            }

        }

        bool isFadeEnd()
        {
            return (fade_step == 1 &&
                    Easing.isEaseEnd(alpha));
        }

    private:
        float alpha;
        int fade_frame;
        int fade_step;
    };


    class FadeOut : public TextureRenderer
    {
    public:
        FadeOut(const ci::ColorA startcolor, const int & fadeframe)
        {
            color->setColor(startcolor);
            fade_frame = fadeframe;
            alpha = 0;
            fade_step = 0;
        }

        void update()override
        {
            color->setColor(ci::ColorA(color->getColor().r,
                                       color->getColor().g,
                                       color->getColor().b,
                                       alpha));
        }

        void transDraw()override
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            ci::app::getWindowSize().x,
                                            ci::app::getWindowSize().y));
        }
        void fadeStart()
        {
            if (fade_step == 0)
            {
                Easing.add(alpha, 1, fade_frame, EaseType::CubicIn);
                fade_step = 1;
            }

        }

        bool isFadeEnd()
        {
            return (fade_step == 1 &&
                    Easing.isEaseEnd(alpha));
        }

    private:
        float alpha;
        int fade_frame;
        int fade_step;
    };
}
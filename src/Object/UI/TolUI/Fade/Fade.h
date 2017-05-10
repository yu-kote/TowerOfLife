#pragma once

#include "../../../../Utility/Easing/Ease.h"
#include "../../TextureRenderer/TextureRenderer.h"

namespace tol
{
    enum FadeState
    {
        STAND_BY,
        EXECUTION,
        END
    };

    class FadeBase : public TextureRenderer
    {
    public:

        FadeBase(const ci::ColorA& startcolor, const int & fadeframe)
        {
            color->setColor(startcolor);
            fade_frame = fadeframe;
            alpha = startcolor.a;
            if (alpha > 0.5f)
                end_alpha = 0;
            if (alpha <= 0.5f)
                end_alpha = 1;
            state = FadeState::STAND_BY;
        }

        void update()override
        {
            color->setColor(ci::ColorA(color->getColor().r,
                                       color->getColor().g,
                                       color->getColor().b,
                                       alpha));
        }

        void fadeStart()
        {
            if (state == FadeState::STAND_BY)
            {
                Easing.add(alpha, end_alpha, fade_frame, EaseType::CubicIn);
                state = FadeState::EXECUTION;
            }
        }

        bool isFadeEnd()
        {
            return (state == FadeState::EXECUTION &&
                    Easing.isEaseEnd(alpha));
        }

    private:
        float alpha;
        float end_alpha;
        int fade_frame;
        FadeState state;
    };

    // フェードインさせるクラス
    class FadeIn : public FadeBase
    {
    public:

        FadeIn(const ci::ColorA& startcolor, const int & fadeframe)
            : FadeBase(startcolor, fadeframe)
        {
        }

        void transLaterDraw()override
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            ci::app::getWindowSize().x,
                                            ci::app::getWindowSize().y));
        }
    };

    // フェードアウトさせるクラス
    class FadeOut : public FadeBase
    {
    public:
        FadeOut(const ci::ColorA& startcolor, const int & fadeframe)
            : FadeBase(startcolor, fadeframe)
        {
        }

        void transDraw()override
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            ci::app::getWindowSize().x,
                                            ci::app::getWindowSize().y));
        }
    };
}
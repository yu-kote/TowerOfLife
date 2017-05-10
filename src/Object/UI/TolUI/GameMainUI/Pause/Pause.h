#pragma once

#include "../../../TextureRenderer/TextureRenderer.h"
#include "../../../Font/FontBase.h"
#include "../../../../../Utility/Easing/Ease.h"


namespace tol
{

    class PauseBackGround : public TextureRenderer
    {
    public:
        PauseBackGround() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:

    };

    class PauseFont : public FontBase
    {
    public:

        PauseFont() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:

    };


    class Pause : public UIBase
    {
    public:
        Pause() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:

        std::shared_ptr<PauseBackGround> background;
        std::shared_ptr<PauseFont> font;


    };
}
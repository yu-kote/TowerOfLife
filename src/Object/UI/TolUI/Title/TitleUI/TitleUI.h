#pragma once
#include "../../../../../Tol/TolGameDataManager.h"

#include "../../../TextureRenderer/TextureRenderer.h"
#include "../../../Font/FontBase.h"

namespace tol
{
    class CoinIcon;

    class TitleScoreFont : public FontBase
    {
    public:
        TitleScoreFont() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:
        ci::Vec3f start_pos;
    };

    class TitleScoreIcon : public TextureRenderer
    {
    public:
        TitleScoreIcon() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:
        std::shared_ptr<TitleScoreFont> scorefont;
    };

    class TitleUI : public UIBase
    {
    public:

        TitleUI() {}

        void setup()override;
        void update()override;
        void transDraw()override;

    private:

        std::shared_ptr<CoinIcon> coin;
        std::shared_ptr<TitleScoreIcon> score;

    };
}
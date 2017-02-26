#pragma once

#include "../../TextureRenderer/TextureRenderer.h"


namespace tol
{

    class ItemRightBar : public TextureRenderer
    {
    public:

        ItemRightBar();

        void setup()override;

        void update();
        void draw()override;

        float bar_angle;

    private:

        float rotate_speed;

    };

    class ItemRightElipse : public TextureRenderer
    {
    public:

        ItemRightElipse();

        void setup()override;

        void draw()override;

    private:

    };

    class GachaItem :public TextureRenderer
    {
    public:
        GachaItem();

        void setup()override;
        void update()override;
        void draw()override;


    private:

        std::vector<std::shared_ptr<ItemRightBar>> bar;
        std::shared_ptr<ItemRightElipse> elipse;

    private:

        void easing();

        int ease_step;
        bool is_easeend;

    };


}

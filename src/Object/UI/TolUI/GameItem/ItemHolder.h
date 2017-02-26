#pragma once
#include "../../TextureRenderer/TextureRenderer.h"
#include "../../Font/FontBase.h"
#include "../../../../Tol/TolGameDataManager.h"
#include "../../../GameObject/Player/Player.h"
#include "../../../GameObject/TolStage/TolBlockHolder.h"
#include "../../../../Utility/Easing/Ease.h"
#include "../../../../Task/SoundManager.h"

namespace tol
{
    class ItemCountFont : public FontBase
    {
    public:
        ItemCountFont();
        ItemCountFont(const int& count);

        void setup()override;
        void draw()override;

        void setCount(const int& count);
    private:
    };
    class ItemIcon0 : public TextureRenderer
    {
    public:

        ItemIcon0();

        void setup()override;
        void update()override;
        void draw()override;

    private:
        std::shared_ptr<ItemCountFont> countfont;
    };
    class ItemIcon1 : public TextureRenderer
    {
    public:

        ItemIcon1();

        void setup()override;
        void update()override;
        void draw()override;

    private:
        std::shared_ptr<ItemCountFont> countfont;
    };

    class ItemIcon2 : public TextureRenderer
    {
    public:

        ItemIcon2();

        void setup()override;
        void update()override;
        void draw()override;


    private:
        std::shared_ptr<ItemCountFont> countfont;
    };


    class ItemHolder : public UIBase
    {
    public:

        ItemHolder();

        void setup()override;
        void update()override;
        void transDraw()override;

    private:

        void useItem();
        void usingItemUpdate();

    private:

        std::shared_ptr<ItemIcon0> item0;
        std::shared_ptr<ItemIcon1> item1;
        std::shared_ptr<ItemIcon2> item2;

        bool is_using_item;

        int item_frame;
        int item_count;


    };
}
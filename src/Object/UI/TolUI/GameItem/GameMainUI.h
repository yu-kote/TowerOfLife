#pragma once
#include "../../TextureRenderer/TextureRenderer.h"
#include "../../Font/FontBase.h"
#include "../../../../Tol/TolGameDataManager.h"
#include "../../../GameObject/Player/Player.h"
#include "../../../GameObject/TolStage/TolBlockHolder.h"
#include "../../../../Utility/Easing/Ease.h"

namespace tol
{
    class ScoreFont : public FontBase
    {
    public:
        ScoreFont();

        void setup()override;
        void update()override;
        void draw()override;

    private:
        ci::Vec3f start_pos;
    };

    class ScoreIcon : public TextureRenderer
    {
    public:
        ScoreIcon() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:
        std::shared_ptr<ScoreFont> scorefont;
    };

    class CoinCountFont : public FontBase
    {
    public:
        CoinCountFont();

        void setup()override;
        void update()override;
        void draw()override;

        void setCount(const int& count);

    private:
    };

    class CoinIcon : public TextureRenderer
    {
    public:
        CoinIcon();

        void setup()override;
        void update()override;
        void draw()override;

        void setCoin(const int& count);

    private:
        std::shared_ptr<CoinCountFont> coinfont;
        int coin_count;
    };

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
        void start(const int& time);

    private:
        std::shared_ptr<ItemCountFont> countfont;
        int end_time;
        bool is_use;
        float alpha;
        ci::Vec3f scale;
        float rect_size;
    };
    class ItemIcon1 : public TextureRenderer
    {
    public:
        ItemIcon1();

        void setup()override;
        void update()override;
        void draw()override;
        void start(const int& time);

    private:
        std::shared_ptr<ItemCountFont> countfont;
        int end_time;
        bool is_use;
        float alpha;
        ci::Vec3f scale;
        float rect_size;
    };

    class ItemIcon2 : public TextureRenderer
    {
    public:
        ItemIcon2();

        void setup()override;
        void update()override;
        void draw()override;
        void start(const int& time);

    private:
        std::shared_ptr<ItemCountFont> countfont;
        int end_time;
        bool is_use;
        float alpha;
        ci::Vec3f scale;
        float rect_size;
    };

    class ItemCrossKey : public TextureRenderer
    {
    public:
        ItemCrossKey();

        void setup()override;
        void update()override;
        void draw()override;

    private:

    };


    class GameMainUI : public UIBase
    {
    public:
        GameMainUI();

        void setup()override;
        void update()override;
        void draw()override;
        void transDraw()override;

        void getCoin();

    private:

        void useItem();
        void usingItemUpdate();

    private:

        std::shared_ptr<ItemIcon0> item0;
        std::shared_ptr<ItemIcon1> item1;
        std::shared_ptr<ItemIcon2> item2;
        std::shared_ptr<ItemCrossKey> cross_key;


        std::shared_ptr<CoinIcon> coin;
        std::shared_ptr<ScoreIcon> score;

        bool is_using_item;

        int item_frame;
        int item_count;


    };
}
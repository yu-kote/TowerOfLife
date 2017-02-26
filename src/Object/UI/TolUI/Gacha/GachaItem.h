#pragma once
#include "../../../../Tol/TolGameDataManager.h"
#include "../../TextureRenderer/TextureRenderer.h"
#include "../../Font/FontBase.h"

namespace tol
{
    class ItemRightBar : public TextureRenderer
    {
    public:
        ItemRightBar();

        void setup()override;
        void update()override;
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

    class DischargeItem : public TextureRenderer
    {
    public:
        DischargeItem(const TolItem& getitem);

        void setup()override;
        void draw()override;

        void start();

    private:
        float alpha;
    };

    class GetItemName : public FontBase
    {
    public:
        GetItemName(const TolItem& getitem);

        void setup()override;
        void draw()override;

    private:
    };

    class GetItemInstruction : public FontBase
    {
    public:
        GetItemInstruction(const TolItem& getitem);

        void setup()override;
        void draw()override;

    private:
    };

    class ItemInstruction : public TextureRenderer
    {
    public:
        ItemInstruction(const TolItem& getitem);

        void setup()override;
        void update()override;
        void draw()override;

        void start();

    private:
        std::shared_ptr<GetItemName> get_item_name;
        std::shared_ptr<GetItemInstruction> get_item_instruction;

        TolItem itemtype;
        bool is_instruction_draw;
        float alpha;
    };

    class GachaItem :public TextureRenderer
    {
    public:
        GachaItem(const TolItem& getitem);

        void setup()override;
        void update()override;
        void draw()override;

        void setItemInstruction(std::shared_ptr<ItemInstruction> item_inst) { item_instruction = item_inst; }

        bool isGachaEnd() { return is_easeend; }
    private:

        std::vector<std::shared_ptr<ItemRightBar>> bar;
        std::shared_ptr<ItemRightElipse> elipse;
        std::shared_ptr<DischargeItem> discharge_item;

        std::shared_ptr<ItemInstruction> item_instruction;


    private:

        void easing();

        int ease_step;
        bool is_easeend;
        TolItem itemtype;

    };


}

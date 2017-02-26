#include "GachaHolder.h"

#include "../../../../Tol/TolGameDataManager.h"
#include "../../../../Utility/Random/Random.h"


void tol::GachaHolder::setup()
{
    RandomInt rand(0, TolItem::ITEM_MAX - 1);

    TolItem getitem = static_cast<TolItem>(rand());
    TolData.itemlist.push_back(getitem);

    item = std::make_shared<tol::GachaItem>(tol::GachaItem(getitem));
    item_instruction = std::make_shared<tol::ItemInstruction>(tol::ItemInstruction(getitem));

    item->setItemInstruction(
        std::static_pointer_cast<tol::ItemInstruction>(item_instruction));

    item->setup();
    item_instruction->setup();

    is_gacha_end = false;
}

void tol::GachaHolder::update()
{
    if (!fadein->isFadeEnd())return;
    item->update();
    item_instruction->update();

    if (item->isGachaEnd())
    {
        if (env.isPadPush(env.BUTTON_4))
        {
            is_gacha_end = true;
        }
    }
}

void tol::GachaHolder::transDraw()
{
    if (!fadein->isFadeEnd())return;
    item->drawReflect();
    item_instruction->drawReflect();
}

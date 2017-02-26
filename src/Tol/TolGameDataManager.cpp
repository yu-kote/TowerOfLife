#include "TolGameDataManager.h"

void tol::TolGameDataManager::setup()
{
#if 1
    itemlist.push_back(TolItem::SCROLL_STOP);
    itemlist.push_back(TolItem::SCROLL_STOP);
    itemlist.push_back(TolItem::SCROLL_STOP);
    itemlist.push_back(TolItem::GIMMICK_STOP);
    itemlist.push_back(TolItem::GIMMICK_STOP);
    itemlist.push_back(TolItem::GIMMICK_STOP);
    itemlist.push_back(TolItem::TWO_STEP_JUMP);
    itemlist.push_back(TolItem::TWO_STEP_JUMP);
    itemlist.push_back(TolItem::TWO_STEP_JUMP);
#endif
}

bool tol::TolGameDataManager::hasItem(const TolItem & item)
{
    for (auto& it : itemlist)
    {
        if (it == item)
            return true;
    }
    return false;
}

void tol::TolGameDataManager::useItem(const TolItem & item)
{
    for (auto it = itemlist.begin(); it != itemlist.end();)
    {
        if ((*it) == item)
        {
            it = itemlist.erase(it);
            return;
        }
        it++;
    }
}

int tol::TolGameDataManager::itemCountCheck(const TolItem & item)
{
    int count = 0;
    for (auto& it : itemlist)
    {
        if (it == item)
            count++;
    }
    return count;
}

std::string tol::TolGameDataManager::getItemName(const TolItem& item)
{
    switch (item)
    {
    case TolItem::SCROLL_STOP:
        return u8"スクロールストッパー";
    case TolItem::GIMMICK_STOP:
        return u8"ギミックストッパー";
    case TolItem::TWO_STEP_JUMP:
        return u8"ダブルジャンパー";
    }
}

std::string tol::TolGameDataManager::getItemInstruction(const TolItem & item)
{
    switch (item)
    {
    case TolItem::SCROLL_STOP:
        return u8"使用すると、一時的に自動スクロールを\n　　　止めることができます。";
    case TolItem::GIMMICK_STOP:
        return u8"使用すると、一時的にブロックの動きを\n　　　止めることができます。";
    case TolItem::TWO_STEP_JUMP:
        return u8"使用すると、一時的に二段ジャンプできるようになります。";
    }
}

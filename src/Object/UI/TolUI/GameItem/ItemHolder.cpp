#include "ItemHolder.h"
#include "../../../../Utility/Easing/Ease.h"
#include "../../../../Utility/Input/InputEvent.h"

using namespace ci;
using namespace ci::app;


////////////////////////////////////////////////////////////////////////////////////////////
// アイテムの数
////////////////////////////////////////////////////////////////////////////////////////////
tol::ItemCountFont::ItemCountFont()
{
}

tol::ItemCountFont::ItemCountFont(const int & count)
{
    drawstring = std::to_string(count);
}

void tol::ItemCountFont::setup()
{
    transform.position = Vec3f(50, 40, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 30);
    color->setColor(ColorA::black());
}

void tol::ItemCountFont::draw()
{
    drawFont();
}

void tol::ItemCountFont::setCount(const int & count)
{
    drawstring = std::to_string(count);
}
////////////////////////////////////////////////////////////////////////////////////////////
// アイテムのアイコン
////////////////////////////////////////////////////////////////////////////////////////////
tol::ItemIcon0::ItemIcon0()
    : TextureRenderer("Item0")
{
}

void tol::ItemIcon0::setup()
{
    transform.position.x = 0;
    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();
}

void tol::ItemIcon0::update()
{
    countfont->setCount(TolData.itemCountCheck(TolItem::SCROLL_STOP));
}

void tol::ItemIcon0::draw()
{
    drawRect(Vec2f(70, 70));
    countfont->drawReflect();
}

tol::ItemIcon1::ItemIcon1()
    : TextureRenderer("Item1")
{
}

void tol::ItemIcon1::setup()
{
    transform.position.x = 100;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();
}

void tol::ItemIcon1::update()
{
    countfont->setCount(TolData.itemCountCheck(TolItem::GIMMICK_STOP));
}

void tol::ItemIcon1::draw()
{
    drawRect(Vec2f(70, 70));
    countfont->drawReflect();
}

tol::ItemIcon2::ItemIcon2()
    : TextureRenderer("Item2")
{
}

void tol::ItemIcon2::setup()
{
    transform.position.x = 200;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();
}

void tol::ItemIcon2::update()
{
    countfont->setCount(TolData.itemCountCheck(TolItem::TWO_STEP_JUMP));
}

void tol::ItemIcon2::draw()
{
    drawRect(Vec2f(70, 70));
    countfont->drawReflect();
}


////////////////////////////////////////////////////////////////////////////////////////////
// まとめ
////////////////////////////////////////////////////////////////////////////////////////////

tol::ItemHolder::ItemHolder()
{
}

void tol::ItemHolder::setup()
{
    is_using_item = false;
    item_frame = 600;
    item_count = 0;

    item0 = std::make_shared<ItemIcon0>();
    item1 = std::make_shared<ItemIcon1>();
    item2 = std::make_shared<ItemIcon2>();

    item0->setup();
    item1->setup();
    item2->setup();
    TolData.using_item = TolItem::ITEM_MAX;
}

void tol::ItemHolder::update()
{
    useItem();
    usingItemUpdate();

    item0->update();
    item1->update();
    item2->update();
}

void tol::ItemHolder::transDraw()
{
    item0->drawReflect();
    item1->drawReflect();
    item2->drawReflect();
}

void tol::ItemHolder::useItem()
{
    if (is_using_item)return;
    if (env.getPadAxis(env.CROSS_HORIZONTAL) <= -1)
    {
        if (!TolData.hasItem(TolItem::SCROLL_STOP))return;
        TolData.using_item = TolItem::SCROLL_STOP;
        TolData.useItem(TolItem::SCROLL_STOP);
        is_using_item = true;
    }
    if (env.getPadAxis(env.CROSS_VERTICAL) <= -1)
    {
        if (!TolData.hasItem(TolItem::GIMMICK_STOP))return;
        TolData.using_item = TolItem::GIMMICK_STOP;
        TolData.useItem(TolItem::GIMMICK_STOP);
        is_using_item = true;
    }
    if (env.getPadAxis(env.CROSS_HORIZONTAL) >= 1)
    {
        if (!TolData.hasItem(TolItem::TWO_STEP_JUMP))return;
        TolData.using_item = TolItem::TWO_STEP_JUMP;
        TolData.useItem(TolItem::TWO_STEP_JUMP);
        is_using_item = true;
    }
}

void tol::ItemHolder::usingItemUpdate()
{
    if (TolData.using_item == TolItem::ITEM_MAX)return;
    item_count++;
    if (item_count > item_frame)
    {
        item_count = 0;
        is_using_item = false;
        TolData.using_item = TolItem::ITEM_MAX;
    }
}
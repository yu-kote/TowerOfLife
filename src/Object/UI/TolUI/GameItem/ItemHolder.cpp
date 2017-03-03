#include "ItemHolder.h"
#include "../../../../Utility/Easing/Ease.h"
#include "../../../../Utility/Input/InputEvent.h"

using namespace ci;
using namespace ci::app;

////////////////////////////////////////////////////////////////////////////////////////////
// スコア
////////////////////////////////////////////////////////////////////////////////////////////

tol::ScoreFont::ScoreFont()
{
}

void tol::ScoreFont::setup()
{
    transform.position = Vec3f(1100, 0, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 60);
    color->setColor(ColorA::black());
}

void tol::ScoreFont::update()
{
    drawstring = std::to_string(TolData.calcScore());
}

void tol::ScoreFont::draw()
{
    drawFont();
}


////////////////////////////////////////////////////////////////////////////////////////////
// コインの枚数
////////////////////////////////////////////////////////////////////////////////////////////

tol::CoinCountFont::CoinCountFont()
{
}

void tol::CoinCountFont::setup()
{
    transform.position = Vec3f(50, 40, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 30);
    color->setColor(ColorA::black());
}

void tol::CoinCountFont::update()
{

}

void tol::CoinCountFont::draw()
{
    drawFont();
}

void tol::CoinCountFont::setCount(const int & count)
{
    drawstring = std::to_string(count);
}

////////////////////////////////////////////////////////////////////////////////////////////
// コインアイコン
////////////////////////////////////////////////////////////////////////////////////////////

tol::CoinIcon::CoinIcon()
    :TextureRenderer("GachaRightElipse")
{
}

void tol::CoinIcon::setup()
{
    transform.position.x = 900;
    coinfont = std::make_shared<CoinCountFont>();
    coinfont->setup();
}

void tol::CoinIcon::update()
{
    coinfont->setCount(coin_count);
    coinfont->update();
}

void tol::CoinIcon::draw()
{
    drawRect(Vec2f(50, 70));
    coinfont->drawReflect();
}

void tol::CoinIcon::setCoin(const int & count)
{
    coin_count = count;
}

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
    scale = transform.scale;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();

    end_time = 0;
    is_use = false;
    alpha = 1;
}

void tol::ItemIcon0::update()
{
    countfont->setCount(TolData.itemCountCheck(TolItem::SCROLL_STOP));

    color->setColor(1, 1, 1, alpha);

    if (is_use)
    {
        end_time--;
        if (end_time < 180)
        {
            alpha = sin(end_time * 0.1f);
        }
        if (end_time < 0.0f)
        {
            is_use = false;
            alpha = 1;
            Easing.add(transform.scale, scale, 60, EaseType::CubicOut);
        }
    }
}

void tol::ItemIcon0::draw()
{
    drawRect(Vec2f(70, 70));
    countfont->drawReflect();
}

void tol::ItemIcon0::start(const int & time)
{
    is_use = true;
    end_time = time;
    Easing.add(transform.scale, transform.scale * 1.3f, 60, EaseType::CubicOut);
}

tol::ItemIcon1::ItemIcon1()
    : TextureRenderer("Item1")
{
}

void tol::ItemIcon1::setup()
{
    transform.position.x = 100;
    scale = transform.scale;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();

    end_time = 0;
    is_use = false;
    alpha = 1;
}

void tol::ItemIcon1::update()
{
    countfont->setCount(TolData.itemCountCheck(TolItem::GIMMICK_STOP));

    color->setColor(1, 1, 1, alpha);

    if (is_use)
    {
        end_time--;
        if (end_time < 180)
        {
            alpha = sin(end_time);
        }
        if (end_time < 0.0f)
        {
            is_use = false;
            alpha = 1;
            Easing.add(transform.scale, scale, 60, EaseType::CubicOut);
        }
    }
}

void tol::ItemIcon1::draw()
{
    drawRect(Vec2f(70, 70));
    countfont->drawReflect();
}

void tol::ItemIcon1::start(const int & time)
{
    is_use = true;
    end_time = time;
    Easing.add(transform.scale, transform.scale * 1.3f, 60, EaseType::CubicOut);
}

tol::ItemIcon2::ItemIcon2()
    : TextureRenderer("Item2")
{
}

void tol::ItemIcon2::setup()
{
    transform.position.x = 200;
    scale = transform.scale;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();

    end_time = 0;
    is_use = false;
    alpha = 1;
}

void tol::ItemIcon2::update()
{
    countfont->setCount(TolData.itemCountCheck(TolItem::TWO_STEP_JUMP));

    color->setColor(1, 1, 1, alpha);

    if (is_use)
    {
        end_time--;
        if (end_time < 180)
        {
            alpha = sin(end_time);
        }
        if (end_time < 0.0f)
        {
            is_use = false;
            alpha = 1;
            Easing.add(transform.scale, scale, 60, EaseType::CubicOut);
        }
    }
}

void tol::ItemIcon2::draw()
{
    drawRect(Vec2f(70, 70));
    countfont->drawReflect();
}

void tol::ItemIcon2::start(const int & time)
{
    is_use = true;
    end_time = time;
    Easing.add(transform.scale, transform.scale * 1.3f, 60, EaseType::CubicOut);
}

////////////////////////////////////////////////////////////////////////////////////////////
// まとめ
////////////////////////////////////////////////////////////////////////////////////////////

tol::GameMainUI::GameMainUI()
{
}

void tol::GameMainUI::setup()
{
    transform.position = Vec3f(100, 50, 0);

    is_using_item = false;
    item_frame = 600;
    item_count = 0;

    item0 = std::make_shared<ItemIcon0>();
    item1 = std::make_shared<ItemIcon1>();
    item2 = std::make_shared<ItemIcon2>();
    coin = std::make_shared<CoinIcon>();
    score = std::make_shared<ScoreFont>();

    item0->setup();
    item1->setup();
    item2->setup();
    coin->setup();
    score->setup();
    TolData.using_item = TolItem::ITEM_MAX;
}

void tol::GameMainUI::update()
{
    useItem();
    usingItemUpdate();

    item0->update();
    item1->update();
    item2->update();
    coin->update();
    score->update();
    coin->setCoin(TolData.temp_coin);
}

void tol::GameMainUI::transDraw()
{
    item0->drawReflect();
    item1->drawReflect();
    item2->drawReflect();
    coin->drawReflect();
    score->drawReflect();
}

void tol::GameMainUI::useItem()
{
    if (is_using_item)return;
    if (env.getPadAxis(env.CROSS_HORIZONTAL) <= -1)
    {
        if (!TolData.hasItem(TolItem::SCROLL_STOP))return;
        TolData.using_item = TolItem::SCROLL_STOP;
        TolData.useItem(TolItem::SCROLL_STOP);
        is_using_item = true;
        item0->start(item_frame);
    }
    if (env.getPadAxis(env.CROSS_VERTICAL) <= -1)
    {
        if (!TolData.hasItem(TolItem::GIMMICK_STOP))return;
        TolData.using_item = TolItem::GIMMICK_STOP;
        TolData.useItem(TolItem::GIMMICK_STOP);
        is_using_item = true;
        item1->start(item_frame);
    }
    if (env.getPadAxis(env.CROSS_HORIZONTAL) >= 1)
    {
        if (!TolData.hasItem(TolItem::TWO_STEP_JUMP))return;
        TolData.using_item = TolItem::TWO_STEP_JUMP;
        TolData.useItem(TolItem::TWO_STEP_JUMP);
        is_using_item = true;
        item2->start(item_frame);
    }
}

void tol::GameMainUI::usingItemUpdate()
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


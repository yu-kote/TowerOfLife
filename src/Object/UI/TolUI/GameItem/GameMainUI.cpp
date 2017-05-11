#include "GameMainUI.h"
#include "../../../../Utility/Easing/Ease.h"
#include "../../../../Utility/Input/InputEvent.h"

#include "../../../../Task/SoundManager.h"

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
    start_pos = Vec3f(290, 00, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 60);
    color->setColor(ColorA::white());
}

void tol::ScoreFont::update()
{
    drawstring = std::to_string(TolData.calcScore());

    if (drawstring.size() > 4)
        transform.scale.x = 0.7f;

    auto offset_pos = Vec3f(drawstring.size() * (font.getSize() - 10) * transform.scale.x, 0, 0);
    transform.position = start_pos - offset_pos;
}

void tol::ScoreFont::draw()
{
    drawFont();
}

////////////////////////////////////////////////////////////////////////////////////////////
// スコア表示
////////////////////////////////////////////////////////////////////////////////////////////

void tol::ScoreIcon::setup()
{
    transform.position = Vec3f(1000, 20, 0);
    color->setColor(ColorA(0, 0, 0, 0.5f));

    scorefont = std::make_shared<ScoreFont>();
    scorefont->setup();
}

void tol::ScoreIcon::update()
{
    scorefont->update();
}

void tol::ScoreIcon::draw()
{
    drawRect(Vec2f(300, 50));
    scorefont->drawReflect();
}

////////////////////////////////////////////////////////////////////////////////////////////
// コインの枚数
////////////////////////////////////////////////////////////////////////////////////////////

tol::CoinCountFont::CoinCountFont()
{
}

void tol::CoinCountFont::setup()
{
    transform.position = Vec3f(50, 20, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 60);
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
    drawstring = u8"×" + std::to_string(count);
}

////////////////////////////////////////////////////////////////////////////////////////////
// コインアイコン
////////////////////////////////////////////////////////////////////////////////////////////

tol::CoinIcon::CoinIcon()
    :TextureRenderer("Coin")
{
}

void tol::CoinIcon::setup()
{
    transform.position.x = 700;
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
    transform.position = Vec3f(-20, 110, 0);
    scale = transform.scale;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();

    end_time = 0;
    is_use = false;
    alpha = 1;
    rect_size = 70;
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

void tol::ItemIcon0::draw()
{
    gl::translate(Vec3f(-rect_size / 2, -rect_size / 2, 0));
    drawRect(Vec2f(rect_size, rect_size));
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
    transform.position = Vec3f(95, 10, 0);
    scale = transform.scale;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();

    end_time = 0;
    is_use = false;
    alpha = 1;
    rect_size = 70;
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
    gl::translate(Vec3f(-rect_size / 2, -rect_size / 2, 0));
    drawRect(Vec2f(rect_size, rect_size));
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
    transform.position = Vec3f(205, 110, 0);
    scale = transform.scale;

    countfont = std::make_shared<ItemCountFont>();
    countfont->setup();

    end_time = 0;
    is_use = false;
    alpha = 1;
    rect_size = 70;
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
    gl::translate(Vec3f(-rect_size / 2, -rect_size / 2, 0));
    drawRect(Vec2f(rect_size, rect_size));
    countfont->drawReflect();
}

void tol::ItemIcon2::start(const int & time)
{
    is_use = true;
    end_time = time;
    Easing.add(transform.scale, transform.scale * 1.3f, 60, EaseType::CubicOut);
}

tol::ItemCrossKey::ItemCrossKey()
    : TextureRenderer("CrossKey")
{
}

void tol::ItemCrossKey::setup()
{
    transform.position = Vec3f(40, 60, 0);
    transform.scale = Vec3f(1.5f, 1.5f, 1.5f);
}

void tol::ItemCrossKey::update()
{
}

void tol::ItemCrossKey::draw()
{
    drawRect(Vec2f(70, 70));
}

////////////////////////////////////////////////////////////////////////////////////////////
// まとめ
////////////////////////////////////////////////////////////////////////////////////////////

tol::GameMainUI::GameMainUI()
{
}

void tol::GameMainUI::setup()
{
    transform.position = Vec3f(100, 60, 0);

    is_using_item = false;
    item_frame = 60 * 20;
    item_count = 0;

    item0 = std::make_shared<ItemIcon0>();
    item1 = std::make_shared<ItemIcon1>();
    item2 = std::make_shared<ItemIcon2>();
    coin = std::make_shared<CoinIcon>();
    score = std::make_shared<ScoreIcon>();
    cross_key = std::make_shared<ItemCrossKey>();

    item0->setup();
    item1->setup();
    item2->setup();
    coin->setup();
    score->setup();
    cross_key->setup();

    TolData.using_item = TolItem::ITEM_MAX;
    update();
}

void tol::GameMainUI::update()
{
    coin->setCoin(TolData.temp_coin);

    useItem();
    usingItemUpdate();

    item0->update();
    item1->update();
    item2->update();
    coin->update();
    score->update();
    cross_key->update();
}

void tol::GameMainUI::draw()
{
}

void tol::GameMainUI::transDraw()
{
    item0->drawReflect();
    item1->drawReflect();
    item2->drawReflect();
    coin->drawReflect();
    score->drawReflect();
    cross_key->drawReflect();
}

void tol::GameMainUI::useItem()
{
    if (is_using_item)
        return;

    if (env.getPadAxis(env.CROSS_HORIZONTAL) <= -1)
    {
        if (!TolData.hasItem(TolItem::SCROLL_STOP))
            return;
        TolData.using_item = TolItem::SCROLL_STOP;
        TolData.useItem(TolItem::SCROLL_STOP);
        is_using_item = true;
        item0->start(item_frame);

        SoundGet.find("UseItem")->start();
    }
    if (env.getPadAxis(env.CROSS_VERTICAL) <= -1)
    {
        if (!TolData.hasItem(TolItem::GIMMICK_STOP))
            return;
        TolData.using_item = TolItem::GIMMICK_STOP;
        TolData.useItem(TolItem::GIMMICK_STOP);
        is_using_item = true;
        item1->start(item_frame);

        SoundGet.find("UseItem")->start();
    }
    if (env.getPadAxis(env.CROSS_HORIZONTAL) >= 1)
    {
        if (!TolData.hasItem(TolItem::TWO_STEP_JUMP))
            return;
        TolData.using_item = TolItem::TWO_STEP_JUMP;
        TolData.useItem(TolItem::TWO_STEP_JUMP);
        is_using_item = true;
        item2->start(item_frame);

        SoundGet.find("UseItem")->start();
    }
}

void tol::GameMainUI::usingItemUpdate()
{
    if (TolData.using_item == TolItem::ITEM_MAX)
        return;
    item_count++;
    if (item_count > item_frame)
    {
        item_count = 0;
        is_using_item = false;
        TolData.using_item = TolItem::ITEM_MAX;
    }
}


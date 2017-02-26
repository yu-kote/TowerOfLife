#include "GachaItem.h"
#include "../../../../Utility/Random/Random.h"
#include "../../../../Utility/Interface/Interface.h"
#include "../../../../Task/SoundManager.h"


using namespace ci;
using namespace ci::app;

////////////////////////////////////////////////////////////////////////////////////////////
// 後光
////////////////////////////////////////////////////////////////////////////////////////////
tol::ItemRightBar::ItemRightBar()
    : TextureRenderer("GachaRightBar")
{

}

void tol::ItemRightBar::setup()
{
    // 長さをランダムに
    RandomFloat rand(getWindowSize().y / 2, getWindowSize().y);
    transform.scale.y = rand();

    // 太さをランダムに
    rand.setRange(15.0f, 50.0f);
    transform.scale.x = rand();

    // バーの中心位置を xを中心に yを一番下にする
    transform.position = Vec3f(-transform.scale.x / 2,
                               -transform.scale.y,
                               0);

    // 回転速度をランダムに
    rand.setRange(0.01f, 1.0f);
    rotate_speed = rand();


    bar_angle = 0;


    for (int i = 0; i < 1024; i++)
        update();
}

void tol::ItemRightBar::update()
{
    bar_angle += rotate_speed;
}

void tol::ItemRightBar::draw()
{
    drawRect();
}

////////////////////////////////////////////////////////////////////////////////////////////
// 後光の円
////////////////////////////////////////////////////////////////////////////////////////////
tol::ItemRightElipse::ItemRightElipse()
    : TextureRenderer("GachaRightElipse")
{
}

void tol::ItemRightElipse::setup()
{
    transform.scale = Vec3f(100.0f, 100.0f, 0);
    transform.position = -transform.scale / 2;
}

void tol::ItemRightElipse::draw()
{
    drawRect();
}


////////////////////////////////////////////////////////////////////////////////////////////
// アイテムの画像
////////////////////////////////////////////////////////////////////////////////////////////
tol::DischargeItem::DischargeItem(const TolItem& getitem) :
    TextureRenderer("Item" + std::to_string(static_cast<int>(getitem)))
{
}

void tol::DischargeItem::setup()
{
    transform.scale = Vec3f(100.0f, 100.0f, 0);
    transform.position = -transform.scale / 2;
    alpha = 0;
}

void tol::DischargeItem::draw()
{
    color->setColor(1, 1, 1, alpha);
    drawRect();
}

void tol::DischargeItem::start()
{
    Easing.add(alpha, 1, 60, EaseType::CubicIn);
}


////////////////////////////////////////////////////////////////////////////////////////////
// アイテムの獲得文
////////////////////////////////////////////////////////////////////////////////////////////
tol::GetItemName::GetItemName(const TolItem & getitem)
{
    drawstring = u8"『" + TolData.getItemName(getitem) + u8"』獲得！";
}

void tol::GetItemName::setup()
{
    transform.position = Vec3f(500, 50, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 60);
    color->setColor(ColorA::black());
}

void tol::GetItemName::draw()
{
    drawFontCenter();
}

////////////////////////////////////////////////////////////////////////////////////////////
// アイテムの説明文
////////////////////////////////////////////////////////////////////////////////////////////
tol::GetItemInstruction::GetItemInstruction(const TolItem & getitem)
{
    drawstring = TolData.getItemInstruction(getitem);
}

void tol::GetItemInstruction::setup()
{
    transform.position = Vec3f(500, 150, 0);
    setFontFromAsset("Font/HuiFont29.ttf", 30);
    color->setColor(ColorA::black());
}

void tol::GetItemInstruction::draw()
{
    drawFontCenter();
}


////////////////////////////////////////////////////////////////////////////////////////////
// 説明文まとめたやつ
////////////////////////////////////////////////////////////////////////////////////////////
tol::ItemInstruction::ItemInstruction(const TolItem& getitem)
{
    itemtype = getitem;
}

void tol::ItemInstruction::setup()
{
    transform.position =
        Vec3f((float)getWindowCenter().x,
        (float)getWindowCenter().y - 80,
              0);

    // アイテムの獲得文初期化
    get_item_name = std::make_shared<tol::GetItemName>(GetItemName(itemtype));
    get_item_name->setup();

    // 説明文の初期化
    get_item_instruction = std::make_shared<tol::GetItemInstruction>(GetItemInstruction(itemtype));
    get_item_instruction->setup();

    is_instruction_draw = false;
    alpha = 0;
    color->setColor(1.0f, 1.0f, 1.0f, alpha);
    get_item_name->color->setColor(0, 0, 0, alpha);
    get_item_instruction->color->setColor(0, 0, 0, alpha);
}

void tol::ItemInstruction::update()
{
    color->setColor(1.0f, 1.0f, 1.0f, alpha - 0.2f);
    get_item_name->color->setColor(0, 0, 0, alpha);
    get_item_instruction->color->setColor(0, 0, 0, alpha);

    get_item_name->update();
    get_item_instruction->update();
}

void tol::ItemInstruction::draw()
{
    Vec2f scale = Vec2f(1000, 250);
    Vec2f pos = Vec2f(-scale.x / 2, -scale.y);

    gl::translate(pos);

    drawRect(scale);

    get_item_name->drawReflectTransform();

    get_item_instruction->drawReflectTransform();
}

void tol::ItemInstruction::start()
{
    if (is_instruction_draw)return;
    is_instruction_draw = true;
    Easing.add(alpha, 1, 60, EaseType::QuartIn);
}


////////////////////////////////////////////////////////////////////////////////////////////
// まとめるやつ
////////////////////////////////////////////////////////////////////////////////////////////
tol::GachaItem::GachaItem(const TolItem& getitem)
{
    itemtype = getitem;
}

void tol::GachaItem::setup()
{
    transform.scale = Vec3f(0.5f, 0.5f, 1);
    transform.position = Vec3f((float)getWindowCenter().x, -500, 0);

    // バーの初期化
    for (int i = 0; i < 10; i++)
    {
        bar.push_back(std::make_shared<tol::ItemRightBar>());
    }

    for (int i = 0; i < bar.size(); i++)
        bar[i]->setup();

    // アイテムの後ろの光の初期化
    elipse = std::make_shared<tol::ItemRightElipse>();
    elipse->setup();

    // アイテムの画像の初期化
    discharge_item = std::make_shared<tol::DischargeItem>(tol::DischargeItem(itemtype));
    discharge_item->setup();

    // イージングの初期化
    is_easeend = false;
    ease_step = 0;
}

void tol::GachaItem::update()
{
    easing();
    for (int i = 0; i < bar.size(); i++)
        bar[i]->update();

    elipse->update();
    discharge_item->update();
}

void tol::GachaItem::draw()
{
    for (int i = 0; i < bar.size(); i++)
    {
        gl::pushMatrices();

        gl::rotate(Vec3f(0, 0, bar[i]->bar_angle));
        bar[i]->drawReflect();

        gl::popMatrices();
    }

    elipse->drawReflect();
    discharge_item->drawReflect();
}

void tol::GachaItem::easing()
{
    if (is_easeend)return;

    if (ease_step == 0 &&
        Easing.isEaseEnd(transform.position.y))
    {
        int frame = 180;
        Easing.add(transform.position.y, (float)getWindowCenter().y, frame, EaseType::QuartOut);
        Easing.add(transform.scale.x, transform.scale.x * 4, frame, EaseType::QuadOut);
        Easing.add(transform.scale.y, transform.scale.y * 4, frame, EaseType::QuadOut);
        ease_step = 1;
        SoundGet.find("FallItem")->start();
    }

    if (ease_step == 1 &&
        Easing.isEaseEnd(transform.position.y))
    {
        Easing.wait(transform.scale.x, 10);
        Easing.wait(transform.scale.y, 10);
        Easing.add(transform.scale.x, transform.scale.x * 2, 60, EaseType::QuadIn);
        Easing.add(transform.scale.y, transform.scale.y * 2, 60, EaseType::QuadIn);
        ease_step = 2;
        SoundGet.find("GetItem")->start();
        discharge_item->start();
    }

    if (env.isPadPush(env.BUTTON_4) &&
        ease_step == 2 &&
        Easing.isEaseEnd(transform.scale.y))
    {
        is_easeend = true;
        item_instruction->start();
        Easing.wait(transform.position.y, 60);
        Easing.add(transform.position.y, transform.position.y + 150, 60, EaseType::QuartOut);
        SoundGet.find("ScaleItem")->start();
    }
}

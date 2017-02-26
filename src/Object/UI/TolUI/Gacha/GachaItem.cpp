#include "GachaItem.h"
#include "../../../../Utility/Random/Random.h"

using namespace ci;
using namespace ci::app;

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
    rand.setRange(25.0f, 50.0f);
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
    drawRect();
}

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

tol::GachaItem::GachaItem()
{
}

void tol::GachaItem::setup()
{
    transform.scale = Vec3f(0.5f, 0.5f, 1);
    transform.position = Vec3f((float)getWindowCenter().x, -500, 0);

    for (int i = 0; i < 20; i++)
    {
        bar.push_back(std::make_shared<tol::ItemRightBar>());
    }

    for (int i = 0; i < bar.size(); i++)
        bar[i]->setup();

    elipse = std::make_shared<tol::ItemRightElipse>();
    elipse->setup();

    is_easeend = false;
    ease_step = 0;

}

void tol::GachaItem::update()
{
    easing();
    for (int i = 0; i < bar.size(); i++)
        bar[i]->update();

    elipse->update();
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
    }

    if (ease_step == 1 &&
        Easing.isEaseEnd(transform.position.y))
    {
        Easing.wait(transform.scale.x, 10);
        Easing.wait(transform.scale.y, 10);
        Easing.add(transform.scale.x, transform.scale.x * 2, 60, EaseType::QuadIn);
        Easing.add(transform.scale.y, transform.scale.y * 2, 60, EaseType::QuadIn);
        ease_step = 2;
    }

    if (ease_step == 2 &&
        Easing.isEaseEnd(transform.scale.y))
    {
        is_easeend = true;
    }

}


#include "Pause.h"

using namespace ci;
using namespace ci::app;

////////////////////////////////////////////////////////////////////////////////////////////
// �w�i
////////////////////////////////////////////////////////////////////////////////////////////

void tol::PauseBackGround::setup()
{
    color->setColor(0, 0, 0, 0.6f);
}

void tol::PauseBackGround::update()
{
}

void tol::PauseBackGround::draw()
{
    ci::gl::drawSolidRect(ci::Rectf(0,
                                    0,
                                    ci::app::getWindowSize().x,
                                    ci::app::getWindowSize().y));
}


////////////////////////////////////////////////////////////////////////////////////////////
// �|�[�Y�̕���
////////////////////////////////////////////////////////////////////////////////////////////

void tol::PauseFont::setup()
{
    drawstring = u8"�ꎞ��~";
    setFontFromAsset("Font/HuiFont29.ttf", 100);
    transform.position = Vec3f(getWindowCenter().x,
                               getWindowCenter().y - font.getSize() / 2,
                               0);
}

void tol::PauseFont::update()
{
}

void tol::PauseFont::draw()
{
    drawFontCenter();
}

////////////////////////////////////////////////////////////////////////////////////////////
// �\��
////////////////////////////////////////////////////////////////////////////////////////////

void tol::Pause::setup()
{
    background = std::make_shared<PauseBackGround>();
    font = std::make_shared<PauseFont>();

    background->setup();
    font->setup();

    // �ŏ��͒�~�����Ȃ����߃A�N�e�B�u��؂�
    setDrawActive(false);
}

void tol::Pause::update()
{
    background->update();
    font->update();
}

void tol::Pause::draw()
{
    background->drawReflect();
    font->drawReflect();
}

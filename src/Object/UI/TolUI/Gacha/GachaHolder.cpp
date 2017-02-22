#include "GachaHolder.h"

void tol::GachaHolder::setup()
{
    gachabutton = std::make_shared<tol::GachaButton>();

    gachabutton->setup();
}

void tol::GachaHolder::update()
{
    gachabutton->update();
}

void tol::GachaHolder::draw()
{
    gachabutton->drawReflect();
}

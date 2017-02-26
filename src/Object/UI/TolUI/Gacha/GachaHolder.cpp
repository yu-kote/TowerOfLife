#include "GachaHolder.h"

void tol::GachaHolder::setup()
{
    gachabutton = std::make_shared<tol::GachaButton>();
    item = std::make_shared<tol::GachaItem>();


    gachabutton->setup();
    item->setup();
}

void tol::GachaHolder::update()
{
    if (!fadein->isFadeEnd())return;
    gachabutton->update();
    item->update();
}

void tol::GachaHolder::draw()
{
    gachabutton->drawReflect();
    if (!fadein->isFadeEnd())return;
    item->drawReflect();

}

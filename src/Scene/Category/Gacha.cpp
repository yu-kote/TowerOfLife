#include "Gacha.h"

#include "../../Object/UI/UICamera/UICamera.h"
#include "../../Object/UI/TolUI/Gacha/GachaHolder.h"

Gacha::Gacha()
{
}

void Gacha::setup()
{
    // UI
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::GachaHolder>();

    entities.setup();
    ui_entities.setup();
}

void Gacha::update()
{
    entities.update();
    ui_entities.update();
}

void Gacha::draw()
{
    entities.draw();
    ui_entities.draw();
}

void Gacha::shift()
{
}

void Gacha::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}

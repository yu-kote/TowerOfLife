#include "TolStage.h"

void tol::TolStage::setup()
{
    block_holder.setup();
}

void tol::TolStage::update()
{
    block_holder.update();
}

void tol::TolStage::draw()
{
    block_holder.draw();
}

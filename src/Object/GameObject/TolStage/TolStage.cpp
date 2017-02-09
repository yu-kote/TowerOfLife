#include "TolStage.h"

void tol::TolStage::setup()
{
    block_holder.setPlayer(player);
    block_holder.setCamera(camera);

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

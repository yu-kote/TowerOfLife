#include "TolBlockActions.h"
#include "TolBlock.h"

using namespace ci;
using namespace ci::app;


tol::NormalBlock::NormalBlock(TolBlock * block_) :
    TolBlockActionBase(block_)
{
}

void tol::NormalBlock::update()
{

}

tol::RoundTripBlock::RoundTripBlock(TolBlock * block_) :
    TolBlockActionBase(block_)
{
    movecount = 0;
}

void tol::RoundTripBlock::update()
{
    movecount += 0.1f;
    block->transform.position.x = start_pos.x + sin(0.7f + 0.3f * movecount);
}

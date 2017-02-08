#include "TolBlockActionBase.h"
#include "TolBlock.h"

tol::TolBlockActionBase::TolBlockActionBase(TolBlock * block_)
{
    block = block_;
    start_pos = block->transform.position;
}

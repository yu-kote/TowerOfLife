#include "TolBlockHolder.h"

using namespace ci;
using namespace ci::app;


void tol::TolBlockHolder::setup()
{
    z_num = 3;
    x_num = 3;
    block_interval = 10;
    current_top_height = 0;
    height_interval = 10;


    std::vector<TolBlockActionType> addtypes;
    for (int i = 0; i < z_num * x_num; i++)
    {
        addtypes.push_back(TolBlockActionType::ROUNDTRIP);
    }

    addOneStepBlocks(addtypes);
}

void tol::TolBlockHolder::update()
{
    for (auto & it : blocks)
        (*it).update();
}

void tol::TolBlockHolder::draw()
{
    pushModelView();

    for (auto & it : blocks)
        (*it).draw();

    popModelView();
}

void tol::TolBlockHolder::addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes)
{
    int x = 0;
    int z = 0;
    for (int i = 0; i < z_num * x_num; i++)
    {

        std::shared_ptr<TolBlock> block = std::make_shared<TolBlock>();

        block->transform.position.x = x * block_interval;
        block->transform.position.z = z * block_interval;
        block->transform.position.y = current_top_height;

        block->setup();

        switch (addblocktypes[i])
        {
        case TolBlockActionType::NORMAL:
            block->setBlockAction<NormalBlock>();
            break;
        case TolBlockActionType::ROUNDTRIP:
            block->setBlockAction<RoundTripBlock>();
            break;
        }
        blocks.push_back(std::move(block));

        {// “ñŽŸ”z—ñ‚ÌŒvŽZ
            if (x == x_num - 1)
            {
                z += 1;
                z = z % z_num;
            }
            x += 1;
            x = x % x_num;
        }
    }
    current_top_height += height_interval;
}

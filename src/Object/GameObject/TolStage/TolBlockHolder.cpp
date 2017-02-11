#include "TolBlockHolder.h"

using namespace ci;
using namespace ci::app;


void tol::TolBlockHolder::setup()
{
    z_num = 3;
    x_num = 3;
    block_interval = 20;
    current_top_height = 0;
    height_interval = 12;


    Vec2f center_num = twoDimensionalArrayCenterPoint(x_num, z_num);
    Vec3f center = Vec3f(center_num.x * block_interval,
                         0,
                         center_num.y * block_interval);
    camera->transform.position += center;
    ease_eyepoint = Vec3f::zero();
    ease_center = Vec3f::zero();

    std::vector<TolBlockActionType> addtypes;
    for (int i = 0; i < z_num * x_num; i++)
    {
        addtypes.push_back(TolBlockActionType::NORMAL);
    }

    addOneStepBlocks(addtypes);

    for (int i = 0; i < 10; i++)
    {
        addOneStepBlocks(addtypes);
    }
}

void tol::TolBlockHolder::update()
{
    decideLookAtCamera();
    playerSetStandRay();
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

void tol::TolBlockHolder::playerSetStandRay()
{
    player->setStandRayIntersection(hitValueNearInZero(player->getStandRay()));
    player->setRizeRayIntersecion(hitValueNearInZero(player->getRizeRay()));
}

float tol::TolBlockHolder::hitValueNearInZero(const ci::Ray & ray)
{
    float high_near_intersection = std::numeric_limits<float>().min();
    float low_near_intersection = std::numeric_limits<float>().max();
    float near_intersection = 0.0f;
    for (int i = 0; i < blocks.size(); i++)
    {
        float intersection = blocks[i]->calcMeshIntersection(ray);
        if (intersection != std::numeric_limits<float>().max())
        {
            if (intersection < 0.0f)
                if (intersection > high_near_intersection)
                    high_near_intersection = intersection;
            if (intersection > 0.0f)
                if (intersection < low_near_intersection)
                    low_near_intersection = intersection;
        }
    }
    if (abs(high_near_intersection) > abs(low_near_intersection))
        near_intersection = high_near_intersection;
    else
        near_intersection = low_near_intersection;
    return near_intersection;
}

void tol::TolBlockHolder::decideLookAtCamera()
{
    Vec2f center_num = twoDimensionalArrayCenterPoint(x_num, z_num);
    float y = convertBlockHeight(player->transform.position.y);
    Vec3f eyepoint = Vec3f(center_num.x * block_interval,
                           y,
                           center_num.y * block_interval);

    y = centerBetweenBlockHeight(player->transform.position.y);
    Vec3f center = Vec3f(center_num.x * block_interval,
                         y,
                         center_num.y * block_interval);

    float ease_speed = 0.05f;
    ease_eyepoint += (eyepoint - ease_eyepoint) * ease_speed;
    ease_center += (center - ease_center) * ease_speed;


    camera->lookAt(ease_eyepoint, ease_center);
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

        block->setPlayer(player);


        switch (addblocktypes[i])
        {
        case TolBlockActionType::NORMAL:
            block->setBlockAction<NormalBlock>();
            break;
        case TolBlockActionType::ROUNDTRIP:
            block->setBlockAction<RoundTripBlock>();
            break;
        }

        block->setup();
        blocks.push_back(std::move(block));
        {// 二次配列の計算
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

bool tol::TolBlockHolder::isBlockOutOfRange(const int & num)
{
    return (num > blocks.size() - 1) ? true : false;
}

int tol::TolBlockHolder::adjusMinMaxNum(const int& num, const int& max_value)
{
    return (num > max_value - 1) ? max_value - 1 : (num < 0) ? 0 : num;
}

ci::Vec2f tol::TolBlockHolder::twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y)
{
    float center_x, center_y;
    if (size_x * size_y % 2 == 0)
    {
        if (size_x % 2 == 0)
            center_x = size_x / 2 - 0.5f;
        else
            center_x = (size_x - 1) / 2;
        if (size_y % 2 == 0)
            center_y = size_y / 2 - 0.5f;
        else
            center_y = (size_y - 1) / 2;
    }
    else
    {
        center_x = (size_x - 1) / 2;
        center_y = (size_y - 1) / 2;
    }

    return ci::Vec2f(center_x, center_y);
}

float tol::TolBlockHolder::convertBlockHeight(const float & height)
{
    float block_height = height / height_interval;
    int skip_value = z_num * x_num;
    int block_num = adjusMinMaxNum(int(block_height) * skip_value, blocks.size());

    return blocks[block_num]->transform.position.y + height_interval;
}

float tol::TolBlockHolder::centerBetweenBlockHeight(const float & height)
{
    float block_height_convert = height / height_interval;
    int block_num = (int)block_height_convert;
    // ブロックの番号*ブロックの間隔 + ブロックの真ん中
    return block_num * height_interval + (height_interval / 2);
}

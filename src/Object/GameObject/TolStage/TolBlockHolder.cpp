#include "TolBlockHolder.h"
#include "../../../Utility/Random/Random.h"

using namespace ci;
using namespace ci::app;


void tol::TolBlockHolder::setup()
{
    blocks.clear();
    {// json予定
        z_num = 3;
        x_num = 3;
        block_space = 17;
        height_interval = 12;
    }
    current_top_height = 0;

    ease_eyepoint = Vec3f::zero();
    ease_center = Vec3f::zero();

    camera_height = 0.0f;
    camera_up_time = 180;
    camera_up_remaining_time = camera_up_time;

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
    addBlocks();
    decideLookAtCamera();
    playerSetStandRay();
    cameraDistanceToBlock();
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

void tol::TolBlockHolder::reset()
{
    setup();
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
    { // カメラを自動的に上に上げる処理
        if (camera_up_remaining_time-- < 0)
        {
            camera_up_remaining_time = camera_up_time;

            camera_height += height_interval;
        }
        else
        {
            if (camera_height < player->transform.position.y - height_interval)
            {
                camera_up_remaining_time = camera_up_time;
                camera_height += height_interval;
            }
        }
    }
    // カメラを真ん中に合わせる
    Vec2f center_num = twoDimensionalArrayCenterPoint(x_num, z_num);

    // カメラの高さをいい感じにブロックのところに合わせる
    float y = camera_height + height_interval;
    Vec3f eyepoint = Vec3f(center_num.x * block_space,
                           y,
                           center_num.y * block_space);

    // 今の高さを見てカメラの見る位置をブロックとブロックの間に合わせる
    y = centerBetweenBlockHeight(camera_height);
    Vec3f center = Vec3f(center_num.x * block_space,
                         y,
                         center_num.y * block_space);

    // イージングさせる
    float ease_speed = 0.05f;
    ease_eyepoint += (eyepoint - ease_eyepoint) * ease_speed;
    ease_center += (center - ease_center) * ease_speed;

    camera->lookAt(ease_eyepoint, ease_center);
}

void tol::TolBlockHolder::cameraDistanceToBlock()
{
    for (auto& it : blocks)
    {
        if (camera->transform.position.y - 100 > it->transform.position.y)
        {
            for (int i = 0; i < z_num * x_num; i++)
            {
                blocks.pop_front();
            }
            return;
        }
    }
}

void tol::TolBlockHolder::addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes)
{
    int x = 0;
    int z = 0;
    for (int i = 0; i < z_num * x_num; i++)
    {
        std::shared_ptr<TolBlock> block = std::make_shared<TolBlock>();

        block->transform.position.x = x * block_space;
        block->transform.position.z = z * block_space;
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

    {
        int count = current_top_height / height_interval;
        bool is_coin_pop = (count % 2 == 1) ? true : false;
        if (is_coin_pop)
        {
            RandomInt rand(0, z_num * x_num - 1);
            Vec3f pos = blocks[rand()]->transform.position;
            coin_holder->instanceCoin(pos.xz(), current_top_height + 2, 1);
        }
    }
}

void tol::TolBlockHolder::addBlocks()
{
    if (player->transform.position.y > current_top_height - height_interval * 1)
    {
        std::vector<TolBlockActionType> addtypes;
        for (int i = 0; i < z_num * x_num; i++)
        {
            addtypes.push_back(TolBlockActionType::NORMAL);
        }
        for (int i = 0; i < 5; i++)
        {
            addOneStepBlocks(addtypes);
        }
    }
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



float tol::TolBlockHolder::centerBetweenBlockHeight(const float & height)
{
    float block_height_convert = height / height_interval;
    int block_step_num = (int)block_height_convert;
    // ブロックの段数 * ブロックの間隔 + ブロックの真ん中
    return block_step_num * height_interval + (height_interval / 2);
}

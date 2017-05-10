#include "Camera.h"
#include "../../../Utility/Interface/Interface.h"
#include "../../../Utility/Input/InputEvent.h"
#include "../../../Utility/Resize/Resize.h"

#include "../Player/Player.h"
#include "../TolStage/TolBlockHolder.h"

#include "../../../Tol/TolGameDataManager.h"

using namespace ci;
using namespace ci::app;

tol::Camera::Camera()
{

}

void tol::Camera::setup()
{
    objective_distance_init_value = Vec3f(0, 15, -50);
    objective_distance = objective_distance_init_value;
    transform.position = objective_distance;
    center_of_interest_point = Vec3d::zero();
    camera.lookAt(transform.position, center_of_interest_point);
    camera.setPerspective(60.0f, getWindowAspectRatio(), 1.0f, 2000.0f);

    jsonSetup();
}

void tol::Camera::update()
{
    WindowResize.setPerspCameraResize = [&]()
    {
        camera.setAspectRatio(getWindowAspectRatio());
    };
    camera.lookAt(transform.position, center_of_interest_point);

    decideLookAtCamera();
    upCamera();
    easeCamera();
}

// デバッグ用にカメラを近づけたり引いたりできるようにした
void tol::Camera::laterUpdate()
{
    Vec3f vec = Vec3f::zero();

    Vec3f init_value_normalize = objective_distance_init_value.normalized();

    if (env.isPress(KeyEvent::KEY_i))
    {
        Vec3f approach_value = init_value_normalize.inverse();
        vec += approach_value;
    }
    if (env.isPress(KeyEvent::KEY_k))
    {
        Vec3f leave_value = init_value_normalize;
        vec += leave_value;
    }
    if (env.isPress(KeyEvent::KEY_UP))
    {
        float up_vec = init_value_normalize.y;
        vec.y += up_vec;
    }
    if (env.isPress(KeyEvent::KEY_DOWN))
    {
        float down_vec = -init_value_normalize.y;
        vec.y += down_vec;
    }
    objective_distance += vec;
    objective_distance = restorePeak(objective_distance, objective_distance_init_value);
    transform.position += objective_distance;
}

void tol::Camera::awakeDraw()
{
    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::pushMatrices();
    gl::setMatrices(camera);
}

void tol::Camera::laterDraw()
{
    gl::popMatrices();
}

ci::Vec3f tol::Camera::restorePeak(ci::Vec3f check_value, ci::Vec3f restore_value)
{
    if (restore_value.x >= 0.0f)
        if (check_value.x < restore_value.x)
            check_value.x = restore_value.x;
    if (restore_value.x < 0.0f)
        if (check_value.x > restore_value.x)
            check_value.x = restore_value.x;

    if (restore_value.y >= 0.0f)
        if (check_value.y < restore_value.y)
            check_value.y = restore_value.y;
    if (restore_value.y < 0.0f)
        if (check_value.y > restore_value.y)
            check_value.y = restore_value.y;

    if (restore_value.z >= 0.0f)
        if (check_value.z < restore_value.z)
            check_value.z = restore_value.z;
    if (restore_value.z < 0.0f)
        if (check_value.z > restore_value.z)
            check_value.z = restore_value.z;

    return check_value;
}

void tol::Camera::jsonSetup()
{
    if (json.openJson("GameData/TolStage.json"))
    {
        auto stage_info = json.root["stage_info"];
        camera_up_time = stage_info["camera_up_time"].asInt();

        camera_height = 0.0f;
        camera_up_remaining_time = camera_up_time;

        ease_eyepoint = Vec3f::zero();
        ease_center = Vec3f::zero();
        ease_speed = stage_info["ease_speed"].asFloat();
    }
}

void tol::Camera::decideLookAtCamera()
{
    lookAt(ease_eyepoint, ease_center);
}

void tol::Camera::upCamera()
{
    if (player->getUpdateActive() == false)
        return;
    if (player->isNotOperation())
        return;

    if (TolData.using_item == TolItem::SCROLL_STOP)
        camera_up_remaining_time = camera_up_time;

    // カメラを自動的に上に上げる処理
    if (camera_up_remaining_time-- < 0)
    {
        camera_up_remaining_time = camera_up_time;
        camera_height += block_holder->getHeightInterval();
    }
    else
    {
        if (camera_height < player->transform.position.y - block_holder->getHeightInterval() &&
            player->isStand())
        {
            camera_up_remaining_time = camera_up_time;
            camera_height += block_holder->getHeightInterval();
        }
    }

    tol::TolData.score = camera_height;
}

void tol::Camera::easeCamera()
{
    // カメラを真ん中に合わせる
    Vec2f center_num = block_holder->getCenterPos();

    // カメラの高さをいい感じにブロックのところに合わせる
    float y = camera_height + block_holder->getHeightInterval();
    Vec3f eyepoint = Vec3f(center_num.x * block_holder->getBlockSpace(),
                           y,
                           center_num.y * block_holder->getBlockSpace());

    // 今の高さを見てカメラの見る位置をブロックとブロックの間に合わせる
    y = block_holder->centerBetweenBlockHeight(camera_height);
    Vec3f center = Vec3f(center_num.x * block_holder->getBlockSpace(),
                         y,
                         center_num.y * block_holder->getBlockSpace());

    // イージングさせる
    ease_eyepoint += (eyepoint - ease_eyepoint) * ease_speed;
    ease_center += (center - ease_center) * ease_speed;
}

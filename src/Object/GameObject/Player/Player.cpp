#include "Player.h"
#include "cinder/gl/gl.h"
#include "../../Component/Components/Material.h"
#include "../../Component/Components/Texture.h"

#include "../../../Task/ObjDataManager.h"
#include "../../../Task/SoundManager.h"
#include "../../../Utility/Input/InputEvent.h"

#include "../../../Tol/TolGameDataManager.h"


using namespace ci;
using namespace ci::app;

void tol::Player::setup()
{
    mesh = &ObjDataGet.find("Player");

    transform.position.y = 5;
    transform.scale = Vec3f(1, 1, 1);

    gl::Material m = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
                                  80.0f,
                                  ci::ColorA(0.2f, 0.5f, 1.0f));
    addComponent<tol::Material>(tol::Material(m));
    //addComponent<tol::Texture>(tol::Texture("Player"));

    state = State::STAND;

    ground_move_speed = 0.02f;
    ground_move_speed_max = 0.4f;
    moving_distance = Vec3f::zero();
    is_max_speed = false;
    air_move_speed = 0.06f;

    gravity = 0.07f;
    fall_speed_max = 0.6f;

    jump_power = 0.9f;
    jump_duration = 10;
    jump_time = 0;

    is_restart = false;
    not_operation = false;
    is_dead_distance_judgment = 50;

    can_one_more_jump = false;
    jump_step = 0;
}

void tol::Player::update()
{
    // ゲームパッドの左スティックで移動
    axisMove();

    // ベクトルから向きを求める
    vecRotate();

    // レイの更新
    rayUpdate();

    // 処理順注意(vecを足してから消す)
    useGravity();
    stand();

    // 処理順注意
    jump();
    hitTheHead();

    // カメラとの角度差を埋める ※ カメラを回転させないため使ってない
    {
        float angle_difference = angleDifference(camera->transform.angle.y, transform.angle.y);
        angle_difference *= env.getPadAxis("Vertical_Left");
        transform.angle.y = angle_difference;


        camera_ray.setOrigin(transform.position);
        camera_ray.setDirection(camera->getCamera().getEyePoint() - transform.position);
    }

    // 状態の更新
    stateUpdate();

    // ゲームオーバー
    gameover();

    // デバッグ用にリスタート
    if (env.isPush(KeyEvent::KEY_RETURN))
        is_restart = true;
}

void tol::Player::draw()
{
    gl::drawCube(Vec3f::zero(), Vec3f(2, 2, 2));

    gl::translate(0, -transform.scale.y, 0);
    gl::scale(0.4f, 0.4f, 0.4f);
    //gl::draw(*mesh);
}


void tol::Player::laterDraw()
{
}

void tol::Player::axisMove()
{
    // 操作不能かどうか
    if (not_operation)return;

    // 左スティックのベクトルをもらう
    auto v = getLeftAxisVec();

    { // デバッグ用のキー移動
        if (env.isPress(KeyEvent::KEY_a))
        {
            v.x = (ground_move_speed_max * 1);
            moving_distance.x = (ground_move_speed_max * 1);
            is_max_speed = true;
        }
        if (env.isPress(KeyEvent::KEY_d))
        {
            v.x = -(ground_move_speed_max * 1);
            moving_distance.x = -(ground_move_speed_max * 1);
            is_max_speed = true;
        }
        if (env.isPress(KeyEvent::KEY_w))
        {
            v.y = (ground_move_speed_max * 1);
            moving_distance.y = (ground_move_speed_max * 1);
            is_max_speed = true;
        }
        if (env.isPress(KeyEvent::KEY_s))
        {
            v.y = -(ground_move_speed_max * 1);
            moving_distance.y = -(ground_move_speed_max * 1);
            is_max_speed = true;
        }
    }

    if (state == State::STAND || state == State::MOVING)
    {
        moving_distance.x = ground_move_speed  * v.x;
        moving_distance.z = ground_move_speed  * v.y;

        velocity.x += moving_distance.x;
        velocity.z += moving_distance.z;

        if (state == State::STAND)
            is_max_speed = false;

        // 速度を一定に抑える処理
        auto max_vec_x = abs(ground_move_speed_max * v.x);
        if (velocity.x > max_vec_x)
        {
            velocity.x = max_vec_x;
            is_max_speed = true;
        }
        if (velocity.x < -max_vec_x)
        {
            velocity.x = -max_vec_x;
            is_max_speed = true;
        }
        auto max_vec_z = abs(ground_move_speed_max * v.y);
        if (velocity.z > max_vec_z)
        {
            velocity.z = max_vec_z;
            is_max_speed = true;
        }
        if (velocity.z < -max_vec_z)
        {
            velocity.z = -max_vec_z;
            is_max_speed = true;
        }

        // 助走してなかったらスティックを倒している分の最大速度を入れる
        if (is_max_speed)
        {
            Vec3f max_speed = Vec3f(ground_move_speed_max * v.x, 0, ground_move_speed_max * v.y);
            velocity.x = max_speed.x;
            velocity.z = max_speed.z;
        }

        jump_moment_vec = Vec3f::zero();
    }


    if (state == State::FALL || state == State::RIZING)
    {
        velocity.x += air_move_speed  * v.x;
        velocity.z += air_move_speed  * v.y;

        // 速度を一定に抑える処理
        auto max_vec_x = abs(ground_move_speed_max);
        if (velocity.x > max_vec_x)
            velocity.x = max_vec_x;
        if (velocity.x < -max_vec_x)
            velocity.x = -max_vec_x;

        auto max_vec_z = abs(ground_move_speed_max);
        if (velocity.z > max_vec_z)
            velocity.z = max_vec_z;
        if (velocity.z < -max_vec_z)
            velocity.z = -max_vec_z;
        velocity.x *= 0.95f;
        velocity.z *= 0.95f;
    }

    if (state == State::STAND)
    {
        valueSlowlyToZero(velocity.x, ground_move_speed);
        valueSlowlyToZero(velocity.z, ground_move_speed);
    }

    transform.translateXZ(velocity, transform.angle.y);
}

ci::Vec2f tol::Player::getLeftAxisVec()
{
    auto x_axis = env.getPadAxis("Horizontal_Left") * -1;
    auto y_axis = env.getPadAxis("Vertical_Left");

    auto min_speed = 0.2f;
    if (x_axis <= min_speed && x_axis >= -min_speed)
        x_axis = 0;
    if (y_axis <= min_speed && y_axis >= -min_speed)
        y_axis = 0;

    auto axis_angle = atan2(y_axis, x_axis);
    axis_angle = toDegrees(axis_angle);

    float vx = cosf(axis_angle * M_PI / 180.0f) * abs(x_axis);
    float vy = sinf(axis_angle * M_PI / 180.0f)* abs(y_axis);

    return ci::Vec2f(vx, vy);
}

void tol::Player::vecRotate()
{
    if (velocity.x == 0.0f && velocity.z == 0.0f) return;

    Vec3f rotateaxis = Vec3f(0.0f, 0.0f, 1.0f);
    Vec3f targetvec = Vec3f(velocity.x, 0, velocity.z);
    targetvec.normalize();

    Vec3f quataxis = rotateaxis.cross(targetvec);
    Quatf targetquat;

    // 左回り
    if (atan2f(velocity.x, velocity.z) > 0.0f)
        targetquat = Quatf(quataxis,
                           atan2f(velocity.x, velocity.z));
    // 右回り
    else if (atan2f(velocity.x, velocity.z) < 0.0f)
        targetquat = Quatf(quataxis,
                           -atan2f(velocity.x, velocity.z));

    auto axis_length = rotateaxis.xz().cross(targetvec.xz());
    if (axis_length == 0.0f)
    {
        if (velocity.z > 0.0f)
            targetquat = Quatf(Vec3f::yAxis(), 0);
        if (velocity.z < 0.0f)
            targetquat = Quatf(Vec3f::yAxis(), (float)M_PI);
    }

    transform.rotation = targetquat.toMatrix44();
}

float tol::Player::angleDifference(const float & angle1, const float & angle2)
{
    if (angle1 == angle2)
    {
        return 0.0f;
    }
    float angle_difference = angle1 - angle2;
    if (angle_difference < -M_PI)
    {
        angle_difference = 2.0f * M_PI + angle_difference;
    }
    else if (angle_difference > M_PI)
    {
        angle_difference = 2.0f * -M_PI + angle_difference;
    }
    angle_difference = std::fmodf(angle_difference, 2.0f * M_PI);
    return angle_difference;
}

void tol::Player::valueSlowlyToZero(float & value, float t)
{
    if (value > 0.0f)
        value -= t;
    if (value < 0.0f)
        value += t;
    if (value <= t && value >= -t)
        value = 0.0f;
}

void tol::Player::rayUpdate()
{
    stand_ray.setOrigin(transform.position);
    stand_ray.setDirection(Vec3f(0, -1.5f, 0));

    rize_ray.setOrigin(transform.position);
    rize_ray.setDirection(Vec3f(0, 1.5f, 0));
}

void tol::Player::jump()
{
    if (TolData.using_item == TolItem::TWO_STEP_JUMP)
    {
        if (jump_step == 2 || jump_step == 3)
        {
            if (env.isPadPress(env.BUTTON_2))
            {
                jump_time++;
                if (jump_time < jump_duration)
                    velocity.y = jump_power;
                if (jump_step == 2)
                    SoundGet.find("Jump")->start();
                jump_step = 3;
            }
            else
            {
                if (jump_step == 3)
                    jump_step = 4;
            }
        }
    }

    if (env.isPadPress(env.BUTTON_2))
    {
        if (can_jump)
        {
            if (jump_step == 0)
                SoundGet.find("Jump")->start();
            jump_time++;
            if (jump_time < jump_duration)
                velocity.y = jump_power;
            jump_step = 1;
        }
        is_jump_key_press = true;
    }
    else
    {
        if (jump_step == 1)
        {
            jump_step = 2;
            jump_time = 0;
        }
        is_jump_key_press = false;
        can_jump = false;
    }


    if (env.isPress(KeyEvent::KEY_SPACE))
    {
        if (jump_time < jump_duration)
        {
            velocity.y = jump_power;
        }
        jump_time++;
    }
}

void tol::Player::useGravity()
{
    velocity.y -= gravity;
    if (velocity.y < -fall_speed_max)
        velocity.y = -fall_speed_max;
}

void tol::Player::stand()
{
    if (velocity.y < 0)
        if (stand_ray_intersection < abs(stand_ray.getDirection().y) && stand_ray_intersection > 0.0f)
        {
            velocity.y = 0;
        }
}

void tol::Player::hitTheHead()
{
    if (velocity.y > 0)
        if (rize_ray_intersection < 1 && rize_ray_intersection  > 0.0f)
        {
            state = State::FALL;
            velocity.y = 0;
        }
}

void tol::Player::stateUpdate()
{
    if (velocity.y == 0.0f)
        state = State::STAND;
    if (moving_distance.x != 0.0f || moving_distance.z != 0.0f)
        state = State::MOVING;
    if (velocity.y < 0.0f)
        state = State::FALL;
    if (velocity.y > 0.0f)
        state = State::RIZING;

    switch (state)
    {
    case State::STAND:
        if (can_jump == false)
        {
            jump_time = 0;
            jump_step = 0;
        }
        if (is_jump_key_press == false)
            can_jump = true;
        can_one_more_jump = true;
        break;
    case State::MOVING:
        if (can_jump == false)
        {
            jump_time = 0;
            jump_step = 0;
        }
        if (is_jump_key_press == false)
            can_jump = true;
        can_one_more_jump = true;
        break;
    case State::RIZING:
        break;
    case State::FALL:
        break;
    }

    if (current_state != state)
    {
        if (current_state == State::MOVING)
            jump_moment_vec = velocity;

        if (current_state == State::FALL)
            SoundGet.find("Landing")->start();

        current_state = state;
    }
}

void tol::Player::gameover()
{
    if (is_restart)
    {
        is_restart = false;
        reset();
    }
    if (not_operation == true)
        return;

    if (camera->transform.position.y - is_dead_distance_judgment > transform.position.y)
    {
        not_operation = true;
    }
}

void tol::Player::reset()
{
    transform.position = Vec3f(0, 5, 0);
    velocity = Vec3f::zero();
    moving_distance = Vec3f::zero();
    jump_moment_vec = Vec3f::zero();
    not_operation = false;
}

// 影

void tol::PlayerShadow::setup()
{
    gl::Material m = gl::Material(ci::ColorA(0, 0, 0, 0.7f),
                                  ci::ColorA(0, 0, 0, 0.7f),
                                  ci::ColorA(0, 0, 0, 0.7f),
                                  80.0f,
                                  ci::ColorA(0, 0, 0, 0.7f));

    addComponent<tol::Material>(tol::Material(m));
}

void tol::PlayerShadow::draw()
{
    ci::Vec3f pos = player->getStandRay().calcPosition(player->getStandRayIntersection());

    pos.y -= player->getGravityPower() + 0.1f;
    ci::gl::drawCube(pos, ci::Vec3f(2, 0.0f, 2));
}

void tol::DebugDraw::setup()
{
    hit_sphere_y = 0.0f;
}


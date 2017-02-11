#include "Player.h"
#include "cinder/gl/gl.h"
#include "../../Component/Components/Material.h"
#include "../../../Utility/Interface/Interface.h"
#include "../../../Utility/Input/InputEvent.h"


using namespace ci;
using namespace ci::app;

void tol::Player::setup()
{

    transform.position.y = 5;
    transform.scale = Vec3f(2, 2, 2);

    Params->addParam("player_pos", &transform.position);
    gl::Material m = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
                                  80.0f,
                                  ci::ColorA(0.5f, 0.5f, 0.8f));

    addComponent<tol::Material>(tol::Material(m));

    ground_move_speed = 0.4f;
    ground_move_speed_max = 0.4f;

    air_move_speed = 0.2f;

    gravity = 0.07f;
    fall_speed_max = 0.6f;
    jump_power = 0.9f;
    jump_duration = 10;
    jump_time = 0;


    stand_ray.setOrigin(transform.position);
    stand_ray.setDirection(Vec3f(0, -transform.scale.y / 2, 0));
    stand_ray_intersection = 0.0f;

    rize_ray.setOrigin(transform.position);
    rize_ray.setDirection(Vec3f(0, transform.scale.y / 2, 0));
    rize_ray_intersection = 0.0f;
}

void tol::Player::update()
{
    // ゲームパッドの左スティックで移動
    axisMove();

    // ベクトルから向きを求める
    //vecRotate();

    // 処理順注意(vecを足してから消す)
    useGravity();
    stand();
    // 処理順注意
    jump();
    hitTheHead();

    // カメラとの角度差を埋める
    {
        float angle_difference = angleDifference(camera->transform.angle.y, transform.angle.y);
        angle_difference *= env.getPadAxis("Vertical_Left");
        transform.angle.y = angle_difference;
    }

    // レイの更新
    {
        stand_ray.setOrigin(transform.position);
        stand_ray.setDirection(Vec3f(0, -transform.scale.y / 2, 0));

        rize_ray.setOrigin(transform.position);
        rize_ray.setDirection(Vec3f(0, transform.scale.y / 2, 0));
    }

    stateUpdate();
    reset();
}

void tol::Player::draw()
{
    gl::drawStrokedCube(Vec3f::zero(), Vec3f(1, 1, 1));


    gl::drawVector(stand_ray.getOrigin() - stand_ray.getOrigin(),
                   stand_ray.getOrigin() + stand_ray.getDirection() - stand_ray.getOrigin());

    gl::drawSphere(stand_ray.calcPosition(stand_ray_intersection) - stand_ray.getOrigin(), 0.2f);
}


void tol::Player::laterDraw()
{


}

void tol::Player::axisMove()
{
    if (state == State::STAND)
    {
        velocity.x = (ground_move_speed  * env.getPadAxis("Horizontal_Left") * -1);
        velocity.z = ground_move_speed  * env.getPadAxis("Vertical_Left");
    }

    if (env.isPress(KeyEvent::KEY_a))
    {
        velocity.x = (ground_move_speed * 1);
    }
    if (env.isPress(KeyEvent::KEY_d))
    {
        velocity.x = -(ground_move_speed * 1);

    }
    if (env.isPress(KeyEvent::KEY_w))
    {
        velocity.z = (ground_move_speed * 1);
    }
    if (env.isPress(KeyEvent::KEY_s))
    {
        velocity.z = -(ground_move_speed * 1);

    }

    if (state == State::FALL || state == State::RIZING)
    {
        velocity.x = jump_vec.x;
        velocity.z = jump_vec.z;
        //velocity.x += air_move_speed * env.getPadAxis("Horizontal_Left") * -1;
        //velocity.z += air_move_speed * env.getPadAxis("Vertical_Left");
    }


    Vec2f c = transform.skewCorrection(Vec2f(velocity.x, velocity.z));

    velocity.x = c.x;
    velocity.z = c.y;


    float min_move = 0.1f;
    if (velocity.x <= min_move && velocity.x >= -min_move)
        velocity.x = 0;
    if (velocity.z <= min_move && velocity.z >= -min_move)
        velocity.z = 0;

    transform.translateXZ(velocity, transform.angle.y);
}

void tol::Player::vecRotate()
{
    Vec3f rotateaxis = Vec3f(0.0f, 0.0f, 1.0f);
    Vec3f targetvec = Vec3f(velocity.x, 0, velocity.z);
    rotateaxis.normalize();
    targetvec.normalize();

    Vec3f quataxis = rotateaxis.cross(targetvec);
    Quatf targetquat;

    //console() << atan2f(velocity.x, velocity.z) << std::endl;

    if (atan2f(velocity.x, velocity.z) >= 0.0f)
        targetquat = Quatf(quataxis,
                           atan2f(velocity.x, velocity.z));
    else if (atan2f(velocity.x, velocity.z) < 0.0f)
        targetquat = Quatf(quataxis,
                           -atan2f(velocity.x, velocity.z));

    if (targetquat.getAngle() <= M_PI - 0.000001)
        transform.rotation = targetquat.toMatrix44();

    if (velocity.x == 0.0f && velocity.z == 0.0f)
        transform.rotation = current_quat.toMatrix44();
    else
        current_quat = transform.rotation;
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
        angle_difference = 2 * M_PI + angle_difference;
    }
    else if (angle_difference > M_PI)
    {
        angle_difference = 2 * -M_PI + angle_difference;
    }
    angle_difference = std::fmod(angle_difference, 2 * M_PI);
    return angle_difference;
}

void tol::Player::jump()
{
    if (env.isPadPress(env.BUTTON_2))
    {
        if (jump_time < jump_duration)
        {
            velocity.y = jump_power;
        }
        jump_time++;
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

    if (transform.position.y < 0)
        transform.position.y = 0;
}

void tol::Player::stand()
{
    if (velocity.y < 0)
        if (stand_ray_intersection < transform.scale.y && stand_ray_intersection > 0.0f)
        {
            velocity.y = 0;
            state = State::STAND;
        }
}

void tol::Player::hitTheHead()
{
    if (velocity.y > 0)
        if (rize_ray_intersection < transform.scale.y && rize_ray_intersection  > 0.0f)
        {
            state = State::FALL;
            velocity.y = 0;
        }
}

void tol::Player::stateUpdate()
{
    if (velocity.y < 0.0f)
        state = State::FALL;
    if (velocity.y > 0.0f)
        state = State::RIZING;



    switch (state)
    {
    case State::STAND:
        jump_time = 0;
        break;
    case State::RIZING:
        break;
    case State::FALL:
        break;
    }

    if (current_state != state)
    {
        if (current_state == State::STAND)
            jump_vec = velocity;


        current_state = state;
    }
}

void tol::Player::reset()
{
    if (!env.isPush(KeyEvent::KEY_RETURN))return;
    transform.position = Vec3f(0, 5, 0);
}



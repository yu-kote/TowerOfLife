#include "Player.h"
#include "cinder/gl/gl.h"
#include "../../Component/Components/Material.h"
#include "../../../Utility/Interface/Interface.h"
#include "../../../Utility/Input/InputEvent.h"


using namespace ci;
using namespace ci::app;

void tol::Player::setup()
{
    Params->addParam("player_pos", &transform.position);
    gl::Material m = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
                                  80.0f,
                                  ci::ColorA(0.5f, 0.5f, 0.8f));

    addComponent<tol::Material>(tol::Material(m));

    move_speed = 0.5f;
    gravity = 0.1f;
    jump_power = 1.0f;
}

void tol::Player::update()
{
    // ゲームパッドの左スティックで移動
    axisMove();

    // ベクトルから向きを求める
    vecRotate();

    jump();
    useGravity();

    // カメラとの角度差を埋める
    {
        float angle_difference = angleDifference(camera->transform.angle.y, transform.angle.y);
        angle_difference *= env.getPadAxis("Vertical_Left");
        transform.angle.y = angle_difference;
    }
}

void tol::Player::draw()
{
    gl::drawCube(Vec3f::zero(), Vec3f(2, 2, 2));
}

void tol::Player::axisMove()
{
    velocity.x = move_speed  * env.getPadAxis("Horizontal_Left") * -1;
    velocity.z = move_speed  * env.getPadAxis("Vertical_Left");

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
    if (env.isPadPush(env.BUTTON_2))
    {
        velocity.y = jump_power;
    }
}

void tol::Player::useGravity()
{
    velocity.y -= gravity;

    if (transform.position.y < 0)
        transform.position.y = 0;
}

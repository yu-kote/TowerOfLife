#include "Camera.h"
#include "../../../Utility/Interface/Interface.h"
#include "../../../Utility/Input/InputEvent.h"
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

}

void tol::Camera::update()
{
    camera.lookAt(transform.position, center_of_interest_point);
    gl::pushMatrices();
    gl::setMatrices(camera);
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

void tol::Camera::draw()
{

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

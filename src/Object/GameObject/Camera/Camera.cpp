#include "Camera.h"
#include "../../../Utility/Interface/Interface.h"
using namespace ci;
using namespace ci::app;

tol::Camera::Camera()
{

}

void tol::Camera::setup()
{
    transform.position = Vec3f(0, 10, -20);

    camera.lookAt(transform.position, Vec3f::zero());
    camera.setPerspective(60.0f, getWindowAspectRatio(), 1.0f, 1000.0f);

    Params->addParam("camera_pos", &offset_eye_point);
}

void tol::Camera::update()
{
    camera.setEyePoint(transform.position);
    camera.setCenterOfInterestPoint(Vec3f::zero());


    gl::pushMatrices();
    gl::setMatrices(camera);
}

void tol::Camera::draw()
{

}

void tol::Camera::laterDraw()
{
    gl::popMatrices();
}

void tol::Camera::setEyePoint(ci::Vec3f pos)
{

}


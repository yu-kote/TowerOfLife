#pragma once
#include "cinder/Camera.h"
#include "../../GameObject/GameObject.h"


namespace tol
{
    class Camera : public GameObject
    {
        Camera();

        void setup();
        void update();
        void draw();

        void setEyePoint(ci::Vec3f pos);

    private:
        ci::CameraPersp camera;



    };
}
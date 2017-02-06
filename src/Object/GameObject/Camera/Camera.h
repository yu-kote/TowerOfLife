#pragma once
#include "../../GameObject/GameObject.h"
#include "cinder/Camera.h"


namespace tol
{
    class Camera : public GameObject
    {
    public:
        Camera();

        void setup()override;
        void update()override;
        void draw()override;
        void laterDraw()override;

        void setEyePoint(ci::Vec3f pos);

    private:
        ci::CameraPersp camera;
        ci::Vec3f offset_eye_point;


    };
}
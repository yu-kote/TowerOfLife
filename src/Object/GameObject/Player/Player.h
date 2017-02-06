#pragma once
#include "../GameObject.h"
#include "../Camera/Camera.h"


namespace tol
{
    class Player : public GameObject
    {
    public:

        void setup()override;
        void update()override;
        void draw()override;


        std::shared_ptr<tol::Camera> camera;
    private:

        void axisMove();
        void vecRotate();
        float angleDifference(const float& angle1, const float& angle2);

        void jump();
        void useGravity();


    private:

        ci::Vec3f velocity;
        ci::Quatf current_quat;
        float move_speed;
        float gravity;
        float jump_power;

    };


}
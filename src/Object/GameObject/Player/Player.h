#pragma once
#include "../GameObject.h"
#include "../Camera/Camera.h"
#include "cinder/Ray.h"

namespace tol
{
    class Player : public GameObject
    {
    public:

        void setup()override;
        void update()override;
        void draw()override;
        void laterDraw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }

        ci::Ray getStandRay() { return stand_ray; }
        void setStandRayIntersection(const float & t) { stand_ray_intersection = t; }

        ci::Ray getRizeRay() { return rize_ray; }
        void setRizeRayIntersecion(const float& t) { rize_ray_intersection = t; }

    private:
        std::shared_ptr<tol::Camera> camera;

        void axisMove();
        void vecRotate();
        float angleDifference(const float& angle1, const float& angle2);

        void jump();
        void useGravity();

        void stand();
        void hitTheHead();

        void stateUpdate();

        void reset();
    private:

        enum State
        {
            STAND,
            RIZING,
            FALL,
        };

        State state;
        State current_state;

        ci::Vec3f velocity;
        ci::Quatf current_quat;
        float ground_move_speed_max;
        float ground_move_speed;
        ci::Vec3f speed;

        float air_move_speed;

        float gravity;
        float fall_speed_max;

        float jump_power;
        ci::Vec3f jump_vec;
        int jump_duration;
        int jump_time;

        // 地面に立つためのレイ
        ci::Ray stand_ray;
        // 地面に立つためのレイの交差地点
        float stand_ray_intersection;

        // 天井にぶつけるためのレイ
        ci::Ray rize_ray;
        // 天井にぶつけるためのレイの交差地点
        float rize_ray_intersection;
    };


}
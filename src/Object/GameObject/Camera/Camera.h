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
        void laterUpdate()override;
        void draw()override;
        void laterDraw()override;

        void setCenterOfInretestPoint(const ci::Vec3f & point) { center_of_interest_point = point; }
        void setEyePoint(const ci::Vec3f & point) { transform.position = point; }
        void lookAt(const ci::Vec3f & eyepoint, const ci::Vec3f & target)
        {
            transform.position = eyepoint;
            center_of_interest_point = target;
        }

    private:
        ci::CameraPersp camera;

        ci::Vec3f center_of_interest_point;         // 見る先
        ci::Vec3f objective_distance;               // ステージとの距離
        ci::Vec3f objective_distance_init_value;    // ステージとの距離の初期値

        // 行き過ぎたら戻す値を返す
        ci::Vec3f restorePeak(ci::Vec3f check_value, ci::Vec3f restore_value);

    };
}
#pragma once
#include "cinder/app/AppNative.h"

namespace tol
{
    class Transform
    {
    public:
        Transform()
        {
            position = ci::Vec3f::zero();
            angle = ci::Vec3f::zero();
            rotation = ci::Quatf::identity();
            scale = ci::Vec3f(1.0f, 1.0f, 1.0f);
        }

    public:

        // 向く
        void lookAt(const Transform& target_);
        void lookAt(const ci::Vec2f& position_);

        // オイラー角でクォータニオンを回転
        void rotate(const ci::Vec3f& angle_);
        void rotate(ci::Vec3f axis_, float angle_);
        void rotate(float angle_x_, float angle_y_, float angle_z_);


        // 平面移動のみ
        void translateXZ(const ci::Vec3f& vector_, const float& angle_y_);
        // 平面移動のための行列計算
        ci::Vec3f translationXZ(const ci::Vec3f& vector_, const float& angle_y_);

        // 全方向移動
        void translate(const ci::Vec3f& vector_, const ci::Vec3f angle_);
        // 全方向移動のための行列計算
        ci::Vec3f translation(const ci::Vec3f& vector_, const ci::Vec3f& angle_);

        ci::Vec3f rotateMatrix(const ci::Vec3f& angle_, float z_);


        // 斜めの値を円の値に補正する
        ci::Vec2f skewCorrection(const ci::Vec2f& vec_, const float& max_value_ = 1);

    public:

        void console()
        {
            ci::app::console() << "Position : " << position << std::endl;
            ci::app::console() << "Rotation : " << rotation << std::endl;
        }

    public:
        ci::Vec3f position;
        ci::Vec3f angle;
        ci::Quatf rotation;
        ci::Matrix44f local_matrix;
        ci::Vec3f scale;

        ci::Vec3f direction;

    };

}
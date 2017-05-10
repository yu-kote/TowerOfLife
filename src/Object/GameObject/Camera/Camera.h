#pragma once
#include "cinder/Camera.h"
#include "../../../Utility/Json/JsonInfo.h"
#include "../../GameObject/GameObject.h"

namespace tol
{
    class Player;
    class TolBlockHolder;

    class Camera : public tol::GameObject
    {
    public:
        Camera();

        void setup()override;
        void update()override;
        void laterUpdate()override;

        void awakeDraw()override;
        void laterDraw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setTolBlockHolder(std::shared_ptr<tol::TolBlockHolder> block_holder_) { block_holder = block_holder_; }

        void setCenterOfInterestPoint(const ci::Vec3f & point) { center_of_interest_point = point; }
        ci::Vec3f getCenterOfInterestPoint() { return center_of_interest_point; }

        void setEyePoint(const ci::Vec3f & point) { transform.position = point; }
        void lookAt(const ci::Vec3f & eyepoint, const ci::Vec3f & target)
        {
            transform.position = eyepoint;
            center_of_interest_point = target;
        }

        ci::CameraPersp getCamera() { return camera; }

    private:
        ci::CameraPersp camera;

        ci::Vec3f center_of_interest_point;         // 見る先
        ci::Vec3f objective_distance;               // ステージとの距離
        ci::Vec3f objective_distance_init_value;    // ステージとの距離の初期値

        // 行き過ぎたら戻す値を返す
        ci::Vec3f restorePeak(ci::Vec3f check_value, ci::Vec3f restore_value);

    private: // jsonから読むところ

        JsonInfo json;
        void jsonSetup();

    private: // プレイヤー

        std::shared_ptr<tol::Player> player;

    public: // ステージとのやり取り

        int getCameraHeight() { return camera_height; }

    private:

        // カメラの位置と見る先を決める関数
        void decideLookAtCamera();
        // カメラを上げる
        void upCamera();
        // カメラをイージングする
        void easeCamera();

        std::shared_ptr<TolBlockHolder> block_holder;
        ci::Vec3f ease_eyepoint;            // イージングするカメラの位置
        ci::Vec3f ease_center;              // イージングするカメラの見る先
        float ease_speed;                   // イージングの速さ
        int camera_height;                  // カメラの高さ
        int camera_up_time;                 // カメラが上に上がる時間
        int camera_up_remaining_time;       // 上に上がるまでの残り時間

    };
}
#pragma once
#include "../GameObject.h"
#include "../Camera/Camera.h"
#include "cinder/Ray.h"

#include "../../../Utility/Interface/Interface.h"

namespace tol
{
    class Player : public GameObject
    {
    public:
        // プレイヤーの状態
        enum State
        {
            STAND,
            MOVING,
            RIZING,
            FALL,
        };

        void setup()override;
        void update()override;
        void draw()override;
        void laterDraw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }

        ci::Ray getStandRay() { return stand_ray; }
        void setStandRayIntersection(const float & t) { stand_ray_intersection = t; }
        float getStandRayIntersection() { return stand_ray_intersection; }

        ci::Ray getRizeRay() { return rize_ray; }
        void setRizeRayIntersecion(const float& t) { rize_ray_intersection = t; }

        ci::Ray getCameraRay() { return camera_ray; }

        bool isDead() { return is_fall_dead; }

        bool isStand() { return (state == State::STAND || state == State::MOVING); }



    private:
        std::shared_ptr<tol::Camera> camera;

        // 移動関数
        void axisMove();
        // パッドの左スティックの大きさを取得
        ci::Vec2f getLeftAxisVec();

        // ベクトルをみて回転させる関数
        void vecRotate();

        // 角度の差を出す
        float angleDifference(const float& angle1, const float& angle2);

        // floatの値を0にtの速さで近づける
        void valueSlowlyToZero(float& value, float t);

        // レイの更新
        void rayUpdate();
        // ジャンプ
        void jump();
        // 重力をかける
        void useGravity();
        // 立つ
        void stand();
        // 頭をぶつける
        void hitTheHead();

        // プレイヤーの状態を更新する関数
        void stateUpdate();

        void gameover();

        // リセット関数
        void reset();
    private:

        ci::TriMesh* mesh;


        State state;                        // プレイヤーの状態
        State current_state;                // 今のプレイヤーの状態を保存


        ci::Vec3f velocity;                 // ベクトル
        ci::Quatf current_quat;             // 今のクォータニオン
        float ground_move_speed;            // 地上にいるときの加速度
        float ground_move_speed_max;        // 地上にいるときの速さの最大値
        ci::Vec3f moving_distance;          // 一フレームに移動する距離
        bool is_max_speed;                  // 加速が終わっているかどうか
        float air_move_speed;               // 空中にいるときの移動速度


        float gravity;                      // 重力
        float fall_speed_max;               // 落下する最大速度


        float jump_power;                   // ジャンプ力
        ci::Vec3f jump_moment_vec;          // ジャンプする瞬間の移動ベクトル
        int jump_duration;                  // ジャンプボタンが押せる期間
        int jump_time;                      // ジャンプしている間の時間
        bool is_jump_key_press;             // ジャンプキーを押しているかどうか
        bool can_jump;                      // ジャンプできるかどうか


        ci::Ray stand_ray;                  // 地面に立つためのレイ
        float stand_ray_intersection;       // 地面に立つためのレイの交差地点

        ci::Ray rize_ray;                   // 天井にぶつけるためのレイ
        float rize_ray_intersection;        // 天井にぶつけるためのレイの交差地点

        bool is_fall_dead;                  // 落下死したかどうか
        int is_dead_distance_judgment;      // どのぐらい離れたらアウトかの値

        ci::Ray camera_ray;
    };



    class TestDraw : public GameObject
    {
    public:

        void setup()override
        {
            hit_sphere_y = 0.0f;
            Params->addParam("hit_sphere_y", &hit_sphere_y).step(0.01f);
        }
        void update()override
        {

        }
        void draw()override
        {
            ci::Vec3f pos = player->getStandRay().calcPosition(player->getStandRayIntersection());
            ci::gl::drawSphere(pos, 0.3f);
            ci::gl::drawSphere(player->getStandRay().calcPosition(hit_sphere_y), 0.3);

            pos = player->getStandRay().getOrigin();
            ci::gl::drawVector(pos, pos + player->getStandRay().getDirection());

            pos = player->getCameraRay().getOrigin();
            ci::gl::drawVector(pos, pos + player->getCameraRay().getDirection());

        }
        void laterDraw()override
        {

        }

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }

    private:

        std::shared_ptr<tol::Player> player;
        std::shared_ptr<tol::Camera> camera;


        float hit_sphere_y;

    };
}


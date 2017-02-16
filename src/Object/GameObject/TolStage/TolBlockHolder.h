#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "TolCoinHolder.h"

namespace tol
{
    class TolBlockHolder : public GameObject
    {
    public:

        TolBlockHolder() {}

        void setup()override;
        void update()override;
        void draw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setCoinHolder(std::shared_ptr<tol::TolCoinHolder> coin_holder_) { coin_holder = coin_holder_; }

        void reset();

    private: // プレイヤー

        std::shared_ptr<tol::Player> player;
        void playerSetStandRay();
        // レイをもらって一番近いところに当たっている交差点を返す
        float hitValueNearInZero(const ci::Ray& ray);

    private: // カメラ

        void decideLookAtCamera();
        std::shared_ptr<tol::Camera> camera;
        ci::Vec3f ease_eyepoint;
        ci::Vec3f ease_center;

    private: // コイン

        std::shared_ptr<tol::TolCoinHolder> coin_holder;

    private: // ブロックの管理

        // 一番上に一段追加する
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);

        void addBlocks();

    private:

        // 配列番号をもらって範囲外かどうかを返す
        bool isBlockOutOfRange(const int& num);
        // 配列番号が超えたら一番大きい値を返す
        int adjusMinMaxNum(const int& num, const int& max_value);

        // サイズもらって真ん中の値を返す
        ci::Vec2f twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y);
        // 高さをもらって、その高さの一段上のブロックの位置を返す
        float convertBlockHeight(const float& height);
        // 高さをもらって、その高さにあるブロックとブロックの間の高さを返す
        float centerBetweenBlockHeight(const float& height);


        int camera_height;          // カメラの高さ
        int camera_up_time;         // カメラが上に上がる時間
        int camera_up_remaining_time;

        int current_top_height;     // 一番上のブロックの高さ
        int height_interval;        // 一段ずつの間隔
        int block_space;            // 隣のブロックとの間隔


        int z_num;                  // ブロックの奥行きの数
        int x_num;                  // ブロックの横の数

        std::vector<std::shared_ptr<TolBlock>> blocks;

    };
}



#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"

namespace tol
{
    class TolBlockHolder : public GameObject
    {
    public:

        TolBlockHolder() {}

        void setup();
        void update();
        void draw();

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

    private:


        std::shared_ptr<tol::Player> player;
        void playerSetStandRay();
        // レイをもらって一番近いところに当たっている交差点を返す
        float hitValueNearInZero(const ci::Ray& ray);

    private:

        void decideLookAtCamera();
        std::shared_ptr<tol::Camera> camera;
        ci::Vec3f ease_eyepoint;
        ci::Vec3f ease_center;


    private: // ブロックの管理

        // 一番上に一段追加する
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);

    private:

        // 配列番号をもらって範囲外かどうかを返す
        bool isBlockOutOfRange(const int& num);
        // 配列番号が超えたら一番大きい値を返す
        int adjusMinMaxNum(const int& num, const int& max_value);

        ci::Vec2f twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y);
        // 高さをもらって、その高さの一段上のブロックの位置を返す
        float convertBlockHeight(const float& height);
        // 高さをもらって、その高さにあるブロックとブロックの間の高さを返す
        float centerBetweenBlockHeight(const float& height);

        float current_top_height;     // 一番上のブロックの高さ
        float height_interval;        // 一段ずつの間隔
        float block_interval;         // 隣のブロックとの間隔


        int z_num;                    // ブロックの奥行きの数
        int x_num;                    // ブロックの横の数

        std::vector<std::shared_ptr<TolBlock>> blocks;

    };
}



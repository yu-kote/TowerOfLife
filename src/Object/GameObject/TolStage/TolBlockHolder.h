#pragma once
#include "../../../Utility/Json/JsonInfo.h"
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"
#include "TolCoinHolder.h"

namespace tol
{
    class Player;
    class Camera;

    class TolBlockHolder : public GameObject
    {
    public:
        TolBlockHolder() {}

        void setup()override;
        void update()override;
        void draw()override;
        void transDraw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setCoinHolder(std::shared_ptr<tol::TolCoinHolder> coin_holder_) { coin_holder = coin_holder_; }

        // リセット関数
        void reset();

    private: // プレイヤー

        std::shared_ptr<tol::Player> player;
        // レイのあたり判定するところ
        void playerSetStandRay();
        // レイをもらって一番近いところに当たっている交差点を返す
        float hitValueNearInZero(const ci::Ray& ray);

    public: // カメラ

        int getHeightInterval() { return height_interval; }
        ci::Vec2f getCenterPos() { return twoDimensionalArrayCenterPoint(x_num, z_num); }
        // 高さをもらって、その高さにあるブロックとブロックの間の高さを返す
        float centerBetweenBlockHeight(const int& height);
        int getBlockSpace() { return block_space; }

    private:

        // カメラとブロックの距離をみてブロックを消去する関数
        void cameraDistanceToBlockErase();

        std::shared_ptr<tol::Camera> camera;

    private: // コインの情報

        std::shared_ptr<tol::TolCoinHolder> coin_holder;

    private: // ブロックの情報管理

        // jsonからブロックの情報を初期化する関数
        void stageSetup();
        // 一番上に一段追加する
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);
        // json読み込みしてブロックを追加する関数
        void addBlocks();

        // プレイヤーとブロックがかぶったらブロックを透明化する関数
        void transBlock();

        JsonInfo json;

    private: // ステージ

        // 配列番号をもらって範囲外かどうかを返す
        bool isBlockOutOfRange(const int& num);
        // 配列番号が超えたら一番大きい値を返す
        int adjusMinMaxNum(const int& num, const int& max_value);
        // ブロックが何マスになっても中心点を返す
        ci::Vec2f twoDimensionalArrayCenterPoint(const int&  size_x, const int& size_y);
        // 今一番高いところの段数を返す
        int currentTopBlockStep();


        int current_top_height;             // 一番上のブロックの高さ
        int height_interval;                // 一段ずつの間隔
        int block_space;                    // 隣のブロックとの間隔

        int z_num;                          // ブロックの奥行きの数
        int x_num;                          // ブロックの横の数

        std::deque<std::shared_ptr<TolBlock>> blocks;   // popfrontをするのでdequeが最速

    private:

    };
}



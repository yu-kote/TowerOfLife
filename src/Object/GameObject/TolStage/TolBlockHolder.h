#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockActions.h"

namespace tol
{
    class TolBlockHolder : public GameObject
    {
    public:

        TolBlockHolder() {}

        void setup();
        void update();
        void draw();


    private:

        // 一番上に一段追加する
        void addOneStepBlocks(const std::vector<TolBlockActionType>& addblocktypes);

    private:

        float current_top_height;     // 一番上のブロックの高さ
        float height_interval;        // 一段ずつの間隔
        float block_interval;         // 隣のブロックとの間隔

        int z_num;                    // ブロックの奥行きの数
        int x_num;                    // ブロックの横の数

        std::vector<std::shared_ptr<TolBlock>> blocks;

    };
}



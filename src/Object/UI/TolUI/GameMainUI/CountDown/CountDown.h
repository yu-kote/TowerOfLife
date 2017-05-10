#pragma once

#include "../../../TextureRenderer/TextureRenderer.h"
#include "../../../Font/FontBase.h"
#include "../../../../../Utility/Easing/Ease.h"


namespace tol
{

    class CountDown : public FontBase
    {
    public:
        CountDown();

        void setup()override;
        void update()override;
        void draw()override;

        bool isCountDownEnd();

    private:

        void countUpdate();
        bool isCountDownStart();

        bool current_countdown_state;   // 音のために現在のカウントダウンの状態を保存する
        int count_down_start_frame;     // カウントダウンを開始するまでのフレーム
        int frame_count;                // カウントダウン中のフレーム
        int drawcount;                  // 実際に画面に表示する数字
    };

    class CountDownCanvas : public UIBase
    {
    public:
        CountDownCanvas();

        void setup()override;
        void update()override;
        void draw()override;

        bool isCountDownEnd() { return countdown->isCountDownEnd(); }
        bool getIsStart() { return is_start; }
        void start() { is_start = true; }

    private:

        std::shared_ptr<CountDown> countdown;
        bool is_start;
    };
}
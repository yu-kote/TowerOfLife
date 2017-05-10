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

        bool current_countdown_state;   // ���̂��߂Ɍ��݂̃J�E���g�_�E���̏�Ԃ�ۑ�����
        int count_down_start_frame;     // �J�E���g�_�E�����J�n����܂ł̃t���[��
        int frame_count;                // �J�E���g�_�E�����̃t���[��
        int drawcount;                  // ���ۂɉ�ʂɕ\�����鐔��
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
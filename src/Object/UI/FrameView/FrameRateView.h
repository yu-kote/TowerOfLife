#pragma once
#include "../Font/FontBase.h"


namespace tol
{
    class FrameRateView : public tol::FontBase
    {
    public:

        FrameRateView();
        void setup()override;
        void update()override;
        void draw()override;

    private:

        int avg_size;
        int prev_frame;
        std::vector<float> frame_buf;


    };
}
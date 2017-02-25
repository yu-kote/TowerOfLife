#include "FrameRateView.h"

#include "../../../Utility/Time/Time.h"
#include "../../../Utility/Interface/Interface.h"

using namespace ci;
using namespace ci::app;


tol::FrameRateView::FrameRateView()
{
}

void tol::FrameRateView::setup()
{
    //setFontFromAsset("Font/nicokaku_v1.ttf", 60.0f);
    setFont("Hiragino Maru Gothic ProN W4", 60.0f);
    transform.position = Vec3f(1380, 820, 0);
    prev_frame = 0;
    avg_size = 30;
    color->setColor(0, 0, 0);
}

void tol::FrameRateView::update()
{
    int frame = static_cast<int>((1000.0f / Timer.deltaTime()) * 0.001f);

    frame_buf.push_back(frame);

    if (frame_buf.size() > avg_size)
    {
        int frame_total = 0;
        for (int i = 0; i < frame_buf.size(); i++)
        {
            frame_total += frame_buf[i];
        }
        prev_frame = frame_total / avg_size;
        frame_buf.clear();
    }

    drawstring = std::to_string(prev_frame);
}

void tol::FrameRateView::draw()
{
    drawFont();
}

#pragma once
#include "cinder/app/App.h"

enum WindowSize
{
    WIDTH = 1440,
    HEIGHT = 900,
};

bool sphereToSphere(const ci::Vec3f& pos1_,
                    const float& radius1_,
                    const ci::Vec3f& pos2_,
                    const float& radius2_);

bool circleToCircle(const ci::Vec2f& pos1,
                    const float& radius1,
                    const ci::Vec2f& pos2,
                    const float& radius2);

bool pointToRect(const ci::Vec2f& pos,
                 const ci::Rectf& rect);


bool rectToRect(const ci::Rectf& rect1,
                const ci::Rectf& rect2);



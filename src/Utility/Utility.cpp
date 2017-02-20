#include "Utility.h"


bool sphereToSphere(const ci::Vec3f& pos1_,
                    const float& radius1_,
                    const ci::Vec3f& pos2_,
                    const float& radius2_)
{
    float dis = pos1_.distanceSquared(pos2_);
    float r = (radius1_ + radius2_) * (radius1_ + radius2_);
    return dis <= r;
}

bool circleToCircle(const ci::Vec2f & pos1,
                    const float & radius1,
                    const ci::Vec2f & pos2,
                    const float & radius2)
{
    float dis = pos1.distanceSquared(pos2);
    float r = (radius1 + radius2) * (radius1 + radius2);
    return dis <= r;
    return false;
}

bool pointToRect(const ci::Vec2f & pos, const ci::Rectf & rect)
{
    return rect.contains(pos);
}

bool rectToRect(const ci::Rectf& rect1, const ci::Rectf& rect2)
{
    return rect1.intersects(rect2);
}

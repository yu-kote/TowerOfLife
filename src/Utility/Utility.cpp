#include "Utility.h"


bool sphereToSphere(ci::Vec3f pos1_, float radius1_, ci::Vec3f pos2_, float radius2_)
{
    float dis = pos1_.distanceSquared(pos2_);
    float r = (radius1_ + radius2_) * (radius1_ + radius2_);
    return dis <= r;
}
#include "Utility.h"

using namespace ci;

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

// 点と多角形のあたり判定
// このサイトを参考にしました http://marupeke296.com/COL_2D_No4_SquareToSquare.html
bool pointToQuadrangle(const ci::Vec2f & point, const std::vector<ci::Vec2f>& vertex)
{
    int is_inside = true;
    for (int i = 0; i < vertex.size(); i++)
    {
        // ベクトル作り
        Vec2f v1, v2;
        v1 = vertex[i];
        if (i < vertex.size() - 1)
            v2 = vertex[i + 1];
        else
            v2 = vertex[0];

        Vec2f v = v2 - v1;

        // 外積
        float c = v.cross(point);
        float calc = ((v2.x - v1.x) * (point.y - v1.y) - (v2.y - v1.y) * (point.x - v1.x));
        if (calc < 0.0f)
            is_inside = false;
    }
    return is_inside;
}

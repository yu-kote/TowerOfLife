#pragma once
#pragma once
#include "cinder/app/App.h"
#include "cinder/TriMesh.h"

#include "../GameObject.h"

#include "cinder/CinderMath.h"



namespace tol
{
    enum CoinType
    {
        COIN_1,
        COIN_2,
        COIN_3,
        COIN_5,
    };

    class TolCoin : public GameObject
    {
    public:

        TolCoin() {}

        void setup()override;
        void update()override;
        void draw()override;

    public:

        bool isHitToCoin(const ci::Vec3f& pos, float radius_ = 1);

        CoinType coin_type;

    private:

        float rotate_speed;         // ‰ñ“]‘¬“x
        float radius;               // ”¼Œa

    };
}
#pragma once
#pragma once
#include "cinder/app/App.h"
#include "cinder/TriMesh.h"

#include "../GameObject.h"

#include "cinder/CinderMath.h"



namespace tol
{

    class TolCoin : public GameObject
    {
    public:

        TolCoin() {}

        void setup()override;
        void update()override;
        void draw()override;

    public:

        bool isHitToCoin(const ci::Vec3f& pos, float radius_ = 1);

        int coin_amount;

    private:

        ci::TriMesh* mesh;

        float rotate_speed;         // ‰ñ“]‘¬“x
        float radius;               // ”¼Œa

    };
}
#pragma once
#include "cinder/app/App.h"
#include "cinder/TriMesh.h"

#include "../GameObject.h"
#include "TolBlockActionBase.h"
#include "../Player/Player.h"

namespace tol
{
    class TolBlock : public GameObject
    {
    public:
        TolBlock() {}

        void setup()override;
        void update()override;
        void draw()override;

        void transDraw()override;

        template<class T>
        void setBlockAction()
        {
            action = std::make_shared<T>(T(static_cast<TolBlock*>(this)));
            action->setup();
        }

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        float calcMeshIntersection(ci::Ray ray);
        //float playerRayIntersection();

    private:
        std::shared_ptr<TolBlockActionBase> action;


        std::shared_ptr<tol::Player> player;

        ci::TriMesh* mesh;

    };
}


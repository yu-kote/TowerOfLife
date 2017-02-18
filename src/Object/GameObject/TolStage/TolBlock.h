#pragma once
#include "cinder/app/App.h"
#include "cinder/TriMesh.h"


#include "../GameObject.h"
#include "TolBlockActionBase.h"
#include "../Player/Player.h"
#include "../../Component/Components/Material.h"

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
        void setTransparentize(bool value) { is_transparentize = value; };

    private:

        // 透明にする関数
        void transparentize();
        // constrainのカラーバージョン
        ci::ColorA constrainColorA(const ci::ColorA& value, const ci::ColorA& min, const ci::ColorA& max);

        bool is_transparentize;
        float trans_speed;

        std::shared_ptr<TolBlockActionBase> action;

        std::shared_ptr<tol::Player> player;

        ci::TriMesh* mesh;

        ci::gl::Material default_material;
        ci::gl::Material trans_material;

        std::shared_ptr<tol::Material> material;

    };
}


#pragma once
#include "../../GameObject/GameObject.h"


namespace tol
{
    class SkydomeBase : public tol::GameObject
    {
    public:
        void setup() override;
        void update() override;
        void draw() override;

        void setTerget(std::shared_ptr<GameObject> target_);

    protected:
        virtual void skydomeSetup() {}
        std::shared_ptr<GameObject> target;

    };
}

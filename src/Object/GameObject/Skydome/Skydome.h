#pragma once 
#include "../../GameObject/GameObject.h"
#include "../../Component/Components/Texture.h"


namespace tol
{
    class Skydome : public tol::GameObject
    {
    public:
        void setup() override;
        void update() override;
        void draw() override;

        void setTerget(std::shared_ptr<GameObject> target_);


    private:
        GameObject* target;

        ci::Vec3f pos;
    };
}

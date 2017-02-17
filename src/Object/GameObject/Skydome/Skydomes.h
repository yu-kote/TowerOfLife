#pragma once 
#include "../../GameObject/GameObject.h"
#include "../../Component/Components/Texture.h"
#include "SkydomeBase.h"

namespace tol
{
    class EarthSkydome : public tol::SkydomeBase
    {
        void skydomeSetup()override
        {
            addComponent<tol::Texture>(tol::Texture("Skydome1"));
            transform.scale = ci::Vec3f::one() * 500;
        }
    };

    class UniverseSkydome : public tol::SkydomeBase
    {
        void skydomeSetup()override
        {
            addComponent<tol::Texture>(tol::Texture("Skydome2"));
            transform.scale = ci::Vec3f::one() * 1000;
            transform.position.y += 400;
        }
    };
}

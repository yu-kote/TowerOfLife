#pragma once
#include "../../Component/Component.h"
#include "cinder/gl/Material.h"


namespace tol
{
    class Material : public Component
    {
    public:

        Material(ci::gl::Material mt_)
        {
            material = mt_;
        }

        void drawBegin()override
        {
            material.apply();
        }

        void setMaterial(ci::gl::Material mt_)
        {
            material = mt_;
        }

        ci::gl::Material getMaterial() { return material; }

    private:

        ci::gl::Material material;

    };

}
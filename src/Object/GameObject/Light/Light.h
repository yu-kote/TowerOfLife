#pragma once
#include "cinder/gl/Light.h" 
#include "cinder/gl/Material.h"
#include "../GameObject.h"

namespace tol
{
    class Light : public tol::GameObject
    {
    public:
        Light();
        ~Light();


        void setup()override;
        void update()override;
        void draw()override;
        void laterDraw()override;

        void Off();
        void On();

        void directionalLightSetup();
        void pointLightSetup();
        void spotLightSetup();

        void shutdown();
    private:
        ci::gl::Light* light;

        ci::Vec3f directionallight_direction;

    };

}
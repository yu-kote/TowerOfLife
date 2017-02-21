#pragma once
#include "cinder/Camera.h"
#include "../../GameObject/GameObject.h"

namespace tol
{
    class UICamera : public tol::GameObject
    {
    public:
        UICamera();

        void setup()override;
        void update()override;
        void awakeDraw()override;
        void laterUpdate()override;
        void laterDraw()override;

    private:
        ci::CameraOrtho camera;


    };
}
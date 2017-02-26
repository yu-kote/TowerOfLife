#pragma once
#include "cinder/app/App.h"

#include "../../../../Utility/Utility.h"
#include "../../../../Utility/Interface/Interface.h"
#include "../../TextureRenderer/TextureRenderer.h"

namespace tol
{
    class BlocksBackGround : public tol::TextureRenderer
    {
    public:

        BlocksBackGround()
            :TextureRenderer("BlocksBackGround")
        {
        }
        void setup()
        {
            Params->addParam("scale", &transform.scale);
            color->setColor(1, 1, 1, 1.0f);
        }

        void update()
        {

        }

        void draw()
        {
            ci::gl::drawSolidRect(ci::Rectf(0,
                                            0,
                                            WIDTH,//ci::app::getWindowSize().x,
                                            HEIGHT));// ci::app::getWindowSize().y));
        }



    };
}
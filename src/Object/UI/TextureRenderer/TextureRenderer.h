#pragma once
#include "../UIBase.h"
#include "../../../Utility/Input/InputEvent.h"


namespace tol
{
    class TextureRenderer : public UIBase
    {
    public:

        TextureRenderer() {}

        TextureRenderer(const std::string& texture_name)
        {
            addComponent<tol::Texture>(tol::Texture(texture_name));
            texture = getComponent<tol::Texture>();
        }

        void setTexture(const ci::gl::TextureRef& tex) { texture->getTexture() = tex; }

        void drawRect()
        {
            ci::gl::drawSolidRect(ci::Rectf(0.0f, 0.0f, 1.0f, 1.0f));
        }

    protected:

        std::shared_ptr<tol::Texture> texture;  // texture

    };
}
#pragma once
#include "../Component.h"
#include "../../../Task/TextureManager.h"


namespace tol
{
    class Texture : public Component
    {
    public:

        Texture(std::string key_)
        {
            texture = TextureGet.find(key_);
        }

        void drawBegin()override
        {
            texture->enableAndBind();
        }

        void drawEnd() override
        {
            texture->disable();
        }

        ci::gl::TextureRef& getTexture()
        {
            return texture;
        }

    private:
        ci::gl::TextureRef texture;
    };


}
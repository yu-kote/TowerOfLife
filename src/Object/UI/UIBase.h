#pragma once
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"

#include "jsoncpp/json/json.h"

#include "../GameObject/GameObject.h"
#include "../../Task/TextureManager.h"
#include "../../Utility/Easing/Ease.h"
#include "../../Utility/Utility.h"
#include "../../Utility/Input/InputEvent.h"
#include "../Component/Components/Texture.h"
#include "../Component/Components/Color.h"

namespace tol
{
    class UIBase : public tol::GameObject
    {
    public:
        UIBase();
        UIBase(const std::string& name);

        // draw関数を行列関数、コンポーネント関数を回しつつ読んでくれる関数
        void drawReflect();

        void setPos(const ci::Vec3f& pos) { transform.position = pos; }

    protected:

        std::shared_ptr<tol::Color> color;

    };
}
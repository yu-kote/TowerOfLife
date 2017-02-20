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

namespace tol
{
    class UIBase : public tol::GameObject
    {
    public:
        UIBase();
        UIBase(const std::string& name);

        // draw�֐����s��֐��A�R���|�[�l���g�֐����񂵂ǂ�ł����֐�
        void drawReflect();

    private:


    };
}
#pragma once
#include "../UIBase.h"


namespace tol
{
    class ButtonBase : public tol::UIBase
    {
    public:
        ButtonBase(const std::string& texture_name);
        ButtonBase(const std::string& texture_name, const std::function<void()>& func);

        void setCallBackFunc(const std::function<void()>& func) { callback_func = func; }

        void setIsSelect(const bool& value) { is_select = value; }
        bool getIsSelect() { return is_select; }

        void setTexture(const ci::gl::TextureRef& tex) { texture->getTexture() = tex; }

    protected:

        std::function<void()> callback_func;    // ボタンを選択した時に呼び出される関数
        std::shared_ptr<tol::Texture> texture;  // 押されたときや、カーソルを合わせたときに変えるtexture
        float radius;                           // 円のボタンの場合の半径
        bool is_select;                         // 選ばれている、またはマウスが入っている場合はtrue
        bool current_is_select;                 // 現在のselectフラグを保存

    };
}

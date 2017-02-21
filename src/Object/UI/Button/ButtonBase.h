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

        std::function<void()> callback_func;    // �{�^����I���������ɌĂяo�����֐�
        std::shared_ptr<tol::Texture> texture;  // �����ꂽ�Ƃ���A�J�[�\�������킹���Ƃ��ɕς���texture
        float radius;                           // �~�̃{�^���̏ꍇ�̔��a
        bool is_select;                         // �I�΂�Ă���A�܂��̓}�E�X�������Ă���ꍇ��true
        bool current_is_select;                 // ���݂�select�t���O��ۑ�

    };
}

#include "ButtonBase.h"

tol::ButtonBase::ButtonBase()
{
}

tol::ButtonBase::ButtonBase(const std::string& texture_name)
{
    addComponent<tol::Texture>(tol::Texture(texture_name));
    texture = getComponent<tol::Texture>();
}

tol::ButtonBase::ButtonBase(const std::string & texture_name, const std::function<void()>& func)
{
    addComponent<tol::Texture>(tol::Texture(texture_name));
    texture = getComponent<tol::Texture>();
    callback_func = func;
}

#include "ButtonBase.h"
#include "../../../Utility/Input/InputEvent.h"


tol::ButtonBase::ButtonBase(const std::string & texture_name)
    :TextureRenderer(texture_name)
{
}

tol::ButtonBase::ButtonBase(const std::string & texture_name, const std::function<void()>& func)
    : TextureRenderer(texture_name)
{
    callback_func = func;
}

void tol::ButtonBase::awake()
{
    mouse_position = env.mousePosition() - transform.position.xy();
}

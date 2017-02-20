#include "UIBase.h"

tol::UIBase::UIBase()
{
}

tol::UIBase::UIBase(const std::string & name)
{
}

void tol::UIBase::drawReflect()
{
    drawBegin();
    pushModelView();
    componentsDraw();
    draw();
    popModelView();
    drawEnd();
}

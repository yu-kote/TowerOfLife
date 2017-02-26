#include "UIBase.h"

tol::UIBase::UIBase()
{
    addComponent<tol::Color>(tol::Color(1.0f, 1.0f, 1.0f));
    color = getComponent<tol::Color>();
}

tol::UIBase::UIBase(const std::string & name)
{
    addComponent<tol::Color>(tol::Color(1.0f, 1.0f, 1.0f));
    color = getComponent<tol::Color>();
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

void tol::UIBase::drawReflectTransform()
{
    pushModelView();
    draw();
    popModelView();
}

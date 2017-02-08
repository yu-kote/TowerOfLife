#include "GameObject.h"

tol::GameObject::GameObject()
{
    active_in_scene = true;
    is_update_active = true;
}

tol::GameObject::GameObject(const std::string & name_) :
    Object(name_)
{
    active_in_scene = true;
    is_update_active = true;
}

void tol::GameObject::pushModelView()
{
    ci::gl::pushModelView();
    ci::gl::translate(transform.position);
    //ci::gl::rotate(transform.angle);
    //ci::gl::multModelView(transform.rotation.toMatrix44());
    glMultMatrixf(transform.rotation.toMatrix44());
    ci::gl::scale(transform.scale);
}

void tol::GameObject::popModelView()
{
    ci::gl::popModelView();
}

void tol::GameObject::componentsUpdate()
{
    for (auto it : components)
    {
        it.second->update();
    }
}

void tol::GameObject::drawBegin()
{
    for (auto it : components)
    {
        it.second->drawBegin();
    }
}

void tol::GameObject::drawEnd()
{
    for (auto it : components)
    {
        it.second->drawEnd();
    }
}

void tol::GameObject::componentsDraw()
{
    for (auto it : components)
    {
        it.second->draw();
    }
}

void tol::GameObject::componentsDestroy()
{
    for (auto it : components)
    {
        it.second->destory();
    }
    components.clear();
}


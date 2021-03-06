#include "GameObject.h"

tol::GameObject::GameObject()
{
    active_in_scene = true;
    is_update_active = true;
    is_draw_active = true;
}

tol::GameObject::GameObject(const std::string & name_) :
    Object(name_)
{
    active_in_scene = true;
    is_update_active = true;
    is_draw_active = true;
}

void tol::GameObject::pushModelView()
{
    ci::gl::pushModelView();
    ci::gl::translate(transform.position);
    ci::gl::rotate(transform.angle);
    //ci::gl::multModelView(transform.rotation.toMatrix44());
    glMultMatrixf(transform.rotation.toMatrix44());
    ci::gl::scale(transform.scale);
    transform.world_matrix = ci::gl::getModelView();
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
    if (!active_in_scene)return;
    if (!is_draw_active)return;
    for (auto it : components)
    {
        it.second->drawBegin();
    }
}

void tol::GameObject::drawEnd()
{
    if (!active_in_scene)return;
    if (!is_draw_active)return;
    for (auto it : components)
    {
        it.second->drawEnd();
    }
}

void tol::GameObject::componentsDraw()
{
    if (!active_in_scene)return;
    if (!is_draw_active)return;
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


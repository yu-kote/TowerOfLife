#include "Skydome.h"
#include "../../Component/Components/Material.h"
#include "cinder/gl/Material.h"

using namespace ci;
using namespace ci::app;

void tol::Skydome::setup()
{
    addComponent<tol::Texture>(tol::Texture("Skydome"));
    addComponent<tol::Material>(tol::Material(tol::Material(
        gl::Material(ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Ambient
                     ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Diffuse
                     ColorA(1.0f, 1.0f, 1.0f, 1.0f),      // Specular
                     80.0f,                               // Shininess
                     ColorA(0.5f, 0.5f, 0.5f, 1.0f)))));	  // Emission

    transform.scale = ci::Vec3f::one() * 500;
}

void tol::Skydome::update()
{
    if (target == nullptr)return;
    transform.position = (*target).transform.getWorldPosition();

}

void tol::Skydome::draw()
{
    glCullFace(GL_FRONT);

    ci::gl::drawSphere(ci::Vec3f::zero(), 1, 30);


    glCullFace(GL_BACK);

}

void tol::Skydome::setTerget(std::shared_ptr<GameObject> target_)
{
    target = target_.get();
}

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class TowerOfLife : public AppNative
{
public:
    void setup();
    void mouseDown(MouseEvent event);
    void update();
    void draw();
};

void TowerOfLife::setup()
{
}

void TowerOfLife::mouseDown(MouseEvent event)
{
}

void TowerOfLife::update()
{
}

void TowerOfLife::draw()
{
    gl::clear(Color(0, 0, 0));


}

CINDER_APP_NATIVE(TowerOfLife, RendererGl)

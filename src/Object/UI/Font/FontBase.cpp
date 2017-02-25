#include "FontBase.h"

using namespace ci;
using namespace ci::app;


tol::FontBase::FontBase()
{
}

tol::FontBase::FontBase(const std::string & font_name, const float& size)
{
    font = Font(font_name, size);
}

void tol::FontBase::setFont(const std::string & font_name, const float & size)
{
    font = Font(font_name, size);
}

void tol::FontBase::setFontFromAsset(const std::string & file_name, const float & size)
{
    font = Font(loadAsset(file_name), size);
}

void tol::FontBase::drawFont()
{
    gl::drawString(drawstring, Vec2f::zero(),
                   color->getColor(), font);
}

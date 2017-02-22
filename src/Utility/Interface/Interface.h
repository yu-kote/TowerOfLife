#pragma once
#include "cinder/params/Params.h"

#define Params Interface::instance().Param


class Interface
{
public:
    Interface(ci::params::InterfaceGlRef _inter)
    {
        Param = _inter;
    }

    static Interface& instance()
    {
        static Interface interface(ci::params::InterfaceGl::create("Interface", ci::Vec2i(200, 300)));
        return interface;
    }
    ci::params::InterfaceGlRef Param;
private:

};
